#ifndef VILLE
#define VILLE

#include "../utils.hpp"
#include <string>

using namespace std;

class Ville {
public:
  Ville(const string &nom, float budget, unsigned int population,
        Resources resources, BatimentList batiments);
  void ajoutBatiment(BatPtr batiment);
  void supprimerBatiment(int id);
  Resources calculerConsummationTotale();
  Resources calculerResourcesTotale();
  float calculerPolutionTotale();
  int calculerSatisfactionTotale();

  // Getters
  string getNom();
  float getBudget();
  unsigned int getPopulation();
  int getSatisfaction();
  float getPolution();
  Resources getResources();

  // Setters
  void setBudget(float newBudget);
  void setPopulation(unsigned int newPopulation);
  void setSatisfaction(int newSatisfaction);
  void setPolution(float newPolution);
  void setResources(Resources newResources);

private:
  string nom;
  float budget;
  unsigned int population;
  int satisfaction;
  float polution;
  Resources resources;
  BatimentList batiments;
};

#endif // !VILLE
