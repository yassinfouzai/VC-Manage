#ifndef MAISON
#define MAISON

#include "resident.hpp"

class Maison : public Resident {
public:
  Maison(int id, const std::string &nom, Ville *ville, int effectSatisfication,
         Resources consummation, float polution, Position position,
         int capaciteHabitants, int habitantsActuels);
  Maison(int id, const std::string &nom, Ville *ville, int effectSatisfication,
         double consummationEau, double consummationElectricte, float polution,
         int x, int y, int capaciteHabitants, int habitantsActuels);
};

#endif // !MAISON
