#include "person.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>

Person::Person(Status status, uint32_t ID, uint32_t SickDays,
               std::vector<Person> Interactions) :
    status_(status),
    ID_(ID), sickDays_(SickDays), interactions_(Interactions) {}

Status Person::getStatus() const {
  return status_;
}

void Person::setStatus(Status s) {
  status_ = s;
}

uint32_t Person::getID() const {
  return ID_;
}

void Person::setID(uint32_t id) {
  ID_ = id;
}

std::string Person::statusToString(Status status) const {
  switch (status) {
  case Status::Susceptible:
    return "susceptible";
    break;
  case Status::Recovered:
    return "recovered";
    break;
  case Status::Vaccinated:
    return "vaccinated";
    break;
  case Status::Sick:
    return "sick";
    break;
  default:
    return "susceptible";
    break;
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

bool Person::isStable() const { // True if sick then recovered
  return (status_ == Status::Recovered);
}
