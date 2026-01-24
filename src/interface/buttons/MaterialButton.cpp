#include "MaterialButton.hpp"
#include "src/Game.hpp"

void MaterialButton::selected() const{
    if (game_.getCurrentMaterial().id == material_.id){
        DrawRectangleRoundedLinesEx(outlineRect, 0.5, 1, 3, GREEN);
    }
}

void MaterialButton::onClick(){
    game_.setCurrentMaterial(material_.id);
}
