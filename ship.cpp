#include "ship.h"
#include "point.h"
#include <string>
#include <vector>

using namespace std;

Ship::Ship(const string& role, bool rot, int x, int y, int size) {
    this->role = role;
    this->rotation = rot;
    this->sunk = false;
    for (int i = 0; i < size; i++) {
        this->points.push_back(Point(x + static_cast<int>(rot) * i, y + static_cast<int>(!rot) * i));
        this->hits.push_back(false);
    }
}

Ship::Ship() {
    Ship("", false, -1, -1, 0);
}

bool Ship::Sunk() const {
    return this->sunk;
}

bool Ship::Shot(const Point& loc) {
    for (int i = 0; i < hits.size(); i++) {
        if (points[i].Equal(loc)) {
            hits[i] = true;
            bool sunk = true;
            for (bool hit : hits) {
                if (!hit) {
                    sunk = false;
                }
            }
            this->sunk = sunk;
            return true;
        }
    }
    return false;
}

bool Ship::ContainsPoint(const Point& p) const {
    for (const Point& loc : points) {
        if (loc.Equal(p)) {
            return true;
        }
    }
    return false;
}

bool Ship::ValidLocation(const Ship& ship) const {
    for (const Point& a : points) {
        for (const Point& b : ship.points) {
            if (a.Equal(b)) {
                return false;
            }
        }
    }
    return true;
}

const string& Ship::Role() const {
    return this->role;
}

const vector<Point>& Ship::Location() const {
    return this->points;
}