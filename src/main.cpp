#include <iostream>
#include "population.h"
#include <vector>

//Main is just tests for now. Simulation logic incoming!

int main(){

  Person myPerson(1);

  std::cout << myPerson.statusToString(myPerson.getStatus()) << std::endl;

  Population myPop;

  std::cout << std::to_string(myPop.getPopulationSize()) << std::endl;

  return 0;
}
