#include "../../include/buildings/appartement.hpp"
#include <stdexcept>
#include <string>

Appartement::Appartement(int id, const std::string &nom, Ville *ville,
                         TypeBatiment type, int effectSatisfication,
                         double cost, Resources consommation, float polution,
                         Position position, Surface surface,
                         int capaciteHabitants, int habitantsActuels,
                         unsigned int floorsCount)
    : floorsCount(floorsCount),
      Resident(id, nom, ville, type, effectSatisfication, cost, consommation,
               polution, position, surface, capaciteHabitants,
               habitantsActuels) {}

Appartement::Appartement(int id, const std::string &nom, Ville *ville,
                         TypeBatiment type, int effectSatisfication,
                         double cost, double consommationEau,
                         double consommationElectricte, float polution, int x,
                         int y, int largeur, int longeur, int capaciteHabitants,
                         int habitantsActuels, unsigned int floorsCount)
    : floorsCount(floorsCount),
      Resident(id, nom, ville, type, effectSatisfication, cost, consommationEau,
               consommationElectricte, polution, x, y, largeur, longeur,
               capaciteHabitants, habitantsActuels) {}

// Getters
unsigned int Appartement::getFloorsCount() { return floorsCount; }

void Appartement::addNewFloor() {
  // Disable adding floors beyond the maximum; apartments are created at max
  if (floorsCount < MAX_FLOOR_COUNT) {
    floorsCount++;
    cost += COST_PER_FLOOR;
    polution += POLUTION_PER_FLOOR;
    effectSatisfication += EFFET_SATISFACTION_PER_FLOOR;
    consommation +=
        Resources(CONSOMMATION_EAU_PER_FLOOR, CONSOMMATION_ELE_PER_FLOOR);
    capaciteHabitants += MAX_HABITATS_PER_FLOOR;
  } else {
    // No-op: already at maximum floors
    return;
  }
}

void Appartement::destroyFloor() {
  // Apartments are fixed at max floors in creation; floor removal disabled.
  return;
}

BatPtr Appartement::createAppartement(Ville *ville,
                                           unsigned int floorsCount, int x,
                                           int y) {
  // Force apartments to be created at maximum floors due to time :'()
  floorsCount = MAX_FLOOR_COUNT;
  
  // Auto-generate name and ID
  std::string generatedName = NameGenerator::getRandomName(TypeBatiment::Apartment);
  Position position(x, y);
  Surface surface(1, 1);
  int generatedID = BuildingIDGenerator::generateID(generatedName, TypeBatiment::Apartment, position, surface);

  double baseCost = Resident::COST_APARTMENT * floorsCount;
  return BatPtr( new Appartement(generatedID, generatedName, ville, TypeBatiment::Apartment,
                     EFFET_SATISFACTION_PER_FLOOR * floorsCount,
                     baseCost,
                     CONSOMMATION_EAU_PER_FLOOR * floorsCount,
                     CONSOMMATION_ELE_PER_FLOOR * floorsCount,
                     POLUTION_PER_FLOOR * floorsCount, x, y, 1, 1,
                     MAX_HABITATS_PER_FLOOR * floorsCount, 0, floorsCount));
}
