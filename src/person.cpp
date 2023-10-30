#include "person.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>

class Person {
private:
  Status Status = Status::Susceptible;
  uint32_t ID_ = 0;
  uint32_t SickDays_ = 0;
  std::vector<Person> Interactions_;

public:
  Person() : status(Status::Susceptible);

  void setStatus(Status s) { Status_ = s; }

  Status getStatus() const { return Status_; }

  int getID() const { return ID_; }

  void setID(uint32_t id) { ID_ = id; }

  std::string statusToString(Status status) {
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
    }
  }

  void update() {

    if (status == Status::Sick) {
      SickDays_--;
      if (SickDays_ == 0) {
        status = Status::Recovered;
      }
    }
  }

  void infect(uint32_t days)
  {
    if (status == Status::Susceptible) {
      SickDays_ = days;
      Status_ = Status::Sick;
    }
  }

  bool is_stable() // true if once sick but has recovered
  {
    return (Status == Status::Recovered);
  }

  // Population methods

  void addInteractionVector(std::vector<Person> p_interactions) {
    interactions = p_interactions;
  }
};
