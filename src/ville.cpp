#include "../include/ville/ville.hpp"
#include "../include/utils.hpp"
#include "../include/buildings/batiment.hpp"
#include <memory>
#include <string>
#include <vector>

using namespace std;

Ville::Ville(const string& nom, float budget, unsigned int population, BatimentList batiments)
    : nom(nom), budget(budget), population(population),
      batiments(std::move(batiments)) {}

// Using Polymorphic storage with a unique pointer to insert any sub-class of
// Batiment
void Ville::ajoutBatiment(BatPtr batiment) {
  batiments.push_back(std::move(batiment));
}
void Ville::supprimerBatiment(int id) {
  for (auto it = batiments.begin(); it != batiments.end(); ++it) {
    if ((*it)->getID() == id) {
      batiments.erase(it);
      return;
    }
  }
}
Resources Ville::calculerConsummationTotale() {
    Resources ConsumationTotale;
    for (auto it = batiments.begin(); it != batiments.end(); ++it) {
        ConsumationTotale += (*it)->getConsummation();
    }
    return ConsumationTotale;
}

int Ville::calculerSatisfaction() {
    int satisfaction;
    for (auto it = batiments.begin(); it != batiments.end(); ++it) {
        satisfaction += (*it)->getSatisfaction();
    }
    return satisfaction;
}
