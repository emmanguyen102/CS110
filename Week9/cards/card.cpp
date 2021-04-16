#include "cards.hh"
#include <iostream>

using namespace std;

Cards::Cards() {
    top_ = nullptr;
}

Cards::~Cards() {
}

void Cards::add(int id) {
    Card_data* c = new Card_data{id, top_};

    if(!top_) {bottom_ = c;}
    top_ = c;
    card_size_++;
}


void Cards::print_from_top_to_bottom(std::ostream& s) {
    Card_data* token = top_;
    int i = 0;
    while(token) {
        i++;
        s << i << ": " << (*token).data << endl;
        token = (*token).next;
    }
}

bool Cards::remove(int& id) {
    if(top_) {
        Card_data* token = (*top_).next;

        id = (*top_).data;
        delete top_;
        top_ = token;
        return true;
    }
    return false;
}

bool Cards::bottom_to_top() {
    if(top_) {
        if(top_ != bottom_) {
            Card_data* token = top_;
            while((*token).next != bottom_) {
                token = (*token).next;
            }

            (*token).next = nullptr;
            (*bottom_).next = top_;
            top_ = bottom_;
            bottom_ = token;
        }
        return true;
    }
    return false;
}

bool Cards::top_to_bottom() {
    if(top_) {
        if(top_ != bottom_) {
            Card_data* token = (*top_).next;

            (*top_).next = nullptr;
            (*bottom_).next = top_;
            bottom_ = top_;
            top_ = token;
        }
        return true;
    }
    return false;
}

void Cards::recursive_print(Card_data* top, int i, std::ostream& s) {
    if((*top).next) {
        Cards::recursive_print((*top).next, i-1, s);
    }
    s << i << ": " << (*top).data << endl;
}

void Cards::print_from_bottom_to_top(std::ostream& s) {

    Cards::recursive_print(top_, card_size_, s);

}
