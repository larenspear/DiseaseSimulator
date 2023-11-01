#include "population.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

Population::Population() :
    populationSize_(0),
    numInteractions_(0),
    transmissionProb_(0.0f),
    daysSick_(0),
    percentVaccinated_(0.0f)
{}

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

void Population::setPopulationSize(uint32_t p) {
  populationSize_ = p;
}

uint32_t Population::getPopulationSize() const {
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
  for (const auto &person : people_) {
    std::cout << person.getID() << "  "
              << person.statusToString(person.getStatus()) << std::endl;
  }
}

void Population::randomInfection() {
  people_[getRandomIndex(populationSize_)].infect(daysSick_);
}

const std::vector<Person>& Population::getPeople() const {
  return people_;
}

uint32_t Population::countInfected() const {
    return std::count_if(people_.begin(), people_.end(), [](const auto &person) {
        return person.getStatus() == Person::Status::Sick;
    });
}

void Population::update() {
  for (auto& person : people_) {
    person.update();
  }
}

void Population::infectRandomPerson() {
  uint32_t unluckyPerson = getRandomIndex(populationSize_);
  float badLuck = getRandomProbability();
  if (badLuck > transmissionProb_) {
    if (people_[unluckyPerson].getStatus() == Person::Status::Susceptible) {
      people_[unluckyPerson].infect(daysSick_);
    }
  }
}

void Population::vaccinate() {
  float toVaccinate = static_cast<float>(populationSize_) * percentVaccinated_;

  uint32_t q = 0;
  while (toVaccinate > 0) {
    people_[q].setStatus(Person::Status::Vaccinated);
    toVaccinate--;
    q++;
  }
}

float Population::getRandomProbability() {
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(rng);
}
