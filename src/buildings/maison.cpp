#include "../../include/buildings/maison.hpp"
#include <string>

using namespace std;

Maison::Maison(int id, string nom, string type, int effectSatisfication, double cost,
               double consommationEau, double consommationElectricite, int x, int y, int largeur, int longeur,
               int capaciteHabitants, int habitantsActuels)
    : Batiment(id, nom, type, effectSatisfication, consommationEau, cost,
               consommationElectricite, x, y, largeur, longeur) {}

Maison::Maison(int id, string nom, string type, int effectSatisfication, double cost,
               double consommationEau, double consommationElectricite, Position position, Surface surface,
               int capaciteHabitants, int habitantsActuels)
    : Batiment(id, nom, type, effectSatisfication, consommationEau, cost,
               consommationElectricite, position, surface) {}


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
