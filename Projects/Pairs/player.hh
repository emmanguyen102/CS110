
/* Luokka: Player
 * --------------
 * Kuvaa yhtä? pelaajaa muistipelissä?.
 *
 * COMP.CS.110 K2021
 * */
//
/* Class: Player
 * -------------
 * Represents a single player in pairs (memory) game.
 *
 * COMP.CS.110 K2021
 * Program author
 * Name: Hang Nguyen
 * Student number: K429778
 * UserID: c6hgnuye
 * E-Mail: hang.t.nguyen@tuni.fi
 * */

#ifndef PLAYER_HH
#define PLAYER_HH

#include "card.hh"
#include <string>
#include <vector>

class Player
{
public:
    // Constructor: creates a player with the given name.
    Player(const std::string& name);

    // Returns the name of the player.
    std::string get_name() const;

    // Returns the number of pairs collected by the player so far.
    unsigned int number_of_pairs() const;

    // Moves the given card from the game board for the player,
    // i.e. inserts it to the collected cards of the player and
    // removes it from the game board.
    void add_card(Card& card);

    // Prints the game status of the player: name and collected pairs so far.
    void print() const;


private:
    // Add necessary attributes here
    std::string name_;
    std::vector<Card> cards_;
};

#endif // PLAYER_HH
