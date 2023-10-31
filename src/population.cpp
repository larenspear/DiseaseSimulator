#include "population.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

Population::Population(uint32_t populationSize, uint32_t numInteractions,
                       float transmissionProb, uint32_t daysSick,
                       float percentVaccinated) :
    populationSize_(populationSize),
    numInteractions_(numInteractions), transmissionProb_(transmissionProb),
    daysSick_(daysSick), percentVaccinated_(percentVaccinated) {}

uint32_t Population::getRandomIndex(uint32_t upperBound) const {
  static std::random_device rd;
  static std::mt19937 gen(rd()); // Mersenne Twister random number generator
  std::uniform_int_distribution<> dis(0, upperBound - 1);
  return dis(gen);
}
/*

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

*/

void Population::setPopsize(uint32_t p) {
  populationSize_ = p;
}

uint32_t Population::getPopsize() const {
  return populationSize_;
}

void Population::setPercentVaccinated(float v) {
  percentVaccinated_ = v;
}

float Population::getPercentVaccinated() const {
  return percentVaccinated_;
}

void Population::setTransmissionProb(float prob) {
  transmissionProb_ = prob;
}

float Population::getTransmissionProb() const {
  return transmissionProb_;
}

void Population::setNumInteractions(uint32_t interactions) {
  numInteractions_ = interactions;
}

uint32_t Population::getNumInteractions() const {
  return numInteractions_;
}

void Population::setDaysSick(uint32_t d) {
  daysSick_ = d;
}

uint32_t Population::getDaysSick() const {
  return daysSick_;
}

void Population::printPeople() const {
  for (auto &person : people_) {
    std::cout << person.getID() << "  "
              << person.statusToString(person.getStatus()) << std::endl;
  }
}

void Population::randomInfection() {
  uint32_t randomPick;
  randomPick = rand() % people_.size();
  people_[randomPick].infect(daysSick_);
}

std::vector<Person> Population::getPeople() const {
  return people_;
}

uint32_t Population::countInfected() const {
  uint32_t totalInfected = 0;
  for (auto &i : people_) {
    if (i.getStatus() == Status::Sick) {
      totalInfected = totalInfected + 1;
    }
  }
  return totalInfected;
}

void Population::update() {
  std::vector<Person> newPeopleVector;
  for (auto &i : newPeopleVector) {
    i.update();
  }
}

void Population::infectRandomPerson() {
  float badLuck = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  uint32_t unluckyPerson = rand() % people_.size();
  if (badLuck > transmissionProb_) {
    if (people_[unluckyPerson].getStatus() == Status::Susceptible) {
      people_[unluckyPerson].infect(daysSick_);
    }
  }
}

void Population::vaccinate() {
  float toVaccinate = static_cast<float>(populationSize_) * percentVaccinated_;

  uint32_t q = 0;
  while (toVaccinate > 0) {

    people_[q].setStatus(Status::Vaccinated);
    toVaccinate--;
    q++;
  }
}

void Population::loopSimulation() {
  for (auto &it : people_) {
    if (it.getStatus() == Status::Sick) {
      for (uint32_t i = 0; i < numInteractions_; i++) {
        uint32_t unluckyPerson = rand() % people_.size();
        float badLuck =
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        do {
          badLuck = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
          unluckyPerson = rand() % people_.size();
        } while (people_[unluckyPerson].getID() == it.getID());

        if (badLuck < transmissionProb_) {
          if (people_[unluckyPerson].getStatus() == Status::Susceptible) {

            people_[unluckyPerson].infect(daysSick_);
          }
        }
      }
    }
  }
}
