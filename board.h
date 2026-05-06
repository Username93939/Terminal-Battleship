#pragma once

#include "ship.h"
#include "point.h"
#include <vector>

class Board {
public:
    Board();
    Board(const std::vector<Point>& hits, const std::vector<Point>& shots, const std::vector<Point>& sunkPoints);
    bool FitData(const Board& b) const;
    bool IsHit(const Point& p) const;
    bool AddShip(const Ship& ship);
    void Clear();
private:
    bool hitmap[9][9];
    bool nullpoints[9][9];
    std::vector<Ship> ships;
};