#pragma once

#include "ship.h"
#include "point.h"
#include <vector>

class Board {
public:
    Board();
    Board(std::vector<Point> hits, std::vector<Point> shots, std::vector<Point> sunkPoints);
    bool FitData(Board& b);
    bool IsHit(Point& p);
    bool AddShip(Ship& ship);
    void Clear();
private:
    bool hitmap[9][9];
    bool nullpoints[9][9];
    std::vector<Ship> ships;
};