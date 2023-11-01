#ifndef PERSON_H
#define PERSON_H

#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

class Person {
private:
  uint32_t ID_;

public:

  enum class Status { Susceptible, Sick, Recovered, Vaccinated };
  std::string statusToString(Status status) const;
  
  Status status_ = Status::Susceptible;
  uint32_t sickDays_ = 0;
  
  Person(uint32_t ID);

  void setStatus(Status s);
  Status getStatus() const;
  uint32_t getID() const;

  void update();

  void infect(uint32_t days);

  void vaccinate();
};

#endif // PERSON_H
