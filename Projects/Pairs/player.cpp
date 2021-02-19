#include "player.hh"
#include <string>
#include <iostream>

Player::Player(const std::string& name):

    name_(name)
{

}

std::string Player::get_name() const
{
    return name_;
}

unsigned int Player::number_of_pairs() const
{
    return cards_.size();
}

void Player::add_card(Card& card)
{
    cards_.push_back(card);
}

void Player::print() const
{
    std::string count_str = std::to_string(cards_.size());
    std::cout << "*** " + name_ + " has " + count_str + " pair(s)." << std::endl;
}


