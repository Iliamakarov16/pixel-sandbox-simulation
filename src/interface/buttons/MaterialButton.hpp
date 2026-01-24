#pragma once

#include "Button.hpp"
#include "src/core/SimMaterial.hpp"


class Game;

class MaterialButton : public Button{
private: 
   SimMaterial material_; 
   Game& game_;
   Rectangle outlineRect;
public:
    MaterialButton(const float x, const float y, const std::string& text, const Color& textColor, const Color& buttonColor, const SimMaterial& material, Game& game) 
    : Button(x, y, text, textColor, buttonColor), 
      material_(material), 
      game_(game), 
      outlineRect(Rectangle(getButtonRect().x + 1, getButtonRect().y, getButtonRect().width - 2, getButtonRect().height - 1)){};

    void selected() const;
    void onClick() override;
};
