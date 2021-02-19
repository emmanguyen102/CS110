#include "player.hh"
#include "card.hh"
#include <iostream>
#include <vector>
#include <random>

using namespace std;

const string INPUT_AMOUNT_OF_CARDS = "Enter the amount of cards (an even number): ";
const string INPUT_SEED = "Enter a seed value: ";
const string INPUT_AMOUNT_OF_PLAYERS = "Enter the amount of players (one or more): ";
const string INPUT_CARDS = "Enter two cards (x1, y1, x2, y2), or q to quit: ";
const string INVALID_CARD = "Invalid card.";
const string FOUND = "Pairs found.";
const string NOT_FOUND = "Pairs not found.";
const string GIVING_UP = "Why on earth you are giving up the game?";
const string GAME_OVER = "Game over!";

using Game_row_type = vector<Card>;
using Game_board_type = vector<vector<Card>>;

// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns 0
// (which leads to an invalid card later).
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}


// Fills the game board, the size of which is rows * columns, with empty cards.
void init_with_empties(Game_board_type& g_board, unsigned int rows, unsigned int columns)
{
    g_board.clear();
    Game_row_type row;
    for(unsigned int i = 0; i < columns; ++i)
    {
        Card card;
        row.push_back(card);
    }
    for(unsigned int i = 0; i < rows; ++i)
    {
        g_board.push_back(row);
    }
}


// Finds the next free position in the game board (g_board), starting from the
// given position start and continuing from the beginning if needed.
// (Called only by the function init_with_cards.)
unsigned int next_free(Game_board_type& g_board, unsigned int start)
{
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Starting from the given value
    for(unsigned int i = start; i < rows * columns; ++i)
    {
        if(g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY) // vaihdettu
        {
            return i;
        }
    }
    // Continuing from the beginning
    for(unsigned int i = 0; i < start; ++i)
    {
        if(g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY)
        {
            return i;
        }
    }
    // You should never reach this
    std::cout << "No more empty spaces" << std::endl;
    return rows * columns - 1;
}

// Initializes the given game board (g_board) with randomly generated cards,
// based on the given seed value.
void init_with_cards(Game_board_type& g_board, int seed)
{
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Drawing a cell to be filled
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, rows * columns - 1);

    // Wiping out the first random number (that is always the lower bound of the distribution)
    distr(randomEng);

    // If the drawn cell is already filled with a card, next empty cell will be used.
    // (The next empty cell is searched for circularly, see function next_free.)
    for(unsigned int i = 0, c = 'A'; i < rows * columns - 1; i += 2, ++c)
    {
        // Adding two identical cards (pairs) in the game board
        for(unsigned int j = 0; j < 2; ++j)
        {
            unsigned int cell = distr(randomEng);
            cell = next_free(g_board, cell);
            g_board.at(cell / columns).at(cell % columns).set_letter(c);
            g_board.at(cell / columns).at(cell % columns).set_visibility(HIDDEN);
        }
    }
}

// Prints a line consisting of the given character c.
// The length of the line is given in the parameter line_length.
// (Called only by the function print.)
void print_line_with_char(char c, unsigned int line_length)
{
    for(unsigned int i = 0; i < line_length * 2 + 7; ++i)
    {
        cout << c;
    }
    cout << endl;
}

// Prints a variable-length game board with borders.
void print(const Game_board_type& g_board)
{
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    print_line_with_char('=', columns);
    cout << "|   | ";
    for(unsigned int i = 0; i < columns; ++i)
    {
        cout << i + 1 << " ";
    }
    cout << "|" << endl;
    print_line_with_char('-', columns);
    for(unsigned int i = 0; i < rows; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < columns; ++j)
        {
            g_board.at(i).at(j).print();
            cout << " ";
        }
        cout << "|" << endl;
    }
    print_line_with_char('=', columns);
}

// split the string with " " delimeter
vector<string> split(const string& s){
    vector<string> result;

    string::size_type pos = 0;
    string tmp = s;
    while (pos < tmp.size()) {
        if (tmp[pos] == ' ') {
            result.push_back(tmp.substr(0, pos));
            tmp = tmp.substr(pos + 1);
            pos = 0;
        } else {
            pos++;
        }
    }

    result.push_back(tmp);
    return result;
}

// Asks the desired product from the user, and calculates the factors of
// the product such that the factor as near to each other as possible.
void ask_product_and_calculate_factors(unsigned int& smaller_factor, unsigned int& bigger_factor)
{
    unsigned int product = 0;
    while(not (product > 0 and product % 2 == 0))
    {
        std::cout << INPUT_AMOUNT_OF_CARDS;
        string product_str = "";
        std::getline(std::cin, product_str);
        product = stoi_with_check(product_str);
    }

    for(unsigned int i = 1; i * i <= product; ++i)
    {
        if(product % i == 0)
        {
            smaller_factor = i;
        }
    }
    bigger_factor = product / smaller_factor;
}


// get amount of players for this game, at least 2 people
// should be accepted
unsigned int ask_number_of_players()
{
    unsigned int number = 0;
    string number_str = "";
    while(not (number > 1))
    {
        std::cout << INPUT_AMOUNT_OF_PLAYERS;
        std::getline(std::cin, number_str);
        number = stoi_with_check(number_str);
    }
    return number;
}

