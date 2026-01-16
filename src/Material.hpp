#pragma once

#include "include/raylib.h"
#include <string>

enum MaterialID { EMPTY, SAND, WATER, STONE, VAPOR, MATERIAL_COUNT };
enum MaterialType { NONE, GRANULAR, SOLID, LIQUID, GAS };

struct SimMaterial{
    std::string name;
    MaterialID id;
    MaterialType type;
    Color color; 
};

extern const SimMaterial MATERIALS[MATERIAL_COUNT];
const SimMaterial& getMaterial(MaterialID id);
