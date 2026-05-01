#pragma once

#include <string>
#include <vector>
#include "point.h"

class Ship {
public:
    Ship(std::string role, bool rot, int x, int y, int size);
    Ship();
    bool Sunk();
    bool Shot(Point loc);
    bool ContainsPoint(Point p);
    bool ValidLocation(Ship ship);
    std::string Role();
    std::vector<Point> Location();
private:
    bool rotation;
    std::string role;
    bool sunk;
    std::vector<bool> hits;
    std::vector<Point> points;
};