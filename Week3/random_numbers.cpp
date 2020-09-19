#include <iostream>
#include <random>
#include <string>

using namespace std;

void produce_random_numbers(unsigned int& lower, unsigned int& upper)
{
    default_random_engine rand_gen;
    cout << "Enter a seed value or an empty line: ";
    string seed_value = "";
    getline(cin, seed_value);
    cout << "\n";

    if (seed_value == "") {
        // If the user did not give a seed value, use computer time as the seed value.
        rand_gen.seed(time(NULL));
    }
    else {
        // If the user gave a seed value, use it.
        rand_gen.seed(stoi(seed_value));
    }

    while (true) {
        uniform_int_distribution<int> distr(lower, upper);
        cout << "Your drawn random number is " << distr(rand_gen) << endl;
        cout << "Press enter to continue or q to quit: ";
        string character;
        getline(cin, character);
        if (character == "q") {
            break;
        }
        cout << "\n";
    }
}

int main()
{
    unsigned int lower_bound, upper_bound;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;

    string line_feed = "";
    getline(cin, line_feed);

    if (lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound" << endl;
        return EXIT_FAILURE;
    }

    produce_random_numbers(lower_bound, upper_bound);

    return EXIT_SUCCESS;
}
