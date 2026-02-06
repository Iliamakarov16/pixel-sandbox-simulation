#include "SimMaterial.hpp"

const SimMaterial MATERIALS[MATERIAL_COUNT] = {//Material table
  //{ name, id, type, color, isFlammable, canEvaporate, baseTemp, density, viscosity } 
  //(density for gasses: 0 - 50, for liquid: 50 - 99, other: 100)
    { "Empty", EMPTY, NONE, BLACK, false, false, 25, 0, 0 },
    { "Sand", SAND, GRANULAR, SAND_COLOR, false, false, 25, 100, 0 },
    { "Water", WATER, LIQUID, BLUE, false, true, 25, 60, 0 },
    { "Stone", STONE, DYNAMIC_SOLID, STONE_COLOR, false, false, 25, 100, 0 },
    { "Stone Wall", STONE_WALL, STATIC_SOLID, STONE_COLOR, false, false, 25, 100, 0 },
    { "Steam", STEAM, GAS, SKYBLUE, false, false, 25, 20, 0 },
    { "Wet Sand", WET_SAND, DYNAMIC_SOLID, WET_SAND_COLOR, false, false, 25, 100, 0 },
    { "Smoke", SMOKE, GAS, SMOKE_COLOR, false, false, 25, 25, 0},
    { "Flame", FLAME, CUSTOM, FLAME_COLOR, false, false, 500, 100, 0},
    { "Wood", WOOD, STATIC_SOLID, WOOD_COLOR, true, false, 25, 100, 0 },
    { "Leaf", LEAF, STATIC_SOLID, LEAF_COLOR, true, false, 25, 100, 0 },
    { "Oil", OIL, LIQUID, OIL_COLOR, true, false, 25, 55, 30 },
    { "Cloud", CLOUD, GAS,  CLOUD_COLOR, false, false, 25, 15, 0},
    { "Rainy Cloud", RAINY_CLOUD, GAS, RAINY_CLOUD_COLOR, false, false, 25, 21, 0},
    { "Lava", LAVA, LIQUID, LAVA_COLOR, false, false, 1200, 65, 60 },
    { "Obsidian", OBSIDIAN, DYNAMIC_SOLID, OBSIDIAN_COLOR, false, false, 25, 100, 0},
    { "Propane", PROPANE, GAS, PROPANE_COLOR, true, false, 25, 30, 0}
};

const SimMaterial& getMaterial(MaterialID id){
    return MATERIALS[id];
}
