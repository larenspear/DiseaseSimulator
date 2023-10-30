#ifndef PERSON_HPP
#define PERSON_HPP

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

enum class Status { susceptible, sick, recovered, vaccinated };

class Person {
private:
  Status status = Status::susceptible;
  uint32_t ID = 0;
  uint32_t sick_days = 0;
  std::vector<Person> interactions;

public:
  Person() : status(Status::susceptible) { ID++; }

  void setStatus(Status s) { status = s; }
  
  Status getStatus() const { return status; }
  
  int getID() const { return ID; }

  void setID(uint32_t id) { ID = id; }

  std::string status_to_string(Status status);

  void update();

  void infect(int days); // infect a person for n days

  bool is_stable(void); // true if once sick but has recovered

  void addInteractionVector(std::vector<Person> p_interactions);
};

#endif // PERSON_HPP

