#ifndef MAISON
#define MAISON

#include "resident.hpp"

class Appartement : public Resident {
public:
  Appartement(int id, const std::string &nom, Ville *ville, int effectSatisfication,
         Resources consommation, float polution, Position position,
         int capaciteHabitants, int habitantsActuels);
  Appartement(int id, const std::string &nom, Ville *ville, int effectSatisfication,
         double consommationEau, double consommationElectricte, float polution, int x, int y,
         int capaciteHabitants, int habitantsActuels);
};

#endif // !MAISON
