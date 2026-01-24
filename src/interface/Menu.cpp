#include "Menu.hpp"
#include "src/Game.hpp"

Menu::Menu(Game& game, int menuTopRow, Color color)
    : game_(game),
      bounds_{0.0f, static_cast<float>(menuTopRow), static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight() - menuTopRow)},
      color_(color){
    const int fontSize = 20;
    const int sidePadding = 10;
    const float buttonHeight = 30.0f;
    const float padding = 10.0f;

    float x = padding;
    float y = bounds_.y + padding;
    const float maxX = bounds_.x + bounds_.width - padding;

    for (int i = 1; i < MATERIAL_COUNT; i++){
        const SimMaterial& material = getMaterial(static_cast<MaterialID>(i));
        const float buttonWidth = MeasureText(material.name.c_str(), fontSize) + sidePadding * 2;

        if (x + buttonWidth > maxX){
            x = padding;
            y += buttonHeight + padding;
        }

        materialButtons_.push_back(MaterialButton(
            x, y, material.name, BLACK, material.color, material, game_
        ));
        x += buttonWidth + padding;
    }
}

void Menu::update(){
    Vector2 mouse = GetMousePosition();
    if (!CheckCollisionPointRec(mouse, bounds_)){
        return;
    }
    for (auto& button : materialButtons_){
        if (button.isClicked()){
            button.onClick();
        }
    }
}

void Menu::draw() const{
    DrawRectangleRec(bounds_, color_);
    for (const auto& button : materialButtons_){
        button.draw();
        button.selected();
    }
}
