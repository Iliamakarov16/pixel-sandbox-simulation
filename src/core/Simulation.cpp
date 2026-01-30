#include "Simulation.hpp"
#include <algorithm>

namespace {
    constexpr int kAmbientTemp = 25;
    constexpr float kLavaHeatSource = 0.2f;
}

//Temperature system
int Simulation::getAvarageTemperature(const int& row, const int& col) const{
    int weightedSum = 0;
    int weightTotal = 0;
    const int radius = 2;
    const int startRow = std::clamp(row - radius, 0, grid_.getRows() - 1);
    const int startCol = std::clamp(col - radius, 0, grid_.getColumns() - 1);
    const int endRow = std::clamp(row + radius, 0, grid_.getRows() - 1);
    const int endCol = std::clamp(col + radius, 0, grid_.getColumns() - 1);

    for (int offsetRow = startRow; offsetRow <= endRow; offsetRow++){
        for (int offsetCol = startCol; offsetCol <= endCol; offsetCol++){
            if (!isValidCell(offsetRow, offsetCol)){
                continue;
            }
            const int dr = std::abs(offsetRow - row);
            const int dc = std::abs(offsetCol - col);
            const int dist = dr + dc;
            const int weight = std::max(1, (radius + 1) - dist);
            weightedSum += temperature_[offsetRow][offsetCol] * weight;
            weightTotal += weight;
        }
    }

    if (weightTotal == 0){
        return temperature_[row][col];
    }

    return weightedSum / weightTotal;
}

void Simulation::updateTemperature(){
    for (int row = 0; row < grid_.getRows(); row++){
        for (int col = 0; col < grid_.getColumns(); col++){
            int t = temperature_[row][col];
            int avgT = getAvarageTemperature(row, col);
            SimMaterial cell = getCell(row, col);
            int baseT = getMaterialBaseTemperature(cell);
            const int targetBase = (baseT > kAmbientTemp) ? kAmbientTemp : baseT;
            int newT = t + (avgT - t) * diffusion;
            newT = newT + (targetBase - newT) * settle;
            if (cell.id == LAVA) {
                newT = newT + (baseT - newT) * kLavaHeatSource;
            }
            nextTemperature_[row][col] = newT;
        }
    }
    temperature_ = nextTemperature_;
    applyTemperature();
}

