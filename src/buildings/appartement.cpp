#include "../../include/buildings/appartement.hpp"

Appartement::Appartement(int id, const std::string &nom, Ville *ville,
               int effectSatisfication, Resources consommation, float polution,
               Position position, int capaciteHabitants, int habitantsActuels)
    : Resident(id, nom, ville, TypeBatiment::Apartment, effectSatisfication, 400.0,
               consommation, polution, position,
               Surface(2, 2), capaciteHabitants, habitantsActuels) {}

Appartement::Appartement(int id, const std::string &nom, Ville *ville,
               int effectSatisfication, double consommationEau,
               double consommationElectricte, float polution, int x, int y,
               int capaciteHabitants, int habitantsActuels)
    : Resident(id, nom, ville, TypeBatiment::Apartment, effectSatisfication, 400.0,
               consommationEau, consommationElectricte, polution, x, y, 1, 1, capaciteHabitants,
               habitantsActuels) {}
