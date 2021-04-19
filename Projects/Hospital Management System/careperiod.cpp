#include "careperiod.hh"
#include <iostream>

CarePeriod::CarePeriod(const std::string& start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::CarePeriod(const Date &start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::~CarePeriod()
{
}

void CarePeriod::add_end_date(const Date &end)
{
   end_ = end;
   leave_ = true;
}

void CarePeriod::print_care_period()
{
    start_.print();
    std::cout << " - " ;
    if (leave_)
    {
        end_.print();
    }
    std::cout << std::endl;
}

void CarePeriod::add_staffs(const std::string& staff_id)
{
    staffs_.insert(staff_id);
}

bool CarePeriod::leave_check() const
{
    if (leave_)
    {
        return true;
    }
    return false;
}

void CarePeriod::print_patient()
{
    patient_->print_id();
}

void CarePeriod::print_patient_info()
{
    std::cout << "* Care period: ";
    start_.print();
    std::cout << " - ";
    if (leave_)
    {
        end_.print();
    }
    std::cout << std::endl;
    std::cout << "  - Staff: ";
    if (staffs_.size() > 0)
    {
        for (auto itr = staffs_.begin(); itr != staffs_.end(); ++itr)
        {
            std::cout << *itr << " ";
        }
    }
    else
    {
        std::cout << "None";
    }
    std::cout << std::endl;
}
