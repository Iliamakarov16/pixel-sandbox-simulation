#pragma once

#include "include/raylib.h"
#include <string>

enum MaterialID { EMPTY, 
                  SAND, 
                  WATER, 
                  STONE, 
                  STEAM,
                  WET_SAND, 
                  SMOKE, 
                  FLAME, 
                  WOOD, 
                  OIL, 
                  CLOUD, 
                  RAINY_CLOUD, 
                  MATERIAL_COUNT };

enum MaterialType { NONE, GRANULAR, SOLID, LIQUID, GAS, CUSTOM};

const Color SAND_COLOR = {203, 189, 147, 255};
const Color STONE_COLOR = {136, 140, 141, 255};
const Color WET_SAND_COLOR = {170, 160, 125, 255};
const Color SMOKE_COLOR = {47, 47, 47, 255};
const Color FLAME_COLOR = {255, 90, 0, 255};
const Color WOOD_COLOR = {86, 50, 5, 255};
const Color OIL_COLOR = {40, 30, 21, 255};
const Color CLOUD_COLOR = {246, 246, 246, 255};
const Color RAINY_CLOUD_COLOR = {116, 116, 116, 255};

struct SimMaterial{
    std::string name;
    MaterialID id;
    MaterialType type;
    Color color;
    bool isFlammable;
    int density;
    int viscosity;
};

extern const SimMaterial MATERIALS[MATERIAL_COUNT];
const SimMaterial& getMaterial(MaterialID id);

