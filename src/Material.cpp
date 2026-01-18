#include "Material.hpp"

const SimMaterial MATERIALS[MATERIAL_COUNT] = {//Material table
    { "Empty", EMPTY, NONE, BLACK, BLACK },
    { "Sand", SAND, GRANULAR, YELLOW, ALTSAND },
    { "Water", WATER, LIQUID, BLUE, ALTWATER },
    { "Stone", STONE, SOLID, GRAY, GRAY },
    { "Vapor", VAPOR, GAS, SKYBLUE, SKYBLUE },
    { "WetSand", WET_SAND, GRANULAR, WETSAND, WETSAND }
};

const SimMaterial& getMaterial(MaterialID id){
    return MATERIALS[id];
}
