#include "../../include/buildings/resident.hpp"

#include <iostream>
#include <string>

using namespace std;

// Constructor
Resident::Resident(int id, const std::string &nom, Ville *ville,
                   TypeBatiment type, int effectSatisfication, double cost,
                   double consommationEau, double consommationElectricite,
                   float polution, int x, int y, int largeur, int longeur,
                   int capaciteHabitants, int habitantsActuels)
    : capaciteHabitants(capaciteHabitants), habitantsActuels(habitantsActuels),
      Batiment(id, nom, ville, type, effectSatisfication, cost, consommationEau,
               consommationElectricite, polution, x, y, largeur, longeur) {}

Resident::Resident(int id, const std::string &nom, Ville *ville,
                   TypeBatiment type, int effectSatisfication, double cost,
                   Resources consommation, float polution, Position position,
                   Surface surface, int capaciteHabitants, int habitantsActuels)
    : capaciteHabitants(capaciteHabitants), habitantsActuels(habitantsActuels),
      Batiment(id, nom, ville, type, effectSatisfication, cost, consommation,
               polution, position, surface) {}

// Methods
void Resident::afficheDetails() const {
  Batiment::afficheDetails();
  std::cout << "Habitants Actuels :\t" << habitantsActuels << endl;
  std::cout << "Capacite Habitants :\t" << capaciteHabitants << endl;
}

void Resident::ajouterHabitants(int nombreHabitants) {
  habitantsActuels += nombreHabitants;
  if (habitantsActuels >= capaciteHabitants)
    habitantsActuels = capaciteHabitants;
}

void Resident::retirerHabitants(int nombreHabitants) {
  if (nombreHabitants >= habitantsActuels)
    habitantsActuels = 0;
  else
    habitantsActuels -= nombreHabitants;
}

Resident Resident::createHouse(int id, const string &nom, Ville *ville, int x,
                               int y) {
  return Resident(id, nom, ville, TypeBatiment::House, 10, 30.0, 20.0, 20.0,
                  3.0, x, y, 1, 1, 6, 0);
}

// Getters
int Resident::gethabitantsActuels() { return habitantsActuels; }
int Resident::getcapaciteHabitants() { return capaciteHabitants; }
