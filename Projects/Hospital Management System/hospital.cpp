#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <vector>

Hospital::Hospital()
{
}

Hospital::~Hospital()
{

}

void Hospital::recruit(Params params)
{
    std::string staff_id = params.at(0);
    if( staff_.find(staff_id) != staff_.end() )
    {
        std::cout << ALREADY_EXISTS << staff_id << std::endl;
        return;
    }
    Person* new_staff = new Person(staff_id);
    staff_.insert({staff_id, new_staff});
    std::cout << STAFF_RECRUITED << std::endl;
}

void Hospital::enter(Params params)
{
    std::string patient_id = params.at(0);
    if( current_patients_.find(patient_id) != current_patients_.end() )
    {
        std::cout << ALREADY_EXISTS << patient_id << std::endl;
        return;
    }
    ;
    std::vector<CarePeriod*> care_periods;
    if (away_patients_.find(patient_id) != away_patients_.end())
    {
        Person* new_patient = away_patients_.find(patient_id)->second;
        current_patients_.insert({patient_id, new_patient});
        CarePeriod* new_care_period = new CarePeriod(utils::today, new_patient);
        care_periods = care_periods_.find(patient_id)->second;
        care_periods.push_back(new_care_period);
        care_periods_.find(patient_id)->second = care_periods;
    }
    else
    {
        Person* new_patient = new Person(patient_id);
        current_patients_.insert({patient_id, new_patient});
        CarePeriod* new_care_period = new CarePeriod(utils::today, new_patient);
        care_periods.push_back(new_care_period);
        care_periods_.insert({patient_id, care_periods});
    }
    std::cout << PATIENT_ENTERED << std::endl;
}

void Hospital::leave(Params params)
{
    std::string patient_id = params.at(0);
    Person* found_patient = current_patients_.find(patient_id)->second;
    if( current_patients_.find(patient_id) == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }
    current_patients_.erase(patient_id);
    std::vector<CarePeriod*> care_periods = care_periods_.find(patient_id)->second;
    for (auto itr = care_periods.begin(); itr != care_periods.end(); ++itr)
    {
        CarePeriod* current = *itr;
        if (current->leave_check() == false)
        {
            current->add_end_date(utils::today);
            break;
        }
    }
    away_patients_.insert({patient_id, found_patient});
    std::cout << PATIENT_LEFT << std::endl;
}

