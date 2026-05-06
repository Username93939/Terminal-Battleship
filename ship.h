#pragma once

#include <string>
#include <vector>
#include "point.h"

class Ship {
public:
    Ship(const std::string& role, bool rot, int x, int y, int size);
    Ship();
    bool Sunk() const;
    bool Shot(const Point& loc);
    bool ContainsPoint(const Point& p) const;
    bool ValidLocation(const Ship& ship) const;
    const std::string& Role() const;
    const std::vector<Point>& Location() const;
private:
    bool rotation;
    std::string role;
    bool sunk;
    std::vector<bool> hits;
    std::vector<Point> points;
};