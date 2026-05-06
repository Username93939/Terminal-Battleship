#pragma once

class Point {
public:
    Point(int x, int y);
    Point();
    bool Equal(const Point& p) const;
    int X() const;
    int Y() const;
private:
    int x;
    int y;
};