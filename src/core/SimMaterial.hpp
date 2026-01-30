#pragma once

#include "include/raylib.h"
#include <string>

enum MaterialID { EMPTY, 
                  SAND, 
                  WATER, 
                  STONE,
                  STONE_WALL, 
                  STEAM,
                  WET_SAND, 
                  SMOKE, 
                  FLAME, 
                  WOOD,
                  LEAF, 
                  OIL, 
                  CLOUD, 
                  RAINY_CLOUD,
                  LAVA, 
                  OBSIDIAN,
                  MATERIAL_COUNT };

enum MaterialType { NONE, GRANULAR, STATIC_SOLID, LIQUID, GAS, DYNAMIC_SOLID, CUSTOM};

const Color SAND_COLOR = {203, 189, 147, 255};
const Color STONE_COLOR = {136, 140, 141, 255};
const Color WET_SAND_COLOR = {170, 160, 125, 255};
const Color SMOKE_COLOR = {47, 47, 47, 255};
const Color FLAME_COLOR = {255, 90, 0, 255};
const Color WOOD_COLOR = {86, 50, 5, 255};
const Color LEAF_COLOR = {92, 169, 4, 255};
const Color OIL_COLOR = {40, 30, 21, 255};
const Color CLOUD_COLOR = {246, 246, 246, 255};
const Color RAINY_CLOUD_COLOR = {116, 116, 116, 255};
const Color LAVA_COLOR = {207, 16, 32, 255};
const Color OBSIDIAN_COLOR = {46, 41, 58, 255};

struct SimMaterial{
    std::string name;
    MaterialID id;
    MaterialType type;
    Color color;
    bool isFlammable;
    bool canEvaporate;
    int baseTemp;
    int density;
    int viscosity;
};

extern const SimMaterial MATERIALS[MATERIAL_COUNT];
const SimMaterial& getMaterial(MaterialID id);

