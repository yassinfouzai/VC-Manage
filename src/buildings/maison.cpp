#include "../../include/buildings/maison.hpp"

#include <iostream>
#include <string>

using namespace std;

// Constructor
Maison::Maison(int id, const string &nom, Ville *ville, const string &type,
               int effectSatisfication, double cost, double consommationEau,
               double consommationElectricite, int x, int y, int largeur,
               int longeur, int capaciteHabitants, int habitantsActuels)
    : capaciteHabitants(capaciteHabitants), habitantsActuels(habitantsActuels),
      Batiment(id, nom, ville, type, effectSatisfication, consommationEau, cost,
               consommationElectricite, x, y, largeur, longeur) {}

Maison::Maison(int id, const string &nom, Ville *ville, const string &type,
               int effectSatisfication, double cost, double consommationEau,
               double consommationElectricite, Position position,
               Surface surface, int capaciteHabitants, int habitantsActuels)
    : capaciteHabitants(capaciteHabitants), habitantsActuels(habitantsActuels),
      Batiment(id, nom, ville, type, effectSatisfication, consommationEau, cost,
               consommationElectricite, position, surface) {}

//Methods
void Maison::afficheDetails() const  {
  Batiment::afficheDetails();
  std::cout << "Habitants Actuels :\t" << habitantsActuels << endl;
  std::cout << "Capacite Habitants :\t" << capaciteHabitants << endl;
}


// TO-DO check with capacity of the house
void Maison::ajouterHabitants(int nombreHabitants) {
  habitantsActuels += nombreHabitants;
}

void Maison::retirerHabitants(int nombreHabitants) {
  if (nombreHabitants >= habitantsActuels)
    habitantsActuels = 0;
  else
    habitantsActuels -= nombreHabitants;
}
