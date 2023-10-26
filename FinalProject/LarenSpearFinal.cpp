#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ofstream;
using std::ios;

// I'm sorry my code is ugly

class Person {
private:
  int status;
  int ID;
  vector<Person> interactions;

public:
  // constructors etc

  Person() { status = 0; }

  void setID(int d) { ID = d; }

  int getID() { return ID; }

  void setStatus(int s) { status = s; }

  int getStatus() { return status; }

  string status_string() // healthy unvaccinated = 0, recovered = -1, vaccinated
                         // = -2, sick n days to recovery
  {
    if (status == 0) {
      return "susceptible";
    } else if (status == -1) {
      return "recovered";
    } else if (status == -2) {
      return "vaccinated";
    } else {
      return "sick (" + std::to_string(status) + " to go)";
    }
  }

  void update() {
    if (status > 0) {
      status = status - 1;
      if (status == 0) // no reinfection
      {
        status = -1;
      }
    }
  }

  int infect(int n) // infect a person for n days
  {
    if (status < 0)
      return 0;
    else
      status = n;
    return 1;
  }

  bool is_stable() // true if once sick but has recovered
  {

    if (status == -1 || status == -2)
      return true;
    else
      return false;
  }

  // Population methods

  void addInteractionVector(vector<Person> p_interactions) {
    interactions = p_interactions;
  }
};

class Population {
private:
  vector<Person> P;
  int population_size;
  int n_interactions;
  int days_sick;
  float transmission;
  float percentvaccinated;

public:
  Population() {}

  Population(
      int x, int n_interactions, float transmission, int days_sick,
      float percentvaccinated) // population size, interactions, transmission
                               // probability, days sick, %vax
  {
    for (int i = 0; i < x; i++) {
      Person j;
      j.setStatus(0);
      j.setID(i);
      P.push_back(j);
    }

    for (int j = 0; j < x; j++) {
      vector<Person> p_interactions;
      for (int i = 0; i < n_interactions; i++) {
        int r = rand() % x;
        for (auto p : p_interactions) {
          while (p.getStatus() == r) {
            r = rand() % x;
          }
        }
        p_interactions.push_back(P[r]);
      }
      P[j].addInteractionVector(p_interactions);
    }
  }

  void setPopsize(int p) { population_size = p; }

  void setPercentVaccinated(float v) { percentvaccinated = v; }

  float getPercentVaccinated() { return percentvaccinated; }

  void setTransmission(float prob) { transmission = prob; }

  int getTransmission() { return transmission; }

  void setNumInteractions(int interactions) { n_interactions = interactions; }

  int getNumInteractions() { return n_interactions; }

  void setDaysSick(int d) { days_sick = d; }

  int getDaysSick() { return days_sick; }

  void printPeople() {
    for (auto person : P) {
      cout << person.getID() << "  " << person.getStatus() << endl;
    }
  }

  void random_infection() {
    int random_pick;
    random_pick = rand() % P.size();
    P[random_pick].infect(days_sick);
  }

  vector<Person> getPeopleV() { return P; }

  int count_infected() {
    int total_infected = 0;
    for (int k = 0; k < P.size(); k++) {
      if (P[k].getStatus() > 0) {
        total_infected = total_infected + 1;
      }
    }
    return total_infected;
  }

  void update() {
    vector<Person> newPeopleVector;
    for (auto &i : P) {
      i.update();
    }
  }

  void infectRandom_person() {
    float bad_luck = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    int unlucky_person = rand() % P.size();
    if (bad_luck > transmission) {
      if (P[unlucky_person].getStatus() == 0) {
        P[unlucky_person].infect(days_sick);
      }
    }
  }

  void vaccinate() {
    float population_f = population_size;
    float to_vaccinate = population_f * percentvaccinated;

    int q = 0;
    while (to_vaccinate > 0) {

      P[q].setStatus(-2);
      to_vaccinate = to_vaccinate - 1;
      q++;
    }
  }

  void loop_simulation() {
    for (auto &it : P) {
      if (it.getStatus() > 0) {
        for (int i = 0; i < n_interactions; i++) {
          int unlucky_person = rand() % P.size();
          float bad_luck = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
          do {
            bad_luck = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            unlucky_person = rand() % P.size();
          } while (P[unlucky_person].getID() == it.getID());

          if (bad_luck < transmission) {
            if (P[unlucky_person].getStatus() == 0) {

              P[unlucky_person].infect(days_sick);
            }
          }
        }
      }
    }
  }
};

void body(int sickdays, int popsize, float transmission, int n_interactions,
         float percentvaccinated) {
  //    Person joe;
  //    int step = 1;
  //    for (int step = 1 ; step < 1000 ; step++)
  //    {
  //        joe.update();
  //        float bad_luck = (float) rand() / (float)RAND_MAX;
  //        if (bad_luck > 0.90)
  //        {
  //            joe.infect(5);
  //        }
  //        cout << "On day " << step << ", Joe is " << joe.status_string() <<
  //        endl; if(joe.is_stable())
  //        {
  //            break;
  //        }
  //    }
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
    cout << "Day " << day << " | " << myPop.count_infected() << " sick" << endl;
    day++;
    myPop.update();
    myPop.loop_simulation();
    if (myPop.count_infected() > peak)
      peak = myPop.count_infected();
  } while (myPop.count_infected() > 0);

  cout << "Day " << day << " | " << myPop.count_infected() << " sick" << endl;
  int total_days = day;

  ofstream outfile;
  outfile.open("Output.txt", ios::app);
  outfile << popsize << " " << transmission << " " << n_interactions << " "
          << total_days << " " << peak << " " << percentvaccinated
          << endl; // add more stuff
  outfile.close();
  cout << "line written" << endl;
}

int main() {
  srand(static_cast<unsigned>(time(NULL)));
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
