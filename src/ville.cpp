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

Ville::~Ville() = default;

// List de batiments
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

// calculations
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
  
  // La pollution est affectée par les bâtiments 
  PolutionTotale *= Batiment::BUILDING_POLLUTION_FACTOR;
  
  // La population affecte aussi la pollution
  PolutionTotale += population * 0.01f;
  
  setPolution(PolutionTotale);
  return PolutionTotale;
}

int Ville::calculerSatisfactionTotale() {
  int satisfactionTotale = 0;
  for (auto it = batiments.begin(); it != batiments.end(); ++it) {
    satisfactionTotale += (*it)->getSatisfaction();
  }
  
  // La pollution réduit la satisfaction
  satisfactionTotale -= static_cast<int>(polution * Batiment::POLLUTION_SATISFACTION_FACTOR);
  
 
  if (satisfactionTotale < 0) satisfactionTotale = 0;
  if (satisfactionTotale > 100) satisfactionTotale = 100;
  
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
  //  La satisfaction affecte la population
  int capaciteTotale = calculerCapacitePopulation();
  int populationActuelle = calculerPopulationTotale();
  
  // Facteur de croissance basé sur la satisfaction
  float croissanceFacteur = 0.5f + (satisfaction / (100.0f * Batiment::SATISFACTION_POPULATION_FACTOR));
  
  // Calculer nouvelle population
  int nouvellePopulation = static_cast<int>(populationActuelle * croissanceFacteur);
  
  // Ne pas dépasser la capacité
  if (nouvellePopulation > capaciteTotale) {
    nouvellePopulation = capaciteTotale;
  }
  
  // Ne pas tomber en dessous de 0
  if (nouvellePopulation < 0) {
    nouvellePopulation = 0;
  }
  
  // Distribuer la population dans les bâtiments
  int difference = nouvellePopulation - populationActuelle;
  
  if (difference > 0) {
    for (auto it = batiments.begin(); it != batiments.end() && difference > 0; ++it) {
      if ((*it)->type == TypeBatiment::House || (*it)->type == TypeBatiment::Apartment) {
        Resident *r = dynamic_cast<Resident *>(it->get());
        if (r && r->gethabitantsActuels() < r->getcapaciteHabitants()) {
          int placesDisponibles = r->getcapaciteHabitants() - r->gethabitantsActuels();
          int ajouter = (placesDisponibles < difference) ? placesDisponibles : difference;
          r->ajouterHabitants(ajouter);
          difference -= ajouter;
        }
      }
    }
  } else if (difference < 0) {
    difference = -difference;
    for (auto it = batiments.begin(); it != batiments.end() && difference > 0; ++it) {
      if ((*it)->type == TypeBatiment::House || (*it)->type == TypeBatiment::Apartment) {
        Resident *r = dynamic_cast<Resident *>(it->get());
        if (r && r->gethabitantsActuels() > 0) {
          int habitants = r->gethabitantsActuels();
          int retirer = (habitants < difference) ? habitants : difference;
          r->retirerHabitants(retirer);
          difference -= retirer;
        }
      }
    }
  }
  
  setPopulation(nouvellePopulation);
}

// Getters
string Ville::getNom() const { return nom; }
double Ville::getBudget() const { return budget; }
float Ville::getPolution() const { return polution; }
unsigned int Ville::getPopulation() const { return population; }  
int Ville::getSatisfaction() const { return satisfaction; }
Resources Ville::getResources() const { return resources; }

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
