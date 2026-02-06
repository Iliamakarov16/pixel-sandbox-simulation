#pragma once

#include "Button.hpp"
#include "src/core/SimMaterial.hpp"


class Game;

class MaterialButton : public Button{
private: 
   SimMaterial material_; 
public:
    MaterialButton(const float x, const float y, const std::string& text, const int& textSize, const Color& textColor, const Color& buttonColor, Game& game, const SimMaterial& material) 
    : Button(x, y, text, textSize, textColor, buttonColor, game), 
      material_(material){};

    void selected() const;
    void onClick() override;
};
