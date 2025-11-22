#ifndef RESIDENT
#define RESIDENT

#include "batiment.hpp"

using namespace std;

class Resident : public Batiment {
public:
  // Constructors
  Resident(int id, const std::string &nom, Ville *ville, TypeBatiment type,
           int effectSatisfication, double cost, double consommationEau,
           double consommationElectricite, float polution, int x, int y,
           int largeur, int longeur, int capaciteHabitants,
           int habitantsActuels);

  Resident(int id, const std::string &nom, Ville *ville, TypeBatiment type,
           int effectSatisfication, double cost, Resources consommation,
           float polution, Position position, Surface surface,
           int capaciteHabitants, int habitantsActuels);

  // Methods
  void afficheDetails() const override;
  void ajouterHabitants(int nombreHabitants);
  void retirerHabitants(int nombreHabitants);

private:
  int capaciteHabitants;
  int habitantsActuels;
};

#endif // !MAISON
