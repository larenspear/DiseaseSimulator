#include "person.h"
#include "population.h"
#include <fstream>
#include <iostream>
#include <random>

void body(int sickDays, int popSize, float transmissionProb,
          int numInteractions, float percentVaccinated) {

  Population myPop(
      sickDays, transmissionProb, numInteractions, sickDays,
      percentVaccinated); // population size, interactions, transmission
                          // probability, days sick, %vax
  myPop.setDaysSick(sickDays);
  myPop.setTransmissionProb(transmissionProb);
  myPop.setNumInteractions(numInteractions);
  myPop.setPopsize(popSize);
  myPop.setPercentVaccinated(percentVaccinated);

  uint32_t day = 1;
  uint32_t peak = 0;

  float toVaccinate =
      static_cast<float>(popSize) * myPop.getPercentVaccinated();

  myPop.vaccinate();

  myPop.randomInfection();

  while (myPop.countInfected() == 0) {
    myPop.randomInfection();
  }

  while (myPop.countInfected() > 0) {

    std::cout << "Day " << day << " | " << myPop.countInfected() << " sick"
              << std::endl;
    day++;
    myPop.update();
    myPop.loopSimulation();
    if (myPop.countInfected() > peak) {
      peak = myPop.countInfected();
    }
  }

  std::cout << "Day " << day << " | " << myPop.countInfected() << " sick"
            << std::endl;

  std::ofstream outfile;

  outfile.open("Output.txt", std::ios::app);
  if (!outfile.is_open()) {
    std::cerr << "Error: Could not open file for writing." << std::endl;
  }
  outfile << popSize << " " << transmissionProb << " " << numInteractions << " "
          << day << " " << peak << " " << percentVaccinated
          << std::endl; // add more stuff

  outfile.close();
  std::cout << "line written" << std::endl;
}

int main() {

  for (uint32_t j = 0; j < 5; j++) {
    for (uint32_t i = 40; i >= 5; i = i - 5) {
      body(5, 40000, 0.05, i, 0);
    }

    for (float k = 0; k <= 1.0;
         k = k + 0.1) // less than 5% of population get sick
    {
      body(5, 40000, 0.05, 40, k);
    }
  }
}
