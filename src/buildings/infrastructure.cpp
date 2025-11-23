#include "../../include/buildings/infrastructure.hpp"

#include <string>

using namespace std;

Infrastructure::Infrastructure(int id, const string &nom, Ville *ville,
                               TypeBatiment type, int effectSatisfication,
                               double cost, unsigned int employees,
                               unsigned int employeesNeeded,
                               double consommationEau,
                               double consommationElectricite, double pollution,
                               int x, int y, int largeur, int longeur,
                               Resources productionRessources)
    : productionRessources(productionRessources),
      Service(id, nom, ville, type, effectSatisfication, cost, employees,
              employeesNeeded, consommationEau, consommationElectricite,
              polution, x, y, largeur, longeur) {}

Infrastructure::Infrastructure(int id, const string &nom, Ville *ville,
                               TypeBatiment type, int effectSatisfication,
                               double cost, unsigned int employees,
                               unsigned int employeesNeeded,
                               double consommationEau,
                               double consommationElectricite, double pollution,
                               Position position, Surface surface,
                               Resources productionRessources)
    : productionRessources(productionRessources),
      Service(id, nom, ville, type, effectSatisfication, cost, employees,
              employeesNeeded, consommation, polution, position, surface) {}
