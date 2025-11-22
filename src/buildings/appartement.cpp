#include "../../include/buildings/appartement.hpp"

Appartement::Appartement(int id, const std::string &nom, Ville *ville,
               int effectSatisfication, Resources consummation, float polution,
               Position position, int capaciteHabitants, int habitantsActuels)
    : Resident(id, nom, ville, TypeBatiment::Apartment, effectSatisfication, 400.0,
               consommation, polution, position,
               Surface(2, 2), capaciteHabitants, habitantsActuels) {}

Appartement::Appartement(int id, const std::string &nom, Ville *ville,
               int effectSatisfication, double consummationEau,
               double consummationElectricte, float polution, int x, int y,
               int capaciteHabitants, int habitantsActuels)
    : Resident(id, nom, ville, TypeBatiment::Apartment, effectSatisfication, 400.0,
               consummationEau, consummationElectricte, polution, x, y, 1, 1, capaciteHabitants,
               habitantsActuels) {}
