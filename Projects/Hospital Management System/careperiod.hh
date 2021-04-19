/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "person.hh"
#include "date.hh"
#include <string>
#include <set>

class CarePeriod
{
public:
    // Constructor, start date given as a string (ddmmyyyy).
    CarePeriod(const std::string& start, Person* patient);

    // Constructor, start date given as a Date object.
    CarePeriod(const Date& start, Person* patient);

    // Destructor.
    ~CarePeriod();

    // More public
    void add_end_date(const Date& end);
    void print_care_period();
    void add_staffs(const std::string& staff_id);
    bool leave_check() const;
    void print_patient_info();
    void print_patient();

private:
    Person* patient_;
    Date start_;
    Date end_;
    bool leave_ = false;

    // More attributes and methods
    std::set<std::string> staffs_;
};

#endif // CAREPERIOD_HH
