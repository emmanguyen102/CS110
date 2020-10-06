#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>
#include <iostream>

using namespace std;

class Player
{
public:
    Player(const string& name);
    string get_name();
    int get_points();
    bool has_won();
    void add_points(int pts);

private:
    string name_;
    int pts_ = 0;
};

#endif
