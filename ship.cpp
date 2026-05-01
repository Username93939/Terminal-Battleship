#include "ship.h"
#include "point.h"
#include <string>
#include <vector>

using namespace std;

Ship::Ship(string role, bool rot, int x, int y, int size) {
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

bool Ship::Sunk() {
    return this->sunk;
}

bool Ship::Shot(Point loc) {
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

bool Ship::ContainsPoint(Point p) {
    for (Point& loc : points) {
        if (loc.Equal(p)) {
            return true;
        }
    }
    return false;
}

bool Ship::ValidLocation(Ship ship) {
    for (Point& a : points) {
        for (Point& b : ship.points) {
            if (a.Equal(b)) {
                return false;
            }
        }
    }
    return true;
}

string Ship::Role() {
    return this->role;
}

vector<Point> Ship::Location() {
    return this->points;
}