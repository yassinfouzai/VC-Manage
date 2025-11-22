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
      Batiment(id, nom, ville, type, effectSatisfication, cost, 0, 0,
               consommationEau, consommationElectricite, polution, x, y,
               largeur, longeur) {}

Resident::Resident(int id, const std::string &nom, Ville *ville,
                   TypeBatiment type, int effectSatisfication, double cost,
                   Resources consummation, float polution, Position position,
                   Surface surface, int capaciteHabitants, int habitantsActuels)
    : capaciteHabitants(capaciteHabitants), habitantsActuels(habitantsActuels),
      Batiment(id, nom, ville, type, effectSatisfication, cost, 0, 0,
               consummation.eau, consummation.electricite, polution, position,
               surface) {}

// Methods
void Resident::afficheDetails() const {
  Batiment::afficheDetails();
  std::cout << "Habitants Actuels :\t" << habitantsActuels << endl;
  std::cout << "Capacite Habitants :\t" << capaciteHabitants << endl;
}

// TO-DO check with capacity of the house
void Resident::ajouterHabitants(int nombreHabitants) {
  habitantsActuels += nombreHabitants;
}

void Resident::retirerHabitants(int nombreHabitants) {
  if (nombreHabitants >= habitantsActuels)
    habitantsActuels = 0;
  else
    habitantsActuels -= nombreHabitants;
}
