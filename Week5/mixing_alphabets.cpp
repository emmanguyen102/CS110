#include <iostream>
#include <string>
#include <algorithm>
#include <random>

int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;

    while (std::cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }

        std::string::size_type length = 0;
        length = word.length();

        if (length > 2) {
            std::string::iterator first_letter = word.begin();
            std::string::iterator last_letter = word.end();
            ++first_letter;
            --last_letter;
            shuffle(first_letter, last_letter, generator);
        }

        std::cout << word << std::endl;
    }
}