void Hospital::assign_staff(Params params)
{
    std::string staff_id = params.at(0);
    std::string patient_id = params.at(1);
    if( staff_.find(staff_id) == staff_.end() )
    {
        std::cout << CANT_FIND << staff_id << std::endl;
        return;
    }
    if( current_patients_.find(patient_id) == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    std::vector<CarePeriod*> care_periods = care_periods_.find(patient_id)->second;

    if (staff_care_periods_.find(staff_id) == staff_care_periods_.end())
    {
        staff_care_periods_.insert({staff_id, care_periods});
    }
    else
    {
        std::vector<CarePeriod*> current_care_periods = staff_care_periods_.find(staff_id)->second;
        for (auto itr = care_periods.begin(); itr != care_periods.end(); ++itr)
        {
            current_care_periods.push_back(*itr);
        }
        staff_care_periods_.find(staff_id)->second = current_care_periods;
    }


    for (auto itr = care_periods.begin(); itr != care_periods.end(); ++itr)
    {
        CarePeriod* current = *itr;
        if (current->leave_check() == false )
        {
            current->add_staffs(staff_id);
        }
    }
    std::cout << STAFF_ASSIGNED << patient_id << std::endl;
}

void Hospital::add_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string strength = params.at(1);
    std::string dosage = params.at(2);
    std::string patient = params.at(3);
    if( not utils::is_numeric(strength, true) or
        not utils::is_numeric(dosage, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    std::set<std::string> medic_patients;
    if (medicines_.find(medicine) == medicines_.end())
    {
        medic_patients.insert(patient);
        medicines_.insert({medicine, medic_patients});
    }
    else
    {
        medic_patients = medicines_.find(medicine)->second;
        medic_patients.insert(patient);
        medicines_.find(medicine)->second = medic_patients;
    }
    std::cout << MEDICINE_ADDED << patient << std::endl;
}

void Hospital::remove_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->remove_medicine(medicine);

    std::set<std::string> medic_patients = medicines_.find(medicine)->second;
    medic_patients.erase(patient);
    medicines_.find(medicine)->second = medic_patients;
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}

void Hospital::print_patient_info(Params params)
{
    std::string patient_id = params.at(0);
    Person* found_person = current_patients_.find(patient_id)->second;
    if( current_patients_.find(patient_id) == current_patients_.end() )
    {
        if (away_patients_.find(patient_id) == away_patients_.end())
        {
            std::cout << CANT_FIND << patient_id << std::endl;
            return;
        }
        else
        {
            found_person = away_patients_.find(patient_id)->second;
        }
    }

    std::vector<CarePeriod*> care_periods = care_periods_.find(patient_id)->second;
    for (auto itr = care_periods.begin(); itr != care_periods.end(); ++itr)
    {
        CarePeriod* current = *itr;
        current->print_patient_info();
    }
    std::cout << "* Medicines:";
    found_person->print_medicines("  - ");
}

void Hospital::print_care_periods_per_staff(Params params)
{
    std::string staff_id = params.at(0);
    if (staff_.find(staff_id) == staff_.end())
    {
        std::cout << CANT_FIND << staff_id << std::endl;
        return;
    }
    if (staff_care_periods_.find(staff_id) == staff_care_periods_.end())
    {
        std::cout << "None" << std::endl;
        return;
    }
    std::vector<CarePeriod*> care_periods = staff_care_periods_.find(staff_id)->second;
    for (auto itr = care_periods.begin(); itr != care_periods.end(); ++itr)
    {
        CarePeriod* current = *itr;
        current->print_care_period();
        std::cout << "* Patient: ";
        current->print_patient();
        std::cout << std::endl;
    }

}

void Hospital::print_all_medicines(Params)
{
    if (medicines_.size() == 0)
    {
        std::cout << "None" << std::endl;
        return;
    }
    for (auto itr = medicines_.begin(); itr != medicines_.end(); ++itr)
    {
        std::set<std::string> patients = itr->second;
        if (patients.size() > 0)
        {
            std::cout << itr->first << " prescribed for " << std::endl;
            for (auto i = patients.begin(); i != patients.end(); ++i)
            {
                std::cout << "* " << *i << std::endl;
            }
        }

    }

}

void Hospital::print_all_staff(Params)
{
    if( staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    for( std::map<std::string, Person*>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        std::cout << iter->first << std::endl;
    }
}

void Hospital::print_all_patients(Params)
{
    if( current_patients_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    for(auto i = current_patients_.begin(); i != current_patients_.end(); ++i)
    {
        std::string patient_id = i->first;
        std::cout << patient_id << std::endl;
        std::vector<CarePeriod*> care_periods = care_periods_.find(patient_id)->second;
        for (auto itr = care_periods.begin(); itr != care_periods.end(); ++itr)
        {
            CarePeriod* current = *itr;
            current->print_patient_info();
        }
        Person* found_person = current_patients_.find(patient_id)->second;
        std::cout << "* Medicines:";
        found_person->print_medicines("  - ");
    }

    for(auto i = away_patients_.begin(); i != away_patients_.end(); ++i)
    {
        std::string patient_id = i->first;
        std::cout << patient_id << std::endl;
        std::vector<CarePeriod*> care_periods = care_periods_.find(patient_id)->second;
        for (auto itr = care_periods.begin(); itr != care_periods.end(); ++itr)
        {
            CarePeriod* current = *itr;
            current->print_patient_info();
        }
        Person* found_person;
        if (current_patients_.find(patient_id) == current_patients_.end())
        {
            found_person = current_patients_.find(patient_id)->second;
        }
        else
        {
            found_person = away_patients_.find(patient_id)->second;

        }
        std::cout << "* Medicines:";
        found_person->print_medicines("  - ");
    }



}

void Hospital::print_current_patients(Params)
{
    if( current_patients_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    for(auto i = current_patients_.begin(); i != current_patients_.end(); ++i)
    {
        std::string patient_id = i->first;
        std::cout << patient_id << std::endl;
        std::vector<CarePeriod*> care_periods = care_periods_.find(patient_id)->second;
        for (auto itr = care_periods.begin(); itr != care_periods.end(); ++itr)
        {
            CarePeriod* current = *itr;
            current->print_patient_info();
        }
        Person* found_person = current_patients_.find(patient_id)->second;
        std::cout << "* Medicines:";
        found_person->print_medicines("  - ");
    }

}

void Hospital::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not utils::is_numeric(day, false) or
        not utils::is_numeric(month, false) or
        not utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}
