#ifndef POPULATION_H
#define POPULATION_H

#include "person.h"
#include <cstdint>
#include <random>
#include <vector>

class Population {
private:
  std::vector<Person> people;
  uint32_t populationSize_;
  uint32_t numInteractions_;
  uint32_t daysSick_;
  float transmissionProb_;
  float percentVaccinated_;

  uint32_t GetRandomIndex(uint32_t upperBound);

public:
  Population(uint32_t populationSize_, uint32_t numInteractions_,
             float transmissionProb_, uint32_t daysSick_,
             float percentVaccinated);

  void SetPopsize(int p);
  void SetPercentVaccinated(float v);
  float GetPercentVaccinated();
  void SetTransmission(float prob);
  uint32_t GetTransmission();
  void SetNumInteractions(int interactions);
  uint32_t GetNumInteractions();
  void SetDaysSick(int d);
  uint32_t GetDaysSick();
  void PrintPeople();
  void Random_infection();
  std::vector<Person> GetPeopleV();
  uint32_t CountInfected();
  void Update();
  void infectRandomPerson();
  void Vaccinate();
  void LoopSimulation();
};

#endif // POPULATION_H
