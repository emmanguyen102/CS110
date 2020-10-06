#include "player.hh"

Player::Player(const string& name)
{
    name_ = name;
}

string Player::get_name(){
    return name_;
}

int Player::get_points(){
    return pts_;
}

bool Player::has_won(){
    if (pts_ == 50) {
        return true;
    }
    else {
        return false;
    }
}

void Player::add_points(int pts){
    pts_ += pts;
    if (pts_ > 50){
        pts_ = 25;
        cout << name_ << " gets penalty points!" << endl;
    }
}
