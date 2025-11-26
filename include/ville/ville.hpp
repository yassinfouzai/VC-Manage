#ifndef VILLE
#define VILLE

#include "../utils.hpp"
#include <string>

using namespace std;

class Ville {
public:
  Ville(const string &nom, double budget, unsigned int population,
        Resources resources, BatimentList batiments);
  void ajoutBatiment(BatPtr batiment);
  void supprimerBatiment(int id);
  Resources calculerconsommationTotale();
  Resources calculerResourcesTotale();
  float calculerPolutionTotale();
  int calculerSatisfactionTotale();
  int calculerPopulationTotale();
  int calculerCapacitePopulation();
  double calculerProfit();
  void collectProfit();
  void updatePopulation();

  // Getters
  string getNom();
  double getBudget();
  unsigned int getPopulation();
  int getSatisfaction();
  float getPolution();
  Resources getResources();

  // Setters
  void setBudget(double newBudget);
  void setPopulation(unsigned int newPopulation);
  void setSatisfaction(int newSatisfaction);
  void setPolution(float newPolution);
  void setResources(Resources newResources);

private:
  string nom;
  double budget;
  unsigned int population;
  int satisfaction;
  float polution;
  Resources resources;
  BatimentList batiments;
  BatimentList newBatiments;
};

#endif // !VILLE
