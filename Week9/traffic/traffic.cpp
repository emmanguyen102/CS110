#include "queue.hh"
#include <iostream>


Queue::Queue(unsigned int cycle) {
    cycle_ = cycle;
}

Queue::~Queue () {

}

void Queue::enqueue(string reg) {
    if(is_green_) {
        std::cout << "GREEN: The vehicle " << reg << " need not stop to wait" << std::endl;
    } else {
        Vehicle* v = nullptr;
        v = new Vehicle();
        (*v).reg_num = reg;
        (*v).next = nullptr;

        if(!first_) {
            first_ = v;
            last_ = v;

        }

        else
        {
            (*last_).next = v;
            last_ = v;
        }
    }
}

bool Queue::check_light() {
    if(is_green_) {
        std::cout << "GREEN: ";
    } else {
        std::cout << "RED: ";
    }

    if(!first_) {
        std::cout << "No vehicles waiting in traffic lights" << std::endl;
        return false;
    }
    return true;
}

void Queue::dequeue() {

    if(Queue::check_light()) {
        unsigned int i = 0;
        std::cout << "Vehicle(s) ";
        while(i < cycle_) {
            Vehicle* token = first_;
            std::cout << (*token).reg_num << " ";

            if(!(*first_).next) {
                first_ = nullptr;
                last_ = nullptr;
                delete token;
                break;
            } else {
                first_ = (*first_).next;
                delete token;
                i++;
            }
        }
        std::cout << "can go on" << std::endl;
        is_green_ = !is_green_;
    }
}


void Queue::switch_light() {
    is_green_ = !is_green_;
    Queue::dequeue();
}

void Queue::reset_cycle(unsigned int cycle) {
    cycle_ = cycle;
}

void Queue::print() {
    if(Queue::check_light()) {
        Vehicle* token = first_;
        std::cout << "Vehicle(s) ";
        while (token != last_) {
            std::cout << (*token).reg_num << " ";
            token = (*token).next;
        }
        std::cout << (*token).reg_num << " ";
        std::cout << "waiting in traffic lights" << std::endl;
    }
}

