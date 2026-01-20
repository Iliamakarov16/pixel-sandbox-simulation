#pragma once

#include "include/raylib.h"
#include <string>

enum MaterialID { EMPTY, SAND, WATER, STONE, STEAM, WET_SAND, MATERIAL_COUNT };
enum MaterialType { NONE, GRANULAR, SOLID, LIQUID, GAS };

const Color ALTSAND = {242, 242, 0, 255};
const Color ALTWATER = {0, 118, 235, 255};

const Color WETSAND = {212, 212, 0, 255};

struct SimMaterial{
    std::string name;
    MaterialID id;
    MaterialType type;
    Color color; 
    Color altColor;
};

extern const SimMaterial MATERIALS[MATERIAL_COUNT];
const SimMaterial& getMaterial(MaterialID id);

