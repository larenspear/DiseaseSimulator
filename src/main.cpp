#include "population.h"
#include <iostream>
#include <vector>

#define POP 10
#define TP 0.01F
#define DS 5
#define PV 0.1

// Main is just tests for now. Simulation logic incoming!

void body(uint32_t populationSize, uint32_t numInteractions,
          float transmissionProb, uint32_t daysSick, float percentVaccinated) {

  Population population(populationSize, numInteractions, transmissionProb,
                        daysSick, percentVaccinated);

  uint32_t day = 1;
  uint32_t peak = 0;

  float toVaccinate =
      static_cast<float>(populationSize) * population.getPercentVaccinated();

  population.vaccinate();

  while (population.countInfected() == 0) {
    population.randomInfection();
  }

  population.createNetwork();

  while (population.countInfected() > 0) {
    day++;
    population.step();

    if (population.countInfected() > peak) {
      peak = population.countInfected();
    }
  }
}

int main() {

  Population myPop(POP, 0, TP, DS, PV);

  std::cout << "worked" << std::endl;

  uint32_t day = 1;
  uint32_t peak = 0;

  std::cout << "worked" << std::endl;

  myPop.vaccinate();

  // myPop.printPeople();

  myPop.createNetwork();

  myPop.randomInfection();

  while (myPop.countInfected() > 0) {
    myPop.step();
  }

  myPop.printPeople();

  return 0;
}
