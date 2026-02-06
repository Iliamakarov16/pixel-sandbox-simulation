#include "Button.hpp"
#include "src/Game.hpp"

void Button::draw() const{
    const int textWidth = MeasureText(text_.c_str(), textSize_);
    const int sidePadding = textSize_/2; 

    const float width = textWidth + sidePadding * 2;
    const float height = textSize_ + 10;
    
    Rectangle buttonRect = {x_, y_, width, height};
    DrawRectangleRounded(buttonRect, 0.5, 1, buttonColor_);

    
    int textX = x_ + (width - textWidth) / 2;
    int textY = y_ + (height - textSize_) / 2;

    DrawText(text_.c_str(), textX, textY, textSize_, textColor_);
}

bool Button::isClicked(){
    Rectangle buttonRect = getButtonRect();
    Vector2 mouse = GetMousePosition();
    return CheckCollisionPointRec(mouse, buttonRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

Rectangle Button::getButtonRect() const{
    const int textWidth = MeasureText(text_.c_str(), textSize_);
    const int sidePadding = textSize_ / 2;

    const float width = textWidth + sidePadding * 2;
    const float height = textSize_ + 10;

    return Rectangle{x_, y_, width, height};
}
