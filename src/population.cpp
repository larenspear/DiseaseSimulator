#include "person.cpp"
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

class Population {
private:
  std::vector<Person> P;
  uint32_t population_size;
  uint32_t n_interactions;
  uint32_t days_sick;
  float transmissionProb;
  float percentvaccinated;

  uint32_t getRandomIndex(uint32_t upperBound) {
    static std::random_device rd;
    static std::mt19937 gen(rd()); // Mersenne Twister random number generator
    std::uniform_int_distribution<> dis(0, upperBound - 1);

    return dis(gen);
  }

public:
  Population() = default;

  Population(
      uint32_t numPeople, uint32_t n_interactions, float transmissionProb,
      uint32_t days_sick,
      float percentvaccinated) // population size, interactions, transmission
                               // probability, days sick, %vax
  {

    std::vector<Person> SimulationPop(numPeople);
    for (uint32_t i = 0; i < numPeople; i++) {
      Person j;
      j.setStatus(Status::susceptible);
      j.setID(i);
      SimulationPop.push_back(j);
    }

    for (uint32_t i = 0; i < numPeople; ++i) {
      std::vector<Person> p_interactions;
      for (int j = 0; j < n_interactions; j++) {
        int r = 0;
        bool isUnique = false;
        do {
          r = getRandomIndex(numPeople);
          isUnique = true;
          for (const auto &p : p_interactions) {
            if (p.getID() == SimulationPop[r].getID()) {
              isUnique = false;
              break;
            }
          }
        } while (!isUnique);
        p_interactions.push_back(SimulationPop[r]);
      }
      SimulationPop[i].addInteractionVector(p_interactions);
    }
  }

  void setPopsize(int p) { population_size = p; }

  void setPercentVaccinated(float v) { percentvaccinated = v; }

  float getPercentVaccinated() { return percentvaccinated; }

  void setTransmission(float prob) { transmissionProb = prob; }

  int getTransmission() { return transmissionProb; }

  void setNumInteractions(int interactions) { n_interactions = interactions; }

  int getNumInteractions() { return n_interactions; }

  void setDaysSick(int d) { days_sick = d; }

  int getDaysSick() { return days_sick; }

  void printPeople() {
    for (auto person : P) {
      std::cout << person.getID() << "  "
                << person.status_to_string(person.getStatus()) << std::endl;
    }
  }

  void random_infection() {
    int random_pick;
    random_pick = rand() % P.size();
    P[random_pick].infect(days_sick);
  }

  std::vector<Person> getPeopleV() { return P; }

  int count_infected() {
    int total_infected = 0;
    for (auto &i : P) {
      if (i.getStatus() == Status::sick) {
        total_infected = total_infected + 1;
      }
    }
    return total_infected;
  }

  void update() {
    std::vector<Person> newPeopleVector;
    for (auto &i : P) {
      i.update();
    }
  }

  void infectRandom_person() {
    float bad_luck = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    int unlucky_person = rand() % P.size();
    if (bad_luck > transmissionProb) {
      if (P[unlucky_person].getStatus() == Status::susceptible) {
        P[unlucky_person].infect(days_sick);
      }
    }
  }

  void vaccinate() {
    float population_f = population_size;
    float to_vaccinate = population_f * percentvaccinated;

    int q = 0;
    while (to_vaccinate > 0) {

      P[q].setStatus(Status::vaccinated);
      to_vaccinate = to_vaccinate - 1;
      q++;
    }
  }

  void loop_simulation() {
    for (auto &it : P) {
      if (it.getStatus() == Status::sick) {
        for (int i = 0; i < n_interactions; i++) {
          int unlucky_person = rand() % P.size();
          float bad_luck =
              static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
          do {
            bad_luck =
                static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            unlucky_person = rand() % P.size();
          } while (P[unlucky_person].getID() == it.getID());

          if (bad_luck < transmissionProb) {
            if (P[unlucky_person].getStatus() == Status::susceptible) {

              P[unlucky_person].infect(days_sick);
            }
          }
        }
      }
    }
  }
};
