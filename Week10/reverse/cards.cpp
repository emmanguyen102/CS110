#include <iostream>
#include <memory>
#include "cards.hh"


Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

bool Cards::remove(int &id)
{
    if (top_ == nullptr)
    {
        return false;
    }
    std::shared_ptr<Card_data> to_be_removed = top_;
    id = to_be_removed->data;

    top_ = top_->next;
    return true;
}

void Cards::reverse()
{
    if (top_ == nullptr)
    {
        return;
    }
    std::shared_ptr<Card_data> temp = top_;
    int count = 0;
    while(temp != nullptr)
    {
        add(temp->data);
        temp = temp->next;
        count++;
    }
    temp = top_;
    for(int a = 1; a < count; a++)
    {
        temp = temp->next;
    }
    temp->next = nullptr;
}

// Tip for writing code more efficiently:
// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file cards.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in cards.cpp
