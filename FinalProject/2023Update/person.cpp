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

  std::string status_to_string(Status status) {
    switch (status) {
    case Status::susceptible:
      return "susceptible";
      break;
    case Status::recovered:
      return "recovered";
      break;
    case Status::vaccinated:
      return "vaccinated";
      break;
    case Status::sick:
      return "sick";
      break;
    }
  }

  void update() {

    if (status == Status::sick) {
      sick_days--;
      if (sick_days == 0) {
        status = Status::recovered;
      }
    }
  }

  void infect(int days) // infect a person for n days
  {
    if (status == Status::susceptible) {
      sick_days = days;
      status = Status::sick;
    }
  }

  bool is_stable(void) // true if once sick but has recovered
  {
    return (status == Status::recovered);
  }

  // Population methods

  void addInteractionVector(std::vector<Person> p_interactions) {
    interactions = p_interactions;
  }
};
