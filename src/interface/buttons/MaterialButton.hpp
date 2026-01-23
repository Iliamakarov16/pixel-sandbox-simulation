#pragma once

#include "Button.hpp"
#include "src\SimMaterial.hpp"

class Game;

class MaterialButton : public Button{
private: 
   SimMaterial material_; 
   Game& game_;
public:
    MaterialButton(const float x, const float y, const std::string& text, const Color& textColor, const Color& buttonColor, const SimMaterial& material, Game& game) 
    : Button(x, y, text, textColor, buttonColor), material_(material), game_(game){};

    void onClick() override;
};
