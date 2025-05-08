#ifndef GRID_H
#define GRID_H
#include <array>
#include <memory>
#include <random>
#include <chrono>
#include <iostream>
#include "Cell.h"

class Grid {
    std::array<std::array<int, 4>,4> grid = {};
    std::array<std::array<int, 4>,4> win = {};
    int N = 0;

    int getInvCount() const;

    bool isSolvable() const;

    void fillGrid();

    void printGrid() const;

public:
    int findXPosition() const;

    int size() const;

    int area() const;

    std::array<std::array<int, 4>,4>& get();
    int get(int i, int j) const;

    Grid();
};

#endif
