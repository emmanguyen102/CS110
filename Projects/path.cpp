#include <iostream>
#include <vector>
using namespace std;

enum Slot_type {RED, GREEN, EMPTY, UNUSED};
const int ROWS = 5;
const int COLUMS = 4;

// define matrix
vector< vector<Slot_type> > board{{ GREEN, GREEN, GREEN, GREEN },
                                  { UNUSED, EMPTY, UNUSED, UNUSED },
                                  { UNUSED, EMPTY, EMPTY, UNUSED },
                                  { UNUSED, EMPTY, UNUSED, UNUSED },
                                  { RED, RED, RED, RED } };

const string INPUT_TEXT = "Enter start point (x, y) and destination point (x, y), or q to quit: ";
const string INVALID_POINT = "Invalid start/destination point.";
const string CANNOT_MOVE = "There is no path between start point and destination point.";
const string GAME_OVER = "Game over. Congratulations!";
const string MOVES_MADE = " move(s) made.";

// Prints the grid
// param: matric reference
// return: print the grid
void print(const vector< vector<Slot_type> >& g)
{
    cout << "===============" << endl;
    cout << "|   | 1 2 3 4 |" << endl;
    cout << "---------------" << endl;
    for(unsigned int i = 0; i < ROWS; ++i) {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < COLUMS; ++j) {
            switch(g.at(i).at(j))
            {
                case GREEN: cout << "G "; break;
                case RED: cout << "R "; break;
                case EMPTY: cout << "o "; break;
                case UNUSED: cout << "  "; break;
            }
        }
        cout << "|" << endl;
    }
    cout << "===============" << endl;
}

// Function to remove spaces
// param: string reference
// return: string after removing spaces
string remove_spaces(const string& str)
{
    string strn = "";

    for (unsigned int i = 0; i < str.length(); ++i) {
        if (str[i] != ' ') strn += str[i];
    }
    return strn;
}

// Check the string input having character that is not an integer
// param: string reference
// return: boolean value
bool stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i) {
        if(not isdigit(str.at(i))) {
            is_numeric = false;
            break;
        }
    }
    return is_numeric;
}

// return input in a  list
// param: string reference
// return: a list
vector<int> inputList(string& str) {
    vector<int> line;
    char test = ' ';
    for(string::size_type i = 0; i < str.size(); i++){
        if(str[i] != test) {
            line.push_back(str[i] - '0');
        }
    }
    return line;
}

// Check input validity
// param: list reference
// return: boolean value
bool check_input(vector< int >& command) {
    int x1 = command[1] - 1;
    int y1 = command[0] - 1;
    int x2 = command[3] - 1;
    int y2 = command[2] - 1;

    if ( x1 < 0 || x2 < 0 ||
         y1 < 0 || y2 < 0 ||
         y1 > ROWS || y2 > ROWS ||
         x1 > COLUMS || x2 > COLUMS ||
         board.at(x1).at(y1) == EMPTY || board.at(x1).at(y1) == UNUSED ||
         board.at(x2).at(y2) != EMPTY) {
        return false;
    }
    return true;
}

// To decide go up, down, left or right
// param: integer a, b
// return: 1 or -1
int direction(int a, int b) {
    if(a < b) return 1;
    else return -1;
}

// Check horizontally left or right empty, if empty move to that empty location
// param: 3 integers
// return: boolean value
bool check_hor(int x1, int y1, int y2) {
    int dir = direction(y1, y2);
    if(board.at(x1).at(y1 + dir) != EMPTY) return false;
    else return true;
}

// After check horizotally available, move
// param: 2 integers
// return: 1 integer after changing value
int move_hor(int y1, int y2){
    return y1 + direction(y1, y2);
}

// Same thing, check vertically availability and move
// param: 3 integers
// return: boolean value
bool check_ver(int x1, int y1, int x2) {
    int dir = direction(x1, x2);
    if(board.at(x1 + dir).at(y1) != EMPTY) return false;
    else return true;
}

// param: 2 integers
// return: 1 integer after changing value
int move_ver(int x1, int x2){
    return x1 + direction(x1, x2);
}

// Check the ability to move from (x1,y1) to (x2,y2)
// param: list reference
// return: boolean value
bool move(vector< int >& command) {
    int x1 = command[1] - 1;
    int y1 = command[0] - 1;
    int x2 = command[3] - 1;
    int y2 = command[2] - 1;
    bool check = true;

    while(true) {
        if(check_hor(x1, y1, y2)) {
            y1 = move_hor(y1, y2);
        } else if(check_ver(x1, y1, x2)) {
            x1 = move_ver(x1, x2);
        } else {
            check = false;
            break;
        }
        if((x1 == x2) && (y1 == y2)) break;
    }
    return check;
}

// Check when the game is over
// param: void
// return: integer
int gameover() {
    int check = 0;

    for(unsigned int i = 0; i < 4; ++i) {
        if(board[0][i] == RED) check++;
    }

    for(unsigned int i = 0; i < 4; ++i) {
        if(board[4][i] == GREEN) check++;
    }

    return check;
}



int main()
{
    string input;
    int moves = 0;

    print(board);

    while(true) {
        cout << INPUT_TEXT;
        getline(cin, input);

        if (input == "q") {
            break;
        } else {
            input = remove_spaces(input);
            if(!stoi_with_check(input)) {
                cout << INVALID_POINT << endl;
            } else {
                vector<int> command = inputList(input);

                if(!check_input(command)) {
                    cout << INVALID_POINT << endl;
                } else {
                    if(!move(command)){
                        cout << CANNOT_MOVE << endl;
                    } else {
                        moves++;
                        board.at(command[3] - 1).at(command[2] - 1) = board.at(command[1] - 1).at(command[0] - 1);
                        board.at(command[1] - 1).at(command[0] - 1) = EMPTY;
                        print(board);
                    }
                }

            }
        }

        if(gameover() == 8) {
            cout << GAME_OVER << endl;
            break;
        }

    }
    cout << moves << MOVES_MADE << endl;
    return 0;
}
