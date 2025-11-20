#ifndef VILLE
#define VILLE

#include "../utils.hpp"
#include <string>

using namespace std;

class Ville {
public:
  Ville(const string& nom, float budget, unsigned int population,
        BatimentList batiments);
  void ajoutBatiment(BatPtr batiment);
  void supprimerBatiment(int id);
  Resources calculerConsummationTotale();
  int calculerSatisfaction();

private:
  string nom;
  float budget;
  unsigned int population;
  float satisfaction;
  BatimentList batiments;
};

#endif // !VILLE
