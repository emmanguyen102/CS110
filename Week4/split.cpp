#include <iostream>
#include <string>
#include <vector>

std::vector <std::string> split(const std::string& line, char separator, bool empty_string = false)
{
    std::vector<std::string> a;
    std::vector<std::string> b;
    std::string c = "";

    for (std::string::size_type i = 0; i <= line.size(); i++) {
        if (line[i] == separator || i == line.size()) {
           if (c != "") {
               a.push_back(c);
               b.push_back(c);
           } else {
               a.push_back("");
           }
           c = "";
        } else {
           c += line[i];
        }
    }

    if (!empty_string) {
       return a;
    } else {
       return b;
    }
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto o : parts ) {
        std::cout << o << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto o : parts_no_empty ) {
        std::cout << o << std::endl;
    }
}
