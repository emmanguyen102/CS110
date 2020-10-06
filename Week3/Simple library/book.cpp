#include "book.hh"
#include "date.hh"
#include <iostream>

using namespace std;

Book::Book(const string& author, const string& title)
{
    author_ = author;
    title_ = title;
}

void Book::loan(Date& date)
{
    if(loan_date_.get_year() == 1) {
        loan_date_ = date;
        return_date_ = loan_date_;
        return_date_.advance(28);
    } else {
        cout << "Already loaned: cannot be loaned" << endl;
    }
}

void Book::renew()
{
    if(loan_date_.get_year() != 1) {
        return_date_.advance(28);
    } else {
        cout << "Not loanded: cannot be renewed" << endl;
    }
}

void Book::give_back()
{
    if(loan_date_.get_year() != 1) {
        loan_date_ = Date(1, 1, 1);
        return_date_ = Date(1, 1, 1);
    } else {
        cout << "Not loanded: cannot be returned" << endl;
    }
}

void Book::print() const
{
    cout << author_ << " : " << title_ << endl;
    if(loan_date_.get_year() == 1) {
        cout << "- available" << endl;
    } else {
        cout << "- loaned: ";
        loan_date_.print();
        cout << "- to be returned: ";
        return_date_.print();
    }
}
