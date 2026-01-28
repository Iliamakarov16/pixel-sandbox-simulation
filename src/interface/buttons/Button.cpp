#include "Button.hpp"
#include "src/Game.hpp"

void Button::draw() const{
    const int fontSize = 20;
    const int textWidth = MeasureText(text_.c_str(), fontSize);
    const int sidePadding = 10; 

    const float width = textWidth + sidePadding * 2;
    const float height = 30;
    
    Rectangle buttonRect = {x_, y_, width, height};
    DrawRectangleRounded(buttonRect, 0.5, 1, buttonColor_);

    
    int textX = x_ + (width - textWidth) / 2;
    int textY = y_ + (height - fontSize) / 2;

    DrawText(text_.c_str(), textX, textY, fontSize, textColor_);
}

bool Button::isClicked(){
    const int fontSize = 20;
    const int textWidth = MeasureText(text_.c_str(), fontSize);
    const int sidePadding = 10;

    const float width = textWidth + sidePadding * 2;
    const float height = 30;

    Rectangle buttonRect = {x_, y_, width, height};
    Vector2 mouse = GetMousePosition();
    return CheckCollisionPointRec(mouse, buttonRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

Rectangle Button::getButtonRect() const{
    const int fontSize = 20;
    const int textWidth = MeasureText(text_.c_str(), fontSize);
    const int sidePadding = 10;

    const float width = textWidth + sidePadding * 2;
    const float height = 30;

    return Rectangle{x_, y_, width, height};
}