void Simulation::applyTemperature(){
    for (int row = 0; row < grid_.getRows(); row++){
        for (int col = 0; col < grid_.getColumns(); col++){
            SimMaterial currCell = getCell(row, col);
            int currCellTemp = getCellTemperature(row, col);

            if (currCell.isFlammable){
                switch (currCell.id){
                    case WOOD: 
                        if (currCellTemp > 300) tempGrid_.setCell(row, col, getColoredMaterial(FLAME));
                        break;
                    case OIL:
                        if (currCellTemp > 200) tempGrid_.setCell(row, col, getColoredMaterial(FLAME));
                        break;
                    default:
                        break;
                }
            }
            else{
                switch (currCell.id){
                    case WET_SAND: 
                        if (currCellTemp > 200) tempGrid_.setCell(row, col, getColoredMaterial(SAND));
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

//Physics by material type
//checks if one of bottom neighbors is empty, and sets material to new position if true. 
void Simulation::simulateGranular(const int& row, const int& col, const SimMaterial& material){
    const int bottomRow = row + neighborsOffset_[BOTTOM].first;
    const int bottomCol = col + neighborsOffset_[BOTTOM].second;
    const int bLeftRow = row + neighborsOffset_[BOTTOM_LEFT].first;
    const int bLeftCol = col + neighborsOffset_[BOTTOM_LEFT].second;
    const int bRightRow = row + neighborsOffset_[BOTTOM_RIGHT].first;
    const int bRightCol = col + neighborsOffset_[BOTTOM_RIGHT].second;

    if (isEmptyForSim(bottomRow, bottomCol)) {
        tempGrid_.setCell(bottomRow, bottomCol, material);
        return;
    }
    else if (isEmptyForSim(bLeftRow, bLeftCol)) {
        tempGrid_.setCell(bLeftRow, bLeftCol, material);
        return;
    }
    else if (isEmptyForSim(bRightRow, bRightCol)) {
        tempGrid_.setCell(bRightRow, bRightCol, material);
        return;
    }
    else if (isLiquidCell(bottomRow, bottomCol)){
        if (GetRandomValue(0, 3) == 0) {
            displacement(row, col, bottomRow, bottomCol);
        }
    }

    tempGrid_.setCell(row, col, material);
}

void Simulation::displacement(const int& row_1, const int& col_1, const int& row_2, const int& col_2){
    tempGrid_.setCell(row_1, col_1, getCell(row_1, col_1));
    tempGrid_.setCell(row_2, col_2, getCell(row_2, col_2));
    tempGrid_.swapCells(row_1, col_1, row_2, col_2);
    return;
}

void Simulation::simulateLiquid(const int& row, const int& col, const SimMaterial& material){
    const int bottomRow = row + neighborsOffset_[BOTTOM].first;
    const int bottomCol = col + neighborsOffset_[BOTTOM].second;
    const int bLeftRow = row + neighborsOffset_[BOTTOM_LEFT].first;
    const int bLeftCol = col + neighborsOffset_[BOTTOM_LEFT].second;
    const int bRightRow = row + neighborsOffset_[BOTTOM_RIGHT].first;
    const int bRightCol = col + neighborsOffset_[BOTTOM_RIGHT].second;
    const int leftRow = row + neighborsOffset_[LEFT].first;
    const int leftCol = col + neighborsOffset_[LEFT].second;
    const int rightRow = row + neighborsOffset_[RIGHT].first;
    const int rightCol = col + neighborsOffset_[RIGHT].second;

    int desiredVx = liquidVx_[row][col];
    if (desiredVx == 0) {
        desiredVx = (GetRandomValue(0, 1) == 0) ? -1 : 1;
    }

    if (isEmptyForSim(bottomRow, bottomCol)) {//drops down when nothing bottom cell is empty
        tempGrid_.setCell(bottomRow, bottomCol, material);
        tempLiquidVx_[bottomRow][bottomCol] = desiredVx;
        return;
    }
    else if(getCell(bottomRow, bottomCol).density < material.density){//liquid density logic
        if (isLiquidCell(bottomRow, bottomCol) && GetRandomValue(0, 20) == 0) {
            displacement(row, col, bottomRow, bottomCol);
            tempLiquidVx_[bottomRow][bottomCol] = desiredVx;
            return;
        }
        else if (getCell(bottomRow, bottomCol).type == GAS){
            displacement(row, col, bottomRow, bottomCol);
            tempLiquidVx_[bottomRow][bottomCol] = desiredVx;
            return;
        }
    }

    if (GetRandomValue(0, 100) >= material.viscosity){
        //When the preferred diagonal is blocked, flip horizontal direction.
        if (desiredVx < 0) {
            if (isEmptyForSim(bLeftRow, bLeftCol)) {
                tempGrid_.setCell(bLeftRow, bLeftCol, material);
                tempLiquidVx_[bLeftRow][bLeftCol] = desiredVx;
                return;
            } 
            else if (isEmptyForSim(bRightRow, bRightCol)) {
                desiredVx = 1;
                tempGrid_.setCell(bRightRow, bRightCol, material);
                tempLiquidVx_[bRightRow][bRightCol] = desiredVx;
                return;
            }
        } 
        else {
            if (isEmptyForSim(bRightRow, bRightCol)) {
                tempGrid_.setCell(bRightRow, bRightCol, material);
                tempLiquidVx_[bRightRow][bRightCol] = desiredVx;
                return;
            } 
            else if (isEmptyForSim(bLeftRow, bLeftCol)) {
                desiredVx = -1;
                tempGrid_.setCell(bLeftRow, bLeftCol, material);
                tempLiquidVx_[bLeftRow][bLeftCol] = desiredVx;
                return;
            }
        }
        if (GetRandomValue(0, 10) > 0) {
        //When blocked to the left, tries the opposite side.
        if (desiredVx < 0) {
                if (isEmptyForSim(leftRow, leftCol)) {
                    tempGrid_.setCell(leftRow, leftCol, material);
                    tempLiquidVx_[leftRow][leftCol] = desiredVx;
                    return;
                } 
                else if (isEmptyForSim(rightRow, rightCol)) {
                    desiredVx = 1;
                    tempGrid_.setCell(rightRow, rightCol, material);
                    tempLiquidVx_[rightRow][rightCol] = desiredVx;
                    return;
                }
        } 
        else {//When blocked to the right, tries the opposite side.
            if (isEmptyForSim(rightRow, rightCol)) {
                tempGrid_.setCell(rightRow, rightCol, material);
                tempLiquidVx_[rightRow][rightCol] = desiredVx;
                return;
            } 
            else if (isEmptyForSim(leftRow, leftCol)) {
                desiredVx = -1;
                tempGrid_.setCell(leftRow, leftCol, material);
                tempLiquidVx_[leftRow][leftCol] = desiredVx;
                return;
            }
        }
        }
    }

    tempGrid_.setCell(row, col, material);
    tempLiquidVx_[row][col] = desiredVx;
}

void Simulation::simulateGas(const int& row, const int& col, const SimMaterial& material){
    const int topRow = row + neighborsOffset_[TOP].first;
    const int topCol = col + neighborsOffset_[TOP].second;
    const int tLeftRow = row + neighborsOffset_[TOP_LEFT].first;
    const int tLeftCol = col + neighborsOffset_[TOP_LEFT].second;
    const int tRightRow = row + neighborsOffset_[TOP_RIGHT].first;
    const int tRightCol = col + neighborsOffset_[TOP_RIGHT].second;
    const int leftRow = row + neighborsOffset_[LEFT].first;
    const int leftCol = col + neighborsOffset_[LEFT].second;
    const int rightRow = row + neighborsOffset_[RIGHT].first;
    const int rightCol = col + neighborsOffset_[RIGHT].second;
    
    int desiredVx = gasVx_[row][col];
    if (desiredVx == 0) {
        desiredVx = (GetRandomValue(0, 1) == 0) ? -1 : 1;
    }

    // if (GetRandomValue(0, 500) == 0){
    //     tempGrid_.setCell(row, col, getColoredMaterial(EMPTY)));
    //     return;
    // }

    if (/*material.id == CLOUD ||*/ material.id == RAINY_CLOUD){
        cloudBehavior(row, col, material);
    }

    const bool allowRise = (GetRandomValue(0, 4) != 0);
    if (allowRise) {
        if (isEmptyForSim(topRow, topCol)) {
            tempGrid_.setCell(topRow, topCol, material);
            tempGasVx_[topRow][topCol] = desiredVx;
            return;
        }
        else if(getCell(topRow, topCol).density > material.density && getCell(topRow, topCol).type != STATIC_SOLID){//gas density logic
            if (GetRandomValue(0, 10) == 0) {
                displacement(row, col, topRow, topCol);
            }
        }
    }
    //Material specific behavior

    
    //When the preferred diagonal is blocked, flip horizontal direction.
    if (desiredVx < 0){
        if (isEmptyForSim(tLeftRow, tLeftCol)) {
            tempGrid_.setCell(tLeftRow, tLeftCol, material);
            tempGasVx_[tLeftRow][tLeftCol] = desiredVx;
            return;
        } 
        else if (isEmptyForSim(tRightRow, tRightCol)) {
            desiredVx = 1;
            tempGrid_.setCell(tRightRow, tRightCol, material);
            tempGasVx_[tRightRow][tRightCol] = desiredVx;
            return;
        }
    }
    else{
        if (isEmptyForSim(tRightRow, tRightCol)) {
            tempGrid_.setCell(tRightRow, tRightCol, material);
            tempGasVx_[tRightRow][tRightCol] = desiredVx;
            return;
        } 
        else if (isEmptyForSim(tLeftRow, tLeftCol)) {
            desiredVx = -1;
            tempGrid_.setCell(tLeftRow, tLeftCol, material);
            tempGasVx_[tLeftRow][tLeftCol] = desiredVx;
            return;
        }
    }

    //Only spread sideways occasionally to keep clouds cohesive.
    if (GetRandomValue(0, 3) == 0) {
        if (desiredVx < 0) {
            if (isEmptyForSim(leftRow, leftCol)) {
                tempGrid_.setCell(leftRow, leftCol, material);
                tempGasVx_[leftRow][leftCol] = desiredVx;
                return;
            } 
            else if (isEmptyForSim(rightRow, rightCol)) {
                desiredVx = 1;
                tempGrid_.setCell(rightRow, rightCol, material);
                tempGasVx_[rightRow][rightCol] = desiredVx;
                return;
            }
        } 
        else {//When blocked to the right, tries the opposite side.
            if (isEmptyForSim(rightRow, rightCol)) {
                tempGrid_.setCell(rightRow, rightCol, material);
                tempGasVx_[rightRow][rightCol] = desiredVx;
                return;
            } 
            else if (isEmptyForSim(leftRow, leftCol)) {
                desiredVx = -1;
                tempGrid_.setCell(leftRow, leftCol, material);
                tempGasVx_[leftRow][leftCol] = desiredVx;
                return;
            }
        }
    }
    
    
    tempGrid_.setCell(row, col, material);
    tempGasVx_[row][col] = desiredVx;
}

void Simulation::simulateStaticSolid(const int& row, const int& col, const SimMaterial& material){
    tempGrid_.setCell(row, col, material);
}

void Simulation::simulateDynamicSolid(const int& row, const int& col, const SimMaterial& material){
    const int bottomRow = row + neighborsOffset_[BOTTOM].first;
    const int bottomCol = col + neighborsOffset_[BOTTOM].second;

    if (isEmptyForSim(bottomRow, bottomCol)){
        tempGrid_.setCell(bottomRow, bottomCol, material);
        return;
    }
    else if (isLiquidCell(bottomRow, bottomCol)){
        if (GetRandomValue(0, 3) == 0) {
            displacement(row, col, bottomRow, bottomCol);
        }
    }
    tempGrid_.setCell(row, col, material);
}

void Simulation::simulateCustom(const int& row, const int& col, const SimMaterial& material){
    if (material.id == FLAME){
        flamePhysics(row, col);
        return;
    }
}

//Custom physics 
void Simulation::flamePhysics(const int& row, const int& col){
    const int topRow = row + neighborsOffset_[TOP].first;
    const int topCol = col + neighborsOffset_[TOP].second;

    SimMaterial flame = getMaterial(FLAME);
    for (const auto& offset : neighborsOffset_){
        int neighborRow = row + offset.first;
        int neighborCol = col + offset.second;
        if (getCell(neighborRow, neighborCol).isFlammable){
            tempGrid_.setCell(neighborRow, neighborCol, getColoredMaterial(FLAME));
        }
    }

    if (isEmptyForSim(topRow, topCol) && GetRandomValue(0, 70) == 0){
        tempGrid_.setCell(topRow, topCol, getColoredMaterial(SMOKE));
    }
    if (GetRandomValue(0, 2) == 0){
        tempGrid_.setCell(row, col, getMaterial(EMPTY));
        return;
    }
    tempGrid_.setCell(row, col, flame);
}

//Additional behavior
void Simulation::cloudBehavior(const int& row, const int& col, const SimMaterial& cloud){
    // if (cloud.id == CLOUD && GetRandomValue(0, 1000) == 0){
    //     tempGrid_.setCell(row, col, getColoredMaterial(RAINY_CLOUD)));
    // }
    if (cloud.id == RAINY_CLOUD){
        const int bottomRow = row + neighborsOffset_[BOTTOM].first;
        const int bottomCol = col + neighborsOffset_[BOTTOM].second;

        if (isEmptyForSim(bottomRow, bottomCol) && GetRandomValue(0, 100) == 0){
            tempGrid_.setCell(bottomRow, bottomCol, getColoredMaterial(WATER));
        }
    }
}

//Interactions by material
void Simulation::sandInteractions(const int& row, const int& col) {
    for (auto neighbor : neighborsOffset_){
        if (getCell(row + neighbor.first, col + neighbor.second).id == WATER){    
            tempGrid_.setCell(row, col, getColoredMaterial(WET_SAND));
        }
    }
}

void Simulation::lavaInteractions(const int& row, const int& col){
    const int topRow = row + neighborsOffset_[TOP].first;
    const int topCol = col + neighborsOffset_[TOP].second;

    if (isEmptyForSim(topRow, topCol) && GetRandomValue(0, 70) == 0){
        tempGrid_.setCell(topRow, topCol, getColoredMaterial(FLAME));
    }

    for (const auto& offset : neighborsOffset_){
        int neighborRow = row + offset.first;
        int neighborCol = col + offset.second;
        if (getCell(neighborRow, neighborCol).canEvaporate){
            if (GetRandomValue(0, 10) == 0) tempGrid_.setCell(neighborRow, neighborCol, getColoredMaterial(STEAM));
            if (GetRandomValue(0, 1000) == 0)  tempGrid_.setCell(row, col, getColoredMaterial(OBSIDIAN));
        }
    }
} 

//Interactions by material type (runs all interactions for materials of this type)
void Simulation::granularInteractions(const int& row, const int& col, const SimMaterial& material){
    if (material.id == SAND){
        sandInteractions(row, col);
        return;
    }
    return;
}
void Simulation::liquidInteractions(const int& row, const int& col, const SimMaterial& material){
    if (material.id == LAVA){
        lavaInteractions(row, col);
    }
}


void Simulation::simulate(){
    //clears temps
    tempGrid_.clear();
    for (int row = 0; row < grid_.getRows(); row++){
        for (int col = 0; col < grid_.getColumns(); col++){
            tempLiquidVx_[row][col] = 0;
        }
    }
    for (int row = 0; row < grid_.getRows(); row++){
        for (int col = 0; col < grid_.getColumns(); col++){
            tempGasVx_[row][col] = 0;
        }
    }
    for (int row = 0; row < grid_.getRows(); row++){
        for (int col = 0; col < grid_.getColumns(); col++){
            nextTemperature_[row][col] = 0;
        }
    }
    updateTemperature();
    //simulates
    for(int row = 0; row < grid_.getRows(); row++){
        for(int col = 0; col < grid_.getColumns(); col++){
            SimMaterial cell = getCell(row, col);
            // if (cell.id == WATER && getCellTemperature(row, col) > 50) {
            //     simulateGas(row, col, getMaterial(STEAM));
            //     continue;
            // }
            if (cell.type == GRANULAR){
                granularInteractions(row, col, cell);
                simulateGranular(row, col, cell);
            }
            else if (cell.type == LIQUID){
                liquidInteractions(row, col, cell);
                simulateLiquid(row, col, cell);
            }
            else if (cell.type == GAS){
                simulateGas(row, col, cell);
            }
            else if (cell.type == STATIC_SOLID){
                simulateStaticSolid(row, col, cell);
            }
            else if (cell.type == DYNAMIC_SOLID){
                simulateDynamicSolid(row, col, cell);
            }
            else if (cell.type == CUSTOM){
                simulateCustom(row, col, cell);
            }
        }
    }
    //sets temps
    grid_ = tempGrid_;
    liquidVx_ = tempLiquidVx_;
    gasVx_ = tempGasVx_;
}



SimMaterial Simulation::varyColor(SimMaterial material){
    SimMaterial placedMat = material;
    if (placedMat.id != EMPTY) {
        // Slight per-placement tint so every material gets natural variation.
        const int range = 12;
        const int dr = GetRandomValue(-range, range);
        const int dg = GetRandomValue(-range, range);
        const int db = GetRandomValue(-range, range);
        placedMat.color = {
            static_cast<unsigned char>(std::clamp<int>(placedMat.color.r + dr, 0, 255)),
            static_cast<unsigned char>(std::clamp<int>(placedMat.color.g + dg, 0, 255)),
            static_cast<unsigned char>(std::clamp<int>(placedMat.color.b + db, 0, 255)),
            placedMat.color.a   
        };
    }
    return placedMat;
}

void Simulation::setCell(const int& row, const int& col, const SimMaterial& material){ 
    grid_.setCell(row, col, varyColor(material));
    if (isValidCell(row, col)) {
        const int baseT = getMaterialBaseTemperature(material);
        temperature_[row][col] = baseT;
        nextTemperature_[row][col] = baseT;
    }
}

void Simulation::removeStone(){
    for (int row = 0; row < grid_.getRows(); row++){
        for (int col = 0; col < grid_.getColumns(); col++){
            if (getCell(row, col).id == STONE){
                setCell(row, col, getMaterial(EMPTY));
            }
        }
    }
}
