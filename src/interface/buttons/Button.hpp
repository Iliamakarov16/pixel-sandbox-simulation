#pragma once

#include "include/raylib.h"
#include <string>

class Button{
private:
    const float x_;
    const float y_;
    const std::string text_;
    const Color textColor_;
    const Color buttonColor_;
public:
    Button(const float x, const float y, const std::string& text, const Color& textColor, const Color& buttonColor) 
    : x_(x), y_(y), text_(text), textColor_(textColor), buttonColor_(buttonColor){};

    void draw() const;

    bool isClicked();

    Rectangle getButtonRect() const;
    
    virtual void onClick() = 0;
    virtual ~Button() = default;
};
