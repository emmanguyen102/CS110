#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>

class Account
{
public:
    // Constructor
    Account(const std::string& owner, bool has_credit = false);

    // More methods
    void set_credit_limit(int credit_limit);
    void save_money(int current_money);
    void take_money(int taken_money);
    void transfer_to(Account& owner, int money);
    void print() const;

private:
    // Generates IBAN (based on running_number_ below).
    // Allows no more than 99 accounts.
    void generate_iban();

    // Used for generating IBAN.
    // Static keyword means that the value of running_number_ is the same for
    // all Account objects.
    // In other words, running_number_ is a class-wide attribute, there is
    // no own copies of it for each object of the class.
    static int running_number_;

    // More attributes/methods
    std::string iban_;
    int credit_limit_;
    int current_money_ = 0;
    std::string owner_;
    bool has_credit_;
};

#endif // ACCOUNT_HH
