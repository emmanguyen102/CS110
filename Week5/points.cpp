#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    string input_name;
    cout << "Input file: ";
    getline(cin, input_name);

    ifstream input(input_name);

    if (!input) {
        cout << "Error! The file " << input_name << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    map<string, int> points;
    string turn;

    while ( getline(input, turn) ) {
        string name = "";
        int sandbox = 1;

        for(char& c : turn) {
            if(c == ':') break;
            name += c;
            sandbox++;
        }

        turn.erase(turn.begin(), turn.begin() + sandbox);

        int point = stoi(turn);

        if(!points[name]) points[name] = point;
        else points[name] += point;
    } input.close();

    cout << "Final scores:" << endl;
    for (auto value : points) {
        cout << value.first << ": " << value.second << endl;
    } return EXIT_SUCCESS;
}