// get coordinates of player input
vector<unsigned int> get_coordinates(Player& p)
{
    vector<unsigned int> position;
    unsigned int pos= 0;
    string pos_str = "";
    std::cout << p.get_name() << ": " << INPUT_CARDS;
    std::getline(std::cin, pos_str);
    vector<string> position_str = split(pos_str);

    for (string i:position_str)
    {
        if (pos_str == "q")
        {
            break;
        }
        pos = stoi_with_check(i);
        position.push_back(pos);
    }
    return position;
}

// check conditions of coordinates according to requirements
bool check_coordinates(Game_board_type& g_board, vector<unsigned int>& position, unsigned int factor1, unsigned int factor2)
{
    bool check = true;

    if (position.at(0) > factor2 || position.at(1) > factor1 ||
        position.at(2) > factor2 || position.at(3) > factor1 ||
        position.at(0) == 0 || position.at(1) == 0 ||
        position.at(2) == 0 || position.at(3) == 0 ||
        (position.at(0) == position.at(2) && position.at(1) == position.at(3)) ||
        g_board.at(position[1] - 1).at(position[0] - 1).get_visibility() == EMPTY ||
        g_board.at(position[3] - 1).at(position[2] - 1).get_visibility() == EMPTY)
    {
        check = false;
    }
    return check;

}

//ask name string and split each name and append all names to a vector
vector<string> players_name(unsigned int number)
{
    string name = "";
    string num_str = to_string(number);
    std::cout << "List " + num_str +" players: ";
    std::getline(std::cin, name);
    vector<string> names = split(name);
    return names;
}

void one_cycle(Game_board_type& g_board, vector<unsigned int>& position, Player& p, unsigned int factor1, unsigned int factor2)
{
    position = get_coordinates(p);
    if (position.size() != 0)
    {
        bool check = check_coordinates(g_board, position, factor1, factor2);

        while (check == false)
        {
            position.clear();
            std::cout << INVALID_CARD << std::endl;
            position = get_coordinates(p);
            if (position.size() != 0)
            {
                check = check_coordinates(g_board, position, factor1, factor2);
            }
            else {break;}
        }
    }
}

bool comparison_letter(Card& a, Card& b, Player& p, unsigned int& c)
{
    bool check = true;
    if (a.get_letter() == b.get_letter())
    {
        a.remove_from_game_board();
        b.remove_from_game_board();
        p.add_card(a);
        std::cout << FOUND << std::endl;
        c += 2;
        check = true;
    }
    else
    {
        check = false;
        a.turn();
        b.turn();
        std::cout << NOT_FOUND << std::endl;
    }
    return check;
}


int main()
{
    Game_board_type game_board;
    vector<Player> players;
    unsigned int factor1 = 1;
    unsigned int factor2 = 1;
    unsigned int num = 0;
    unsigned int cards_count = 0;


    ask_product_and_calculate_factors(factor1, factor2);
    init_with_empties(game_board, factor1, factor2);

    string seed_str = "";
    std::cout << INPUT_SEED;
    std::getline(std::cin, seed_str);
    int seed = stoi_with_check(seed_str);
    init_with_cards(game_board, seed);

    // Lisä?ä? koodia
    // More code
    num = ask_number_of_players();
    vector<string> names = players_name(num);
    for (string& n:names)
    {
        players.push_back(Player(n));
    }

    print(game_board);


    while (cards_count != (factor1 * factor2))
    {
        for (Player& p:players)
        {
            while (true) {
                vector<unsigned int> position;

                one_cycle(game_board, position, p, factor1, factor2);
                if (position.size() == 0)
                {
                    std::cout << GIVING_UP << std::endl;
                    return EXIT_SUCCESS;
                }

                Card& a = game_board.at(position[1] - 1).at(position[0] - 1);
                Card& b = game_board.at(position[3] - 1).at(position[2] - 1);

                a.turn();
                b.turn();

                print(game_board);

                bool check = comparison_letter(a, b, p, cards_count);

                for (Player j:players)
                {
                    j.print();
                }
                print(game_board);

                if (!check || (cards_count == (factor1 * factor2))) {
                    break;
                } else {
                    continue;
                }
            }
            if (cards_count == (factor1 * factor2)) {
                break;
            }
        }

    }

    std::cout << "Game over!" << std::endl;

    unsigned int max_pairs = 0;
    unsigned int tie = 0;
    string max_name = "";
    for(Player& p:players)
    {
        if (p.number_of_pairs() > max_pairs)
        {
            max_pairs = p.number_of_pairs();
            max_name = p.get_name();
        }
    }

    for(Player& p:players)
    {
        if (p.number_of_pairs() == max_pairs && p.get_name() != max_name)
        {
            tie += 1;
        }
    }

    string max_pairs_str = to_string(max_pairs);
    string tie_str = to_string(tie + 1);
    if (tie == 0)
    {
        std::cout << max_name + " has won with " + max_pairs_str + " pairs." << std::endl;
    }
    else
    {
        std::cout << "Tie of " + tie_str + " players with " + max_pairs_str + " pairs." << std::endl;
    }

    return EXIT_SUCCESS;
}

