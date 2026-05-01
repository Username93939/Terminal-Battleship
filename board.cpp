#include "board.h"
#include "point.h"
#include "ship.h"
#include <vector>

using namespace std;

Board::Board() {
    ships = {};
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            hitmap[i][j] = false;
            nullpoints[i][j] = false;
        }
    }
}

Board::Board(vector<Point> hits, vector<Point> shots, vector<Point> sunkPoints) {
    ships = {};
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            nullpoints[i][j] = true;
        }
    }
    for (Point& p : shots) {
        hitmap[p.Y()][p.X()] = false;
        nullpoints[p.Y()][p.X()] = false;
    }
    for (Point& p : hits) {
        hitmap[p.Y()][p.X()] = true;
    }
    for (Point& p : sunkPoints) {
        hitmap[p.Y()][p.X()] = false;
    }
}

bool Board::FitData(Board& b) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (!b.nullpoints[i][j] && !this->nullpoints[i][j]) {
                if (this->hitmap[i][j] != b.hitmap[i][j]) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Board::AddShip(Ship& ship) {
    for (Ship& existingShip : ships) {
        if (!ship.ValidLocation(existingShip)) {
            return false;
        }
    }
    ships.push_back(ship);
    for (Point& p : ship.Location()) {
        hitmap[p.Y()][p.X()] = true;
    }
    return true;
}

bool Board::IsHit(Point& p) {
    return hitmap[p.Y()][p.X()];
}

void Board::Clear() {
    ships = {};
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            hitmap[i][j] = false;
            nullpoints[i][j] = false;
        }
    }
}