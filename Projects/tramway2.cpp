#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

// split the string with either " or constant delimter to formatted string
vector<string> split(const string& s, const char delimiter, bool ignore_empty = false){
    vector<std::string> result;
    string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        char c = delimiter;
        if(tmp.find('"') == 0)
        {
            tmp = tmp.substr(1, tmp.size());
            c = '"';
        }
        string new_part = tmp.substr(0, tmp.find(c));
        tmp = tmp.substr(tmp.find(c)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

// The most magnificent function in this whole program.
// Prints a RASSE
void print_rasse()
{
    std::cout <<
                 "=====//==================//===\n"
                 "  __<<__________________<<__   \n"
                 " | ____ ____ ____ ____ ____ |  \n"
                 " | |  | |  | |  | |  | |  | |  \n"
                 " |_|__|_|__|_|__|_|__|_|__|_|  \n"
                 ".|                  RASSE   |. \n"
                 ":|__________________________|: \n"
                 "___(o)(o)___(o)(o)___(o)(o)____\n"
                 "-------------------------------" << std::endl;
}

// construct a custom data structure
struct Tram
{
    string line;
    string stop;
    double distance;
};

// print lines in alphabetical order
void print_lines(set<string>& a)
{
    for (auto i=a.begin(); i!=a.end(); ++i)
        cout << *i << endl;
}

// print stops by given line
void print_stops_in_line(string& a, multimap <string, Tram>& lines)
{
    map<double, string> map1;
    auto range = lines.equal_range(a);

    for (auto i = range.first; i != range.second; ++i)
    {
        if (i -> second.line == a)
        {
            map1.insert(pair<double, string> (i->second.distance, i ->second.stop));
        }
    }

    for (auto it = map1.begin(); it != map1.end(); it++)
    {
        cout << " - " + it -> second << " : " << it -> first << endl;
    }
}

// print line(s) by given stop
void print_line_by_stop(string& a, multimap<string, Tram>& b)
{
    set <string> lines;
    auto range = b.equal_range(a);
    for (auto i = range.first; i != range.second; ++i)
    {
        if (i -> second.stop == a)
        {
            lines.insert(i->second.line);
        }
    }
    for (auto it=lines.begin(); it!=lines.end(); ++it)
        cout << "- " + *it << endl;
}

// add a line to data structure
void add_line(string& a, set<string>& b)
{
    b.insert(a);
    cout << "Line was added." << endl;
}

// estimate the distance between 2 stops of the same line
double calculate_distance(string& a, string& b, string& c, multimap<string, Tram>& d)
{
    auto range = d.equal_range(a);
    double distance1 = 0.0;
    double distance2 = 0.0;
    for (auto i = range.first; i != range.second; ++i)
    {
        if (i -> first == a)
        {
            if (i -> second.stop == b)
            {
                distance1 = i -> second.distance;
            }
            if (i -> second.stop == c)
            {
                distance2 = i -> second.distance;
            }
        }
    }
    return abs(double(distance1 - distance2));
}

// add a stop to the several data structures so that it can automatically change with other command
string add_stop(string& a, string& b, string& c, multimap<string, Tram>& d, set<string>& lines, multimap<string, Tram>& m2, set<string>& stops)
{
    string error = "Error: Stop/line already exists.";
    string success = "Stop was added.";
    auto range = d.equal_range(a);
    double num = stod(c);
    for (auto i = range.first; i != range.second; ++i)
    {
        if (i -> first == a)
        {
            if (i -> second.stop == b)
            {
                return error;
            }
            else if (i -> second.distance == num)
            {
                return error;
            }
        }
    }
    struct Tram tram = {a, b, num};
    d.insert(pair <string, Tram> (a, tram));
    m2.insert(pair<string, Tram> (b, tram));
    stops.insert(b);
    lines.insert(a);

    return success;
}

// remove a stop from all lines
void remove_stop(string& a, multimap<string, Tram>& stops, set<string>& c, multimap<string, Tram>& lineTree)
{
    c.erase(a);
    auto range = stops.equal_range(a);
    for (auto i = range.first; i != range.second;i++)
    {
        // removes stop
        if (i->first == a) {
            stops.erase(i);
            break;
        }
    }

    vector<multimap<string, Tram>::iterator> lines;
    for (auto itr = lineTree.begin(); itr != lineTree.end(); itr++) {
        if (itr->second.stop == a) {
            lines.push_back(itr);
        }
    }
    
    for (auto it = lines.begin(); it != lines.end(); it++) {
        lineTree.erase(*it);
    }
}

// Short and sweet main.
int main()
{
    multimap <string, Tram> lineTree;
    multimap <string, Tram> stopTree;
    double num = 0.0;
    // print tramway
    print_rasse();

    // read input file
    string input_name;
    cout << "Give a name for input file: ";
    getline(cin, input_name);
    ifstream input(input_name);

    if (!input)
    {
        cout << "Error: File could not be read." << endl;
        return EXIT_FAILURE;
    }

    // Processing the input file
    string myText;

    while (getline (input, myText))
    {
        vector<string> lists = split(myText, ';', true);

        // the line does not have 4 fields will raise an error
        if (lists.size() > 3 || lists.size() < 2)
        {
            cout << "Error: Invalid format in file." << endl;
            return EXIT_FAILURE;
        }

        string line = lists.at(0);
        string stop = lists.at(1);

        if (lists.size() == 2) lists.push_back("0");
        if (lists.at(2) == "") lists.at(2) = "0";

        double distance = stod(lists.at(2));

        struct Tram tram = {line, stop, distance};

        // put values to multimap
        lineTree.insert( pair<string, Tram> (line, tram) );
        stopTree.insert( pair<string, Tram> (stop, tram) );

    }

    set<string> lines;
    set<string> stops;

    // put all lines and stops to set for further usage of command input by user
    for (auto i = lineTree.begin(); i != lineTree.end(); ++i)
    {
        lines.insert(i->first);
    }

    for (auto i = stopTree.begin(); i != stopTree.end(); ++i)
    {
        stops.insert(i->first);
    }

    while (true){
        string line;
        cout << "tramway> ";
        getline(cin, line);
        vector<string> parts = split(line, ' ', true);
        string command = parts.at(0);
        std::for_each(command.begin(), command.end(), [](char & c)
        {
            c = ::toupper(c);
        });

        if(command == "LINES")
        {
            cout << "All tramlines in alphabetical order:" << endl;
            print_lines(lines);
        }
        else if (command == "STOPS")
        {
            cout << "All stops in alphabetical order:" << endl;
            print_lines(stops);
        }
        else if (command == "LINE")
        {
            if(parts.size() == 1) cout << "Error: Invalid input." << endl;
            else if(lines.find(parts.at(1))== lines.end())
            {
                cout << "Error: Line could not be found." << endl;
            }
            else
            {
                cout << "Line " + parts.at(1) +" goes through these stops in the order they are listed:" << endl;
                print_stops_in_line(parts.at(1), lineTree);
            }
        }
        else if (command == "STOP")
        {
            if(parts.size() == 1) cout << "Error: Invalid input." << endl;
            else
            {
                string str = parts.at(1);
                str.erase(std::remove(str.begin(),str.end(),'\"'),str.end());
                if(stops.find(str) == stops.end())
                {
                    cout << "Error: Stop could not be found." << endl;
                }
                else
                {
                    cout << "Stop " + str +" can be found on the following lines:" << endl;
                    print_line_by_stop(str, stopTree);
                }
            }
        }
        else if (command == "ADDLINE")
        {
            if(parts.size() == 1) cout << "Error: Invalid input." << endl;
            else if(lines.find(parts.at(1)) != lines.end())
            {
                cout << "Error: Stop/line already exists." << endl;
            }
            else
            {
                add_line(parts.at(1), lines);
            }
        }
        else if (command == "DISTANCE")
        {
            if (parts.size() != 4) cout << "Error: Invalid input." << endl;
            else
            {
                string str1 = parts.at(2);
                string str2 = parts.at(3);

                // remove double quote from the string input for further process
                str1.erase(std::remove(str1.begin(),str1.end(),'\"'),str1.end());
                str2.erase(std::remove(str2.begin(),str2.end(),'\"'),str2.end());

                if(lines.find(parts.at(1)) == lines.end())
                {
                    cout << "Error: Line could not be found." << endl;
                }
                else if (stops.find(str2) == stops.end() || stops.find(str1) == stops.end())
                {
                    cout << "Error: Stop could not be found." << endl;
                }
                else
                {
                    num = calculate_distance(parts.at(1), str1, str2, lineTree);
                    cout << "Distance between " + str1 + " and " + str2 + " is " + to_string(num) << endl;
                }
            }
        }
        else if (command == "ADDSTOP")
        {
            if(parts.size() != 4) cout << "Error: Invalid input." << endl;
            else
            {
                string str = parts.at(2);
                str.erase(std::remove(str.begin(),str.end(),'\"'),str.end());
                if(lines.find(parts.at(1)) == lines.end())
                {
                    cout << "Error: Line could not be found." << endl;
                }
                else
                {
                    if (stops.find(str) != stops.end())
                    {
                    cout << "Error: Stop/line already exists." << endl;
                    }
                    else
                    {
                        string result = add_stop(parts.at(1), str, parts.at(3), lineTree, lines, stopTree, stops);
                        cout << result << endl;
                    }
                }
            }
        }
        else if (command == "REMOVE")
        {
            if(parts.size() != 2) cout << "Error: Invalid input." << endl;
            else
            {
                string str = parts.at(1);
                str.erase(std::remove(str.begin(),str.end(),'\"'),str.end());
                if(stops.find(str) == stops.end())
                {
                    cout << "Error: Stop could not be found." << endl;
                }
                else
                {
                    remove_stop(str, stopTree, stops, lineTree);
                    cout << "Stop was removed from all lines." << endl;
                }
            }
        }
        else if (command == "QUIT")
        {
            return EXIT_SUCCESS;
        }
        else
        {
            cout << "Error: Invalid input." << endl;
        }
    }

    input.close();
    return EXIT_SUCCESS;
}

