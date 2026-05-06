#include "point.h"

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

Point::Point() {
    this->x = -1;
    this->y = -1;
}

bool Point::Equal(const Point& p) const {
    return p.x == this->x && p.y == this->y;
}

int Point::X() const {
    return this->x;
}

int Point::Y() const {
    return this->y;
}