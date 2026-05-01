#pragma once

class Point {
public:
    Point(int x, int y);
    Point();
    bool Equal(Point p);
    int X();
    int Y();
private:
    int x;
    int y;
};