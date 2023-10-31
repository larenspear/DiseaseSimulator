#ifndef POPULATION_H
#define POPULATION_H

#include "person.h"
#include <cstdint>
#include <random>
#include <vector>

class Population {
private:
  std::vector<Person> people_;
  uint32_t populationSize_;
  uint32_t numInteractions_;
  uint32_t daysSick_;
  float transmissionProb_;
  float percentVaccinated_;

public:
  Population(uint32_t populationSize_, uint32_t numInteractions_,
             float transmissionProb_, uint32_t daysSick_,
             float percentVaccinated_);

  uint32_t getRandomIndex(uint32_t upperBound) const;
  void setPopsize(uint32_t p);
  uint32_t getPopsize() const;
  void setPercentVaccinated(float v);
  float getPercentVaccinated() const;
  void setTransmissionProb(float prob);
  float getTransmissionProb() const;
  void setNumInteractions(uint32_t interactions);
  uint32_t getNumInteractions() const;
  void setDaysSick(uint32_t d);
  uint32_t getDaysSick() const;
  void printPeople() const;
  void randomInfection();
  std::vector<Person> getPeople() const;
  uint32_t countInfected() const;
  void update();
  void infectRandomPerson();
  void vaccinate();
  void loopSimulation();
};

#endif // POPULATION_H
