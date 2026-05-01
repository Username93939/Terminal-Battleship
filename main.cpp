#include <iostream>
#include <cctype>
#include "battleship.h"
#include "point.h"

using namespace std;

int main() {
    char useColor;
    char colorChoice;
    cout << "Enable color? (y/n): ";
    cin >> colorChoice;
    useColor = toupper(colorChoice) == 'Y';
    Battleship game = Battleship(useColor);
    bool turn = true;
    while (true) {
        game.DrawRadar();
        game.DrawBoard();
        if (turn) {
            char x;
            int y;
            cout << "Guess column: ";
            cin >> x;
            cout << "Guess row: ";
            cin >> y;
            while (toupper(x) - 'A' < 0 || toupper(x) - 'A' > 8 || y < 1 || y > 9 || !game.TakeShot(Point(toupper(x) - 'A', y - 1))) {
                cout << "Guess column: ";
                cin >> x;
                cout << "Guess row: ";
                cin >> y;
            }
        } else {
            game.TakeShot();
        }
        if (game.GameOver()) {
            break;
        }
        turn = !turn;
    }
    system("pause");
    return 0;
}