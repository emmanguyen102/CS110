/* Luokka: Card
 * ------------
 * Kuvaa yhtä? korttia muistipelissä?.
 *
 * COMP.CS.110 K2021
 * */
//
/* Class: Card
 * -----------
 * Represents a single card in pairs (memory) game.
 *
 * COMP.CS.110 K2021
 * Program author
 * Name: Hang Nguyen
 * Student number: K429778
 * UserID: c6hgnuye
 * E-Mail: hang.t.nguyen@tuni.fi
 * */

#ifndef CARD_HH
#define CARD_HH

enum Visibility_type {OPEN, HIDDEN, EMPTY};
const char HIDDEN_CHAR = '#';
const char EMPTY_CHAR = '.';

class Card
{
public:
    // Oletusrakentaja: luo tyhjä?n kortin.
    //
    // Default constructor: creates an empty card.
    Card();

    // Rakentaja: luo piilotetun kortin, jonka kirjaimeksi tulee annettu merkki.
    //
    // Constructor: creates a hidden card with the given character.
    Card(const char c);

    // Ilmeiset setter- ja getter-metodit.
    //
    // Obvious setter and getter methods.
    void set_letter(const char c);
    void set_visibility(const Visibility_type visibility);
    char get_letter() const;
    Visibility_type get_visibility() const;

    // Kä?ä?ntä?ä? kortin: vaihtaa nä?kyvyyden avoimesta piilotettuun ja pä?in vastoin.
    //
    // Turns a card: changes the visibility from open to hidden and vice versa.
    void turn();

    // Tulostaa kortin sen tä?mä?nhetkisen tilanteen (nä?kyvyyden) mukaisesti.
    //
    // Prints a card based on its current state (visibility).
    void print() const;

    // Poistaa kortin pelilaudalta: muuttaa nä?kyvyyden tyhjä?ksi.
    //
    // Removes a card from the game board: changes the visibility to empty.
    void remove_from_game_board();

private:
    char letter_;
    Visibility_type visibility_;
};

#endif // CARD_HH
