#include "battleship.h"
#include "point.h"
#include "ship.h"
#include "rng.h"
#include "board.h"
#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include <limits>

using namespace std;

const string Battleship::SHIP_ROLES[5] = {"Patrol Boat", "Destroyer", "Submarine", "Battleship", "Aircraft Carrier"};
const int Battleship::SHIP_SIZES[5] = {2, 3, 3, 4, 5};

Battleship::Battleship(bool color) {
    p1Shots = {};
    p2Shots = {};
    p1Hits = {};
    p2Hits = {};
    rng = RNG();
    p1SunkPoints = {};
    useColor = color;
    Battleship::Clear();
    cout << "Loading...";
    Battleship::Clear();
    DrawBoard();
    string temp;
    for (int i = 0; i < 5; i++) {
        cout << "Place your " << Battleship::SHIP_ROLES[i] << endl << "Orientation (1 for vertical, 2 for horizontal): ";
        int rotation;
        char col = 0;
        int row = 0;
        cin >> temp;
        rotation = temp[0] - '0';
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (rotation != 1 && rotation != 2) {
            cout << "Invalid orientation. Please enter another (1 for vertical, 2 for horizontal): ";
            cin >> temp;
            rotation = temp[0] - '0';
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (rotation == 1) {
            cout << "Choose a column for the " << Battleship::SHIP_ROLES[i] << ": ";
            cin >> temp;
            col = temp[0];
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while (toupper(col) - 'A' < 0 || toupper(col) - 'A' > 8) {
                cout << "Invalid column. Please choose another column: ";
                cin >> temp;
                col = temp[0];
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Choose the topmost row of the " << Battleship::SHIP_ROLES[i] << ": ";
            cin >> temp;
            row = temp[0] - '0';
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while (row < 1 || row > 10 - SHIP_SIZES[i]) {
                cout << "Invalid row. Please choose another row: ";
                cin >> temp;
                row = temp[0] - '0';
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } else {
            cout << "Choose a row for the " << Battleship::SHIP_ROLES[i] << ": ";
            cin >> temp;
            row = temp[0] - '0';
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while (row < 0 || row > 9) {
                cout << "Invalid row. Please choose another row: ";
                cin >> temp;
                row = temp[0] - '0';
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Choose the leftmost column of the " << Battleship::SHIP_ROLES[i] << ": ";
            cin >> temp;
            col = temp[0];
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while (toupper(col) - 'A' < 0 || toupper(col) - 'A' > 9 - SHIP_SIZES[i]) {
                cout << "Invalid column. Please choose another column: ";
                cin >> temp;
                col = temp[0];
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        bool rot = rotation == 2;
        bool valid = true;
        for (Ship& ship : p1Ships) {
            if (!ship.ValidLocation(Ship(Battleship::SHIP_ROLES[i], rot, toupper(col) - 'A', row - 1, Battleship::SHIP_SIZES[i]))) {
                valid = false;
            }
        }
        if (valid) {
            p1Ships[i] = Ship(Battleship::SHIP_ROLES[i], rot, toupper(col) - 'A', row - 1, Battleship::SHIP_SIZES[i]);
            Battleship::Clear();
            DrawBoard();
        } else {
            Battleship::Clear();
            DrawBoard();
            cout << "This ship cannot be placed here." << endl;
            i--;
        }
    }
    for (int i = 0; i < 5; i++) {
        bool rotation = rng.Next() > 0.5;
        int x, y;
        if (rotation) {
            x = static_cast<int>(rng.Next() * (9 - Battleship::SHIP_SIZES[i]));
            y = static_cast<int>(rng.Next() * 9);
        } else {
            x = static_cast<int>(rng.Next() * 9);
            y = static_cast<int>(rng.Next() * (9 - Battleship::SHIP_SIZES[i]));
        }
        bool valid = true;
        for (Ship& ship : p2Ships) {
            if (!ship.ValidLocation(Ship(Battleship::SHIP_ROLES[i], rotation, x, y, Battleship::SHIP_SIZES[i]))) {
                valid = false;
            }
        }
        while (!valid) {
            rotation = rng.Next() > 0.5;
            if (rotation) {
                x = static_cast<int>(rng.Next() * (9 - Battleship::SHIP_SIZES[i]));
                y = static_cast<int>(rng.Next() * 9);
            } else {
                x = static_cast<int>(rng.Next() * 9);
                y = static_cast<int>(rng.Next() * (9 - Battleship::SHIP_SIZES[i]));
            }
            valid = true;
            for (Ship& ship : p2Ships) {
                if (!ship.ValidLocation(Ship(Battleship::SHIP_ROLES[i], rotation, x, y, Battleship::SHIP_SIZES[i]))) {
                    valid = false;
                }
            }
        }
        p2Ships[i] = Ship(Battleship::SHIP_ROLES[i], rotation, x, y, Battleship::SHIP_SIZES[i]);
    }
    Battleship::Clear();
}

void Battleship::DrawBoard() {
    cout << "Board\n\n" << " " << " ";
    for (int i = 0; i < 9; i++) {
        cout << static_cast<char>('A' + i) << " ";
    }
    cout << endl;
    for (int i = 0; i < 9; i++) {
        cout << i + 1 << " ";
        for (int j = 0; j < 9; j++) {
            char correctMark = '.';
            for (Ship& s : p1Ships) {
                if (s.ContainsPoint(Point(j, i))) {
                    if (useColor) {
                        cout << "\033[38;2;255;255;0m";
                    }
                    correctMark = '#';
                }
            }
            for (Point& p : p2Shots) {
                if (p.Equal(Point(j, i))) {
                    if (useColor) {
                        cout << "\033[0m";
                    }
                    correctMark = '@';
                }
            }
            for (Point& p : p2Hits) {
                if (p.Equal(Point(j, i))) {
                    if (useColor) {
                        cout << "\033[38;2;255;0;0m";
                    }
                    correctMark = '*';
                }
            }
            if (static_cast<int>(p2Shots.size()) > 0 && Point(j, i).Equal(p2Shots[static_cast<int>(p2Shots.size() - 1)])) {
                cout << "\033[1m";
            }
            cout << correctMark << "\033[0m ";
        }
        cout << endl;
    }
    cout << endl;
}

void Battleship::DrawRadar() {
    cout << "Radar\n\n" << " " << " ";
    for (int i = 0; i < 9; i++) {
        cout << static_cast<char>('A' + i) << " ";
    }
    cout << endl;
    for (int i = 0; i < 9; i++) {
        cout << i + 1 << " ";
        for (int j = 0; j < 9; j++) {
            char correctMark = '.';
            for (Point& p : p1Shots) {
                if (p.Equal(Point(j, i))) {
                    if (useColor) {
                        cout << "\033[0m";
                    }
                    correctMark = '@';
                }
            }
            for (Point& p : p1Hits) {
                if (p.Equal(Point(j, i))) {
                    if (useColor) {
                        cout << "\033[38;2;255;0;0m";
                    }
                    correctMark = '*';
                }
            }
            if (static_cast<int>(p1Shots.size()) > 0 && Point(j, i).Equal(p1Shots[static_cast<int>(p1Shots.size() - 1)])) {
                cout << "\033[1m";
            }
            cout << correctMark << "\033[0m ";
        }
        cout << endl;
    }
    cout << endl;
}

bool Battleship::TakeShot(Point pos) {
    for (Point& shot : p1Shots) {
        if (shot.Equal(pos)) {
            cout << "You already guessed that!" << endl;
            return false;
        }
    }
    p1Shots.push_back(pos);
    for (Ship& ship : p2Ships) {
        if (ship.Shot(pos)) {
            if (useColor) {
                cout << "\033[38;2;255;0;0m";
            }
            p1Hits.push_back(pos);
            if (!ship.Sunk()) {
                cout << "Hit!\033[0m" << endl;
                UpdateAfterShot(true);
                return true;
            } else {
                cout << "Sunk enemy " << ship.Role() << "!\033[0m" << endl;
                UpdateAfterShot(true);
                return true;
            }
        }
    }
    cout << "Miss!" << endl;
    UpdateAfterShot(true);
    return true;
}

void Battleship::TakeShot() {
    Battleship::Clear();
    cout << "loading...";
    Board current = Board(p2Hits, p2Shots, p1SunkPoints);
    vector<Board> testBoards(25000);
    int validBoards = 0;
    vector<Board> validIndex = {};
    int hitMap[9][9];
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            hitMap[i][j] = 0;
        }
    }
    for (Board& board : testBoards) {
        int tries = 0;
        while (true) {
            tries++;
            vector<Ship> testShips = {};
            board.Clear();
            while (true) {
                testShips = {};
                for (Ship& p1Ship : p1Ships) {
                    if (!p1Ship.Sunk()) {
                        bool rotation = rng.Next() > 0.5;
                        if (rotation) {
                            testShips.push_back(Ship("", rotation, static_cast<int>(rng.Next() * (10 - static_cast<int>(p1Ship.Location().size()))), static_cast<int>(rng.Next() * 9), static_cast<int>(p1Ship.Location().size())));
                        } else {
                            testShips.push_back(Ship("", rotation, static_cast<int>(rng.Next() * 9), static_cast<int>(rng.Next() * (10 - static_cast<int>(p1Ship.Location().size()))), static_cast<int>(p1Ship.Location().size())));
                        }
                    }
                }
                bool allShipsValid = true;
                for (int i = 0; i < static_cast<int>(testShips.size()); i++) {
                    for (int j = i + 1; j < static_cast<int>(testShips.size()); j++) {
                        if (!testShips.at(i).ValidLocation(testShips.at(j))) {
                            allShipsValid = false;
                        }
                    }
                }
                if (allShipsValid) {
                    break;
                }
            }
            for (int i = 0; i < static_cast<int>(testShips.size()); i++) {
                board.AddShip(testShips.at(i));
            }
            if (current.FitData(board)) {
                validBoards++;
                validIndex.push_back(board);
                break;
            }
            if (validBoards > 10 && tries > 100) {
                board.Clear();
                break;
            }
        }
    }
    for (Board& board : validIndex) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                Point test = Point(i, j);
                bool alreadyGuessed = false;
                for (Point& p : p2Shots) {
                    if (test.Equal(p)) {
                        alreadyGuessed = true;                   
                    }
                }
                if (!alreadyGuessed && board.IsHit(test)) {
                    hitMap[j][i]++;
                }
            }
        }
    }
    int maxProb = -1;
    int bestX = 0, bestY = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (hitMap[i][j] > maxProb) {
                maxProb = hitMap[i][j];
                bestX = j;
                bestY = i;
            }
        }
    }
    p2Shots.push_back(Point(bestX, bestY));
    for (Ship& ship : p1Ships) {
        if (ship.Shot(Point(bestX, bestY))) {
            p2Hits.push_back(Point(bestX, bestY));
            if (ship.Sunk()) {
                for (Point& p : ship.Location()) {
                    p1SunkPoints.push_back(p);
                }
            }
        }
    }
    Battleship::Clear();
    Battleship::UpdateAfterShot(false);
}

bool Battleship::GameOver() {
    bool gameOverP1 = true;
    bool gameOverP2 = true;
    for (Ship& ship : p1Ships) {
        if (!ship.Sunk()) {
            gameOverP1 = false;
        }
    }
    for (Ship& ship : p2Ships) {
        if (!ship.Sunk()) {
            gameOverP2 = false;
        }
    }
    if (gameOverP1) {
        Battleship::Clear();
        cout << "Computer Wins!\n";
        return true;
    } else if (gameOverP2) {
        Battleship::Clear();
        cout << "You Win!\n";
        return true;
    }
    return false;
}

void Battleship::UpdateAfterShot(bool turn) {
    if (turn) {
        cout << "Press enter to update your radar.";
        cin.get();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Battleship::Clear();
        Battleship::DrawRadar();
        Battleship::DrawBoard();
        cout << "Press enter to continue.";
        cin.get();
        Battleship::Clear();
    } else {
        cout << "Press enter to update your board.";
        cin.get();
        Battleship::Clear();
        Battleship::DrawRadar();
        Battleship::DrawBoard();
        cout << "Press enter to continue.";
        cin.get();
        Battleship::Clear();
    }
}

void Battleship::Clear() {
    cout << "\033[2J\033[1;1H\033[3J";
}