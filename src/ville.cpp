#include "../include/ville/ville.hpp"
#include "../include/buildings/batiment.hpp"
#include "../include/utils.hpp"
#include <memory>
#include <string>
#include <vector>

using namespace std;

Ville::Ville(const string &nom, double budget, unsigned int population,
             Resources resources, BatimentList batiments)
    : nom(nom), budget(budget), population(population), resources(resources),
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

// calculus
Resources Ville::calculerconsommationTotale() {
  Resources ConsumationTotale;
  for (auto it = batiments.begin(); it != batiments.end(); ++it) {
    ConsumationTotale += (*it)->getconsommation();
  }
  return ConsumationTotale;
}

Resources Ville::calculerResourcesTotale() {
  Resources ResourcesTotale;
  for (auto it = batiments.begin(); it != batiments.end(); ++it) {
    if ((*it)->type == TypeBatiment::PowerPlant ||
        (*it)->type == TypeBatiment::WaterTreatmentPlant) {
      ResourcesTotale += (*it)->getconsommation();
    }
  }
  setResources(resources);
  return ResourcesTotale;
}

float Ville::calculerPolutionTotale() {
  float PolutionTotale;
  for (auto it = batiments.begin(); it != batiments.end(); ++it) {
    PolutionTotale += (*it)->getPolution();
  }
  setPopulation(PolutionTotale);
  return PolutionTotale;
}

int Ville::calculerSatisfactionTotale() {
  int satisfactionTotale;
  for (auto it = batiments.begin(); it != batiments.end(); ++it) {
    satisfactionTotale += (*it)->getSatisfaction();
  }
  setSatisfaction(satisfactionTotale);
  return satisfactionTotale;
}

// Getters
string Ville::getNom() { return nom; }
double Ville::getBudget() { return budget; }
float Ville::getPolution() { return polution; }
unsigned int Ville::getPopulation() { return polution; }
int Ville::getSatisfaction() { return satisfaction; }
Resources Ville::getResources() { return resources; }

// Setters
void Ville::setBudget(double newBudget) { budget = newBudget; }
void Ville::setPopulation(unsigned int newPopulation) {
  population = newPopulation;
}
void Ville::setSatisfaction(int newSatisfaction) {
  satisfaction = newSatisfaction;
}
void Ville::setPolution(float newPolution) { polution = newPolution; }
void Ville::setResources(Resources newResources) { resources = newResources; }
