#include "Material.hpp"

const SimMaterial MATERIALS[MATERIAL_COUNT] = {//Material table
    { "Empty", EMPTY, NONE, BLACK },
    { "Sand", SAND, POWDER, YELLOW },
    { "Water", WATER, LIQUID, BLUE },
    { "Stone", STONE, SOLID, GRAY },
    { "Vapor", VAPOR, GAS, SKYBLUE },
};

const SimMaterial& getMaterial(MaterialID id){
    return MATERIALS[id];
}
