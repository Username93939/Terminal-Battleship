#include <iostream>
#include <cctype>
#include "battleship.h"
#include "point.h"

using namespace std;

int main() {
    char useColor;
    char colorChoice;
    string temp;
    cout << "Enable color? (y/n): ";
    cin >> temp;
    colorChoice = temp[0];
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
            cin >> temp;
            x = temp[0];
            cout << "Guess row: ";
            cin >> temp;
            y = temp[0] - '0';
            while (toupper(x) - 'A' < 0 || toupper(x) - 'A' > 8 || y < 1 || y > 9 || !game.TakeShot(Point(toupper(x) - 'A', y - 1))) {
                cout << "Invalid guess. Please enter another.\n";
                cout << "Guess column: ";
                cin >> temp;
                x = temp[0];
                cout << "Guess row: ";
                cin >> temp;
                y = temp[0] - '0';
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