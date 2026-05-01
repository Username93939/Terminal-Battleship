#pragma once

#include "ship.h"
#include "point.h"
#include "rng.h"
#include "board.h"
#include <vector>
#include <string>

class Battleship {
public:
    Battleship(bool color);
    void DrawBoard();
    void DrawRadar();
    bool TakeShot(Point pos);
    bool GameOver();
    void TakeShot();
private:
    Ship p1Ships[5];
    Ship p2Ships[5];
    std::vector<Point> p1Hits;
    std::vector<Point> p2Hits;
    std::vector<Point> p1Shots;
    std::vector<Point> p2Shots;
    std::vector<Board> possibleBoards;
    const static std::string SHIP_ROLES[5];
    const static int SHIP_SIZES[5];
    RNG rng;
    static void Clear();
    void UpdateAfterShot(bool turn);
    std::vector<Point> p1SunkPoints;
    bool useColor;
};