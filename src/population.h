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
  Population();

  Population(uint32_t populationSize, uint32_t numInteractions,
             float transmissionProb, uint32_t daysSick,
             float percentVaccinated);

  uint32_t getRandomIndex(uint32_t upperBound) const;

  float getRandomProbability();

  void setPopulationSize(uint32_t p);

  uint32_t getPopulationSize() const;

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

  const std::vector<Person> &getPeople() const;

  uint32_t countInfected() const;

  void update();

  void step();

  void infectRandomPerson();

  void interact(Person &person1, Person *person2);

  void vaccinate();

  void createNetwork();

  void loopSimulation();
};

#endif // POPULATION_H
