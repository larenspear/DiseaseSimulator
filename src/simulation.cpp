#include "person.hpp"
#include "population.hpp"
#include <iostream>
#include <random>

void body(int sickdays, int popsize, float transmission, int n_interactions,
          float percentvaccinated) {

  Population myPop(
      popsize, transmission, n_interactions, sickdays,
      percentvaccinated); // population size, interactions, transmission
                          // probability, days sick, %vax
  myPop.setDaysSick(sickdays);
  myPop.setTransmission(transmission);
  myPop.setNumInteractions(n_interactions);
  myPop.setPopsize(popsize);
  myPop.setPercentVaccinated(percentvaccinated);

  int day = 1;
  int peak = 0;

  float population_f = popsize;
  float to_vaccinate = population_f * myPop.getPercentVaccinated();

  myPop.vaccinate();

  myPop.random_infection();
  while (myPop.count_infected() == 0)
    myPop.random_infection();
  do {
    std::cout << "Day " << day << " | " << myPop.count_infected() << " sick"
              << std::endl;
    day++;
    myPop.update();
    myPop.loop_simulation();
    if (myPop.count_infected() > peak)
      peak = myPop.count_infected();
  } while (myPop.count_infected() > 0);

  std::cout << "Day " << day << " | " << myPop.count_infected() << " sick"
            << std::endl;
  int total_days = day;

  std::ofstream outfile;
  outfile.open("Output.txt", std::ios::app);
  outfile << popsize << " " << transmission << " " << n_interactions << " "
          << total_days << " " << peak << " " << percentvaccinated
          << std::endl; // add more stuff
  outfile.close();
  std::cout << "line written" << std::endl;
}

int main() {

  for (int j = 0; j < 5; j++) {
    for (int i = 40; i >= 5; i = i - 5) {
      body(5, 40000, 0.05, i, 0);
    }

    for (float k = 0; k <= 1.0;
         k = k + 0.1) // less than 5% of population get sick
    {
      body(5, 40000, 0.05, 40, k);
    }
  }
}
