#include "point.h"

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

Point::Point() {
    this->x = -1;
    this->y = -1;
}

bool Point::Equal(Point p) {
    return p.x == this->x && p.y == this->y;
}

int Point::X() {
    return this->x;
}

int Point::Y() {
    return this->y;
}