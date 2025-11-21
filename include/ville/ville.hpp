#ifndef VILLE
#define VILLE

#include "../utils.hpp"
#include <string>

using namespace std;

class Ville {
public:
  Ville(const string& nom, float budget, unsigned int population, float satisfaction, float polution,
        BatimentList batiments);
  void ajoutBatiment(BatPtr batiment);
  void supprimerBatiment(int id);
  Resources calculerConsummationTotale();
  int calculerSatisfaction();

  // Getters  
  string getNom();
  float getBudget();
  unsigned int getPopulation();
  float getSatisfaction();
  float getPolution();

  // Setters
  void setBudget(float newBudget);
  void setPopulation(unsigned int newPopulation);
  void setSatisfaction(int newSatisfaction);
  void setPolution(float newPolution);

private:
  string nom;
  float budget;
  unsigned int population;
  int satisfaction;
  float polution;
  BatimentList batiments;
};

#endif // !VILLE
