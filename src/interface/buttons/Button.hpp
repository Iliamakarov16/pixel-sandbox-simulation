#pragma once

#include "include/raylib.h"
#include <string>

class Game;

class Button{
private:
    const float x_;
    const float y_;
    const std::string text_;
    const Color textColor_;
    const Color buttonColor_;
    
protected:
    Rectangle outlineRect;
    Game& game_;
public:
    Button(const float x, const float y, const std::string& text, const Color& textColor, const Color& buttonColor, Game& game) 
    : x_(x), 
      y_(y), 
      text_(text), 
      textColor_(textColor), 
      buttonColor_(buttonColor),
      outlineRect(Rectangle{getButtonRect().x + 1.0f, getButtonRect().y, getButtonRect().width - 2.0f, getButtonRect().height - 1.0f}),
      game_(game)
      {};

    void draw() const;

    bool isClicked();

    Rectangle getButtonRect() const;
    
    virtual void onClick() = 0;
    virtual ~Button() = default;
};
