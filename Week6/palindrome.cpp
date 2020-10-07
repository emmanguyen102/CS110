#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool isPal(std::string s, int a, int b) {
    if (a==b) return true;
    if (s[a] != s[b]) return false;
    if (a<b+1) return isPal(s, a+1, b-1);
    return true;
}

bool palindrome_recursive(std::string s)
{
    RECURSIVE_FUNC
    unsigned int n =  s.size();
    if (n == 0) return true;
    return isPal(s, 0, n-1);
}

#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
