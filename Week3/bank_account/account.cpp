#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit)
{
    has_credit_ = has_credit;
    owner_ = owner;
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));
    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::set_credit_limit(int credit_limit){
    if(has_credit_) {
        credit_limit_ = credit_limit;
    } else {
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
    }
}

void Account::save_money(int current_money){
    current_money_ += current_money;
}

void Account::take_money(int taken_money){
    if (has_credit_) {
        if(taken_money <= current_money_ + credit_limit_) {
            taken_money=current_money_ - taken_money;
            std::cout << taken_money << " euros taken: new balance of " << iban_ << " is " << current_money_ << " euros" << std::endl;
        } else {
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
        }
    }
    else {
        if(taken_money <= current_money_) {
            current_money_ -= taken_money;
            std::cout << taken_money << " euros taken: new balance of " << iban_ << " is " << current_money_ << " euros" << std::endl;
        } else {
            std::cout << "Cannot take money: balance underflow" << std::endl;
        }
    }
}

void Account::transfer_to(Account& owner, int money){
    if (has_credit_) {
        if (money <= current_money_ + credit_limit_) {
            current_money_ = current_money_ - money;
            owner.current_money_ = owner.current_money_ + money;
            std:: cout << money << " euros taken: new balance of " << iban_ << " is " << current_money_ << " euros" << std::endl;
        }
        else {
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
            std::cout << "Transfer from " << iban_ << " failed" << std::endl;
        }
    }
    else {
        if (money <= current_money_){
            current_money_ = current_money_ - money;
            owner.current_money_ = owner.current_money_ + money;
            std:: cout << money << " euros taken: new balance of " << iban_ << " is " << current_money_ << " euros" <<std::endl;
        } else {
            std::cout << "Cannot take money: balance underflow" << std::endl;
            std::cout << "Transfer from " << iban_ << " failed" << std::endl;
            }
        }
    }

void Account::print() const {
    std::cout << owner_ << " : " << iban_ << " : " << current_money_ << " euros" << std::endl;
    }
