#ifndef PERSON_H
#define PERSON_H

#include <cstdint>
#include <vector>

enum class Status { Susceptible, Sick, Recovered, Vaccinated };

class Person {
private:
  Status status_;
  uint32_t ID_;
  uint32_t sickDays_;
  std::vector<Person> Interactions_;

public:

  Person();

  void setStatus(Status s);

  Status getStatus() const;

  uint32_t getID() const;

  void setID(uint32_t id);

  std::string statusToString(Status status);

  void update();

  void infect(uint32_t days);

  bool isStable() const;

  void addInteractionVector(std::vector<Person> p_interactions);
};

#endif // PERSON_H
