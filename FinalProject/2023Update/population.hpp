#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "person.hpp"
#include <vector>
#include <cstdint>
#include <random>

class Population {
private:
    std::vector<Person> P;
    uint32_t population_size;
    uint32_t n_interactions;
    uint32_t days_sick;
    float transmissionProb;
    float percentvaccinated;

    uint32_t getRandomIndex(uint32_t upperBound);

public:
    Population() = default;

    Population(uint32_t numPeople, uint32_t n_interactions, float transmissionProb, uint32_t days_sick, float percentvaccinated);

    void setPopsize(int p);
    void setPercentVaccinated(float v);
    float getPercentVaccinated();
    void setTransmission(float prob);
    int getTransmission();
    void setNumInteractions(int interactions);
    int getNumInteractions();
    void setDaysSick(int d);
    int getDaysSick();
    void printPeople();
    void random_infection();
    std::vector<Person> getPeopleV();
    int count_infected();
    void update();
    void infectRandom_person();
    void vaccinate();
    void loop_simulation();
};

#endif // POPULATION_HPP

