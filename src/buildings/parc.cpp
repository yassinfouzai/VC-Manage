#include "../../include/buildings/parc.hpp"
#include <iostream>

Parc::Parc(int id, const string &nom, Ville *ville, int effectSatisfication,
           double cost, double consommationEau, double consommationElectricite,
           float polution, Position position, int effectBienEtre,
           unsigned int EmployeesNeeded)
    : effectBienEtre(effectBienEtre), EmployeesNeeded(EmployeesNeeded),
      Batiment(id, nom, ville, TypeBatiment::Park, effectSatisfication, cost, 0, 0, // TODO : modify this to be employee attrib
               consommationEau, consommationElectricite, polution, position,
               Surface(2, 2)) {}

Parc::Parc(int id, const string &nom, Ville *ville, int effectSatisfication,
           double cost, double consommationEau, double consommationElectricite,
           float polution, int x, int y, int effectBienEtre,
           unsigned int EmployeesNeeded)
    : effectBienEtre(effectBienEtre), EmployeesNeeded(EmployeesNeeded),
      Batiment(id, nom, ville, TypeBatiment::Park, effectSatisfication, cost, 0, 0, // TODO : same here 
               consommationEau, consommationElectricite, polution, x, y, 2, 2) {
}

void Parc::diminuerPollution() {
  ville->setPolution(ville->getPolution() - (surface.largeur * surface.longeur *
                                             Parc::POLLUTION_REDUCTION_FACTOR));
}

void Parc::ameliorerBienEtre() {
  ville->setSatisfaction(
      ville->getSatisfaction() +
      (float)(surface.largeur * surface.longeur * effectBienEtre));
}

void Parc::afficheDetails() const {
  Batiment::afficheDetails();
  std::cout << "effectBienEtre :\t" << effectBienEtre << endl;
}
