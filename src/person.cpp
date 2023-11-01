#include "person.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>

Person::Person(uint32_t ID) : ID_(ID), status_(Status::Susceptible), sickDays_(0) {}
  
Person::Status Person::getStatus() const {
  return status_;
}

void Person::setStatus(Status s) {
  status_ = s;
}

uint32_t Person::getID() const {
  return ID_;
}

std::string Person::statusToString(Status status) const {
  switch (status) {
  case Status::Susceptible: return "susceptible";
  case Status::Recovered: return "recovered";
  case Status::Vaccinated: return "vaccinated";
  case Status::Sick: return "sick";
  default: return "unknown";
  }
}

void Person::update() {

  if (status_ == Status::Sick) {
    sickDays_--;
    if (sickDays_ == 0) {
      status_ = Status::Recovered;
    }
  }
}

void Person::infect(uint32_t days) {
  if (status_ == Status::Susceptible) {
    sickDays_ = days;
    status_ = Status::Sick;
  }
}

void Person::vaccinate() {
  status_ = Status::Vaccinated;
}
