#ifndef MAISON
#define MAISON

#include "batiment.hpp"

using namespace std;

class Maison : public Batiment {
public:
  Maison(int id, string nom, string type, int effectSatisfication, double cost,
         double consommationEau, double consommationElectricite, int x, int y, int largeur, int longeur,
         int capaciteHabitants, int habitantsActuels);
  Maison(int id, string nom, string type, int effectSatisfication, double cost,
         double consommationEau, double consommationElectricite, Position position, Surface surface,
         int capaciteHabitants, int habitantsActuels);
  void ajouterHabitants(int nombreHabitants);
  void retirerHabitants(int nombreHabitants);

private:
  int capaciteHabitants;
  int habitantsActuels;
};

#endif // !MAISON
