#include "MaterialButton.hpp"
#include "src\Game.hpp"

void MaterialButton::onClick(){
    game_.setCurrentMaterial(material_.id);
}

