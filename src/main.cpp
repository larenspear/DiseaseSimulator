#include <iostream>
#include "population.h"
#include <vector>

//Main is just tests for now. Simulation logic incoming!

void body(uint32_t populationSize, uint32_t numInteractions, float transmissionProb, uint32_t daysSick, float percentVaccinated){
  
  Population population(
      populationSize, numInteractions, transmissionProb, daysSick, percentVaccinated);

  uint32_t day = 1;
  uint32_t peak = 0;

  float toVaccinate = static_cast<float>(populationSize) * population.getPercentVaccinated();

  population.vaccinate();

  while(population.countInfected() == 0){
    population.randomInfection();
  }

  while(population.countInfected() > 0){
    day++;
    population.update();
    if(population.countInfected() > peak){
      peak = population.countInfected();
    }
  }

}


int main(){

  Person myPerson(1);

  std::cout << myPerson.statusToString(myPerson.getStatus()) << std::endl;

  Population myPop;

  std::cout << std::to_string(myPop.getPopulationSize()) << std::endl;

  return 0;
}
