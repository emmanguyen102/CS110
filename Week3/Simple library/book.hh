#ifndef BOOK_HH
#define BOOK_HH

#include "date.hh"
#include <string>
using namespace std;

class Book
{
public:
    Book(const string& author, const string& title);

    void loan(Date&);
    void renew();
    void give_back();
    void print() const;

private:
    string author_;
    string title_;
    Date return_date_;
    Date loan_date_;
};

#endif // BOOK_H
