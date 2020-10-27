#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>

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

// create a set of name, theme, enrollment for education center
struct Course
{
    string name;
    string theme;
    int enrollment;
};

// print the location in sorted order
void print_location(set<string> locations)
{
    for (auto i=locations.begin(); i!=locations.end(); ++i)
        cout << *i << endl;
}


// print courses according to location and theme, sorted order
void print_courses(string& a, string& b, multimap <string, Course> locationTree)
{
    multiset<pair<string, int>> courses;
    auto range = locationTree.equal_range(a);

    for (auto i = range.first; i != range.second; ++i)
    {
        if (i -> second.theme == b)
        {
            courses.insert( pair<string,int>(i->second.name, i->second.enrollment));
        }
    }

    for (auto itr = courses.begin(); itr != courses.end(); ++itr)
    {
        if (itr -> second == 50)
            cout << itr->first << " --- full" << endl;
        else
            cout << itr->first << " --- " << itr->second << " enrollments" << endl;
    }
}

// print all available courses in sorted order: location, then theme then courses
void print_available_courses(set<string> locations, multimap<string, Course> locationTree)
{
    for (auto i=locations.begin(); i!=locations.end(); ++i)
    {
        multiset<pair<string, string>> themecourses;
        set<string> courses;
        auto range = locationTree.equal_range(*i);

        for (auto j = range.first; j != range.second; ++j)
        {
            if (j -> second.enrollment != 50 && courses.find(j->second.name) == courses.end())
            {
                themecourses.insert( pair<string,string>(j->second.theme, j->second.name));
                courses.insert(j->second.name);
            }
        }

        for (auto itr = themecourses.begin(); itr != themecourses.end(); ++itr) {
            cout << *i << " : " << itr->first << " : " << itr->second << endl;
        }
    }
}


// print all courses belonging to chosen theme
void print_courses_in_theme(string& key, multimap <string, Course> themeTree)
{

    set <string> courses;
    auto range = themeTree.equal_range(key);

    for (auto i = range.first; i != range.second; ++i)
    {
        courses.insert(i->second.name);
    }

    for (auto it=courses.begin(); it!=courses.end(); ++it)
        cout << *it << endl;
}

// print the sum enrollment
int print_max(string& key, multimap <string, Course> themeTree)
{
    auto range = themeTree.equal_range(key);
    int sum = 0;

    for (auto i = range.first; i != range.second; ++i)
    {
        sum += i->second.enrollment;
    }
    return sum;
}

int main()
{
    string input_name;
    cout << "Input file: ";
    getline(cin, input_name);
    ifstream input(input_name);

    if (!input)
    {
        cout << "Error: the input file cannot be opened" << endl;
        return EXIT_FAILURE;
    }

    // Processing the input file
    string myText;

    // initialize multimap to be used in functions
    multimap <string, Course> themeTree;
    multimap <string, Course> locationTree;

    while (getline (input, myText)) {

        vector<string> lists = split(myText, ';', true);

        // the line does not have 4 fields will raise an error
        if (lists.size() != 4)
        {
            cout << "Error: empty field" << endl;
            return EXIT_FAILURE;
        }

        string location = lists.at(0);
        string name = lists.at(2);
        string theme = lists.at(1);

        if (lists.at(3) == "full") lists.at(3) = "50";

        int enrollment = stoi(lists.at(3));

        struct Course course = {name, theme, enrollment};

        locationTree.insert( pair<string, Course> (location, course) );

        themeTree.insert( pair <string, Course>(theme, course) );
    }

    // create sets
    set<string> themes;
    set<string> locations;

    for (auto i = themeTree.begin(); i != themeTree.end(); ++i)
    {
        themes.insert(i->first);
    }

    for (auto i = locationTree.begin(); i != locationTree.end(); ++i)
    {
        locations.insert(i->first);
    }

    // Processing the command lines
    while (true){
        string line;
        cout << "> ";
        getline(cin, line);
        vector<string> parts = split(line, ' ', true);
        string command = parts.at(0);

        if(command == "locations")
        {
            print_location(locations);
        }

        else if (command == "courses")
        {
            if (parts.size() !=3)
            {
                cout << " Error: error in command courses" << endl;
            }
            else if (locations.find(parts.at(1)) == locations.end())
            {
                cout << "Error: unknown location name" << endl;
            }
            else if (themes.find(parts.at(2)) == themes.end())
            {
                cout << "Error: unknown theme" << endl;
            }
            else
            {
                print_courses(parts.at(1), parts.at(2), locationTree);
            }
        }

        else if (command =="available")
        {
            print_available_courses(locations, locationTree);
        }

        else if (command == "courses_in_theme")
        {
            if(themes.find(parts.at(1)) == themes.end())
            {
                cout << "Error: unknown theme" << endl;
            }
            else
            {
                print_courses_in_theme(parts.at(1), themeTree);
            }
        }

        else if (command == "favorite_theme")
            {
            int b = 0;
            vector<string> c;

            if (locationTree.empty())
            {
                cout << "No enrollments" << endl;
            }
            else
            {
                for (auto it=themes.begin(); it!=themes.end(); ++it)
                {
                    string a = *it;

                    if (b == print_max(a, themeTree))
                    {
                        c.push_back(a);
                    }

                    else if (b < print_max(a, themeTree))
                    {
                        c.clear();
                        b = print_max(a, themeTree);
                        c.push_back(a);
                    }
                }

                cout << b << " enrollments in themes" << endl;

                for(string &x : c)
                {
                    cout << "--- " << x << endl;
                }
            }


        }
        else if (command == "quit")
        {
            return EXIT_SUCCESS;
        }
        else
        {
            cout << "Error: Unknown command: " << command << endl;
        }
    }

    input.close();
}
