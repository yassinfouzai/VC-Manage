#include "../../include/buildings/maison.hpp"

Maison::Maison(int id, const std::string &nom, Ville *ville,
               int effectSatisfication, Resources consummation,
               float polution, Position position, int capaciteHabitants,
               int habitantsActuels)
    : Resident(id, nom, ville, TypeBatiment::House, effectSatisfication, 150.0,
               consummation, polution, position, Surface(1, 1),
               capaciteHabitants, habitantsActuels) {}

Maison::Maison(int id, const std::string &nom, Ville *ville,
               int effectSatisfication, double consummationEau,
               double consummationElectricte, float polution, int x, int y,
               int capaciteHabitants, int habitantsActuels)
    : Resident(id, nom, ville, TypeBatiment::House, effectSatisfication, 150.0,
               consummationEau, consummationElectricte, polution, x, y, 1, 1, capaciteHabitants,
               habitantsActuels) {}
