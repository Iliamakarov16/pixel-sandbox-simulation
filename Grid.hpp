#pragma once 
#include "include/raylib.h"
#include <vector>
class Grid{
private:
    int rows_;
    int columns_;
    int cellSize_;
    std::vector<std::vector<bool>> cells_;
public:
    Grid(const int&  rows, const int& columns, const int& cellSize) 
    : rows_(rows/cellSize), columns_(columns/cellSize), cellSize_(cellSize), cells_(rows_, std::vector<bool>(columns_, 0)){};

    void draw();
    void setValue(const int& row, const int& col, const bool& val);
    bool getValue(const int& row, const int& col) const;

    bool isValidCell(const int&  row, const int&  col) const;

    int getRows() const{return rows_;}
    int getCols() const{return columns_;}

    void fillRand();
    void clear();

    void toggleCell(const int& row, const int& col);
};
