#ifndef VILLE
#define VILLE

#include "../utils.hpp"
#include <string>

using namespace std;

class Batiment;

class Ville {
public:
  Ville(const string &nom, double budget, unsigned int population,
        Resources resources, BatimentList batiments);
  ~Ville();

  Ville(const Ville &) = delete;
  Ville &operator=(const Ville &) = delete;

  // Enable move
  Ville(Ville &&) = default;
  Ville &operator=(Ville &&) = default;

  void ajoutBatiment(BatPtr batiment);
  void supprimerBatiment(int x, int y);
  Resources calculerconsommationTotale();
  Resources calculerResourcesTotale();
  // Total resource production from infrastructure plants
  Resources calculerProductionTotale() const;
  float calculerPolutionTotale();
  int calculerSatisfactionTotale();
  // Employment
  unsigned int calculerCapaciteEmploi() const;
  unsigned int calculerEmploiActuel() const;
  float calculerTauxChomage() const;
  void assignerEmplois(); // Distribute population to jobs
  void afficherStatutEmploi() const; // Display job status per building
  int calculerPopulationTotale() const;
  int calculerCapacitePopulation() const;
  double calculerProfit();
  void collectProfit();
  void updatePopulation();

  // Getters
  string getNom() const;
  double getBudget() const;
  unsigned int getPopulation() const;
  int getSatisfaction() const;
  float getPolution() const;
  Resources getResources() const;
  // Utilities availability (0..1)
  float getWaterAvailability() const;
  float getPowerAvailability() const;
  Batiment* getBatimentByPos(int x, int y) const;

  // Setters
  void setBudget(double newBudget);
  void setPopulation(unsigned int newPopulation);
  void setSatisfaction(int newSatisfaction);
  void setPolution(float newPolution);
  void setResources(Resources newResources);
  void setWaterAvailability(float value);
  void setPowerAvailability(float value);


  BatimentList batiments;
private:
  string nom;
  double budget;
  unsigned int population;
  int satisfaction;
  float polution;
  Resources resources;
  // Cached utility availability for gameplay penalties
  float waterAvailability = 1.0f;
  float powerAvailability = 1.0f;
};

#endif // !VILLE
