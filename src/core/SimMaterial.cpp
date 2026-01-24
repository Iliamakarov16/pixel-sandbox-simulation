#include "SimMaterial.hpp"

const SimMaterial MATERIALS[MATERIAL_COUNT] = {//Material table
  //{ name, id, type, color, isFlammable, density, viscosity } (density for gasses: 0 - 50, for liquid: 50 - 99, other: 100)
    { "Empty", EMPTY, NONE, BLACK, false, 0, 0 },
    { "Sand", SAND, GRANULAR, SAND_COLOR, false, 100, 0 },
    { "Water", WATER, LIQUID, BLUE, false, 70, 0},
    { "Stone", STONE, SOLID, STONE_COLOR, false, 100, 0 },
    { "Steam", STEAM, GAS, SKYBLUE, false, 20, 0 },
    { "WetSand", WET_SAND, CUSTOM, WET_SAND_COLOR, false, 100, 0 },
    { "Smoke", SMOKE, GAS, SMOKE_COLOR, false, 50, 0},
    { "Flame", FLAME, CUSTOM, FLAME_COLOR, false, 100, 0},
    { "Wood", WOOD, SOLID, WOOD_COLOR, true, 100, 0 },
    { "Oil", OIL, LIQUID, OIL_COLOR, true, 55, 60},
    { "Cloud", CLOUD, GAS,  CLOUD_COLOR, false, 15, 0},
    { "Rainy Cloud", RAINY_CLOUD, GAS, RAINY_CLOUD_COLOR, false, 15, 0}
};

const SimMaterial& getMaterial(MaterialID id){
    return MATERIALS[id];
}
