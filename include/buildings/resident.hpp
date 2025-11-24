#ifndef RESIDENT
#define RESIDENT

#include "batiment.hpp"

using namespace std;

class Resident : public Batiment {
protected:
  // Constructors
  Resident(int id, const string &nom, Ville *ville, TypeBatiment type,
           int effectSatisfication, double cost, double consommationEau,
           double consommationElectricite, float polution, int x, int y,
           int largeur, int longeur, int capaciteHabitants,
           int habitantsActuels);

  Resident(int id, const string &nom, Ville *ville, TypeBatiment type,
           int effectSatisfication, double cost, Resources consommation,
           float polution, Position position, Surface surface,
           int capaciteHabitants, int habitantsActuels);

  int capaciteHabitants;
  int habitantsActuels;

public:
  // Methods
  void afficheDetails() const override;
  void ajouterHabitants(int nombreHabitants);
  void retirerHabitants(int nombreHabitants);

  static Resident createHouse(int id, const string &nom, Ville *ville, int x,
                              int y);

  // Getters
  int gethabitantsActuels();
};

#endif // !MAISON
