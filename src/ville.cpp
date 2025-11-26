#include "../include/ville/ville.hpp"
#include "../include/buildings/batiment.hpp"
#include "../include/buildings/commercial.hpp"
#include "../include/buildings/resident.hpp"
#include "../include/utils.hpp"
#include <memory>
#include <string>
#include <vector>

using namespace std;

// Constructor
Ville::Ville(const string &nom, double budget, unsigned int population,
             Resources resources, BatimentList batiments)
    : nom(nom), budget(budget), population(population), resources(resources),
      batiments(std::move(batiments)) {}


// List de batiments
// TO-DO : Need to figure out how the building are destroyed
void Ville::ajoutBatiment(BatPtr batiment) {
  batiments.push_back(std::move(batiment));
  budget -= batiment->getCost();
}
void Ville::supprimerBatiment(int id) {
  for (auto it = batiments.begin(); it != batiments.end(); ++it) {
    if ((*it)->getID() == id) {
      budget += (*it)->getCost();
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
  float PolutionTotale = 0;
  for (auto it = batiments.begin(); it != batiments.end(); ++it) {
    PolutionTotale += (*it)->getPolution();
  }
  setPopulation(PolutionTotale);
  return PolutionTotale;
}

int Ville::calculerSatisfactionTotale() {
  int satisfactionTotale = 0;
  for (auto it = batiments.begin(); it != batiments.end(); ++it) {
    satisfactionTotale += (*it)->getSatisfaction();
  }
  setSatisfaction(satisfactionTotale);
  return satisfactionTotale;
}

int Ville::calculerPopulationTotale() {
  int populationTotale = 0;
  for (auto it = batiments.begin(); it != batiments.end(); ++it) {
    if ((*it)->type == TypeBatiment::House ||
        (*it)->type == TypeBatiment::Apartment) {
      Resident *r = dynamic_cast<Resident *>(it->get());
      if (r)
        populationTotale += r->gethabitantsActuels();
    }
  }
  setPopulation(populationTotale);
  return populationTotale;
}

int Ville::calculerCapacitePopulation() {
  int capaciteTotale = 0;
  for (auto it = batiments.begin(); it != batiments.end(); ++it) {
    if ((*it)->type == TypeBatiment::House ||
        (*it)->type == TypeBatiment::Apartment) {
      Resident *r = dynamic_cast<Resident *>(it->get());
      if (r)
        capaciteTotale += r->getcapaciteHabitants();
    }
  }
  return capaciteTotale;
}

double Ville::calculerProfit() {
  double profitTotale = 0.0;
  for (auto it = batiments.begin(); it != batiments.end(); ++it) {
    Comercial *c = dynamic_cast<Comercial *>(it->get());
    if (c)
      profitTotale += c->getProfit();
  }
  return profitTotale;
}

void Ville::collectProfit() { budget += calculerProfit(); }

void Ville::updatePopulation() {
  int newPopulation = calculerSatisfactionTotale() / 2;
  int capaciteTotale = calculerCapacitePopulation();
  if (newPopulation > capaciteTotale) {
    newPopulation = capaciteTotale;
  }
  population = newPopulation;
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
