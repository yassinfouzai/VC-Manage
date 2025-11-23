#include "../../include/buildings/commercial.hpp"

#include <iostream>
#include <string>

using namespace std;

Comercial::Comercial(int id, const string &nom, Ville *ville, TypeBatiment type,
                     int effectSatisfication, double cost,
                     unsigned int Employees, unsigned int EmployeesNeeded,
                     double consommationEau, double consommationElectricite,
                     float polution, int x, int y, int largeur, int longeur,
                     double profit)
    : profit(profit),
      Service(id, nom, ville, type, effectSatisfication, cost, Employees,
              EmployeesNeeded, consommationEau, consommationElectricite,
              polution, x, y, largeur, longeur) {}

Comercial::Comercial(int id, const string &nom, Ville *ville, TypeBatiment type,
                     int effectSatisfication, double cost,
                     unsigned int Employees, unsigned int EmployeesNeeded,
                     Resources consommation, float polution, Position position,
                     Surface surface, double profit)
    : profit(profit),
      Service(id, nom, ville, type, effectSatisfication, cost, Employees,
              EmployeesNeeded, consommation, polution, position, surface) {}

Comercial Comercial::createCinema(int id, const string &nom, Ville *ville,
                                  int x, int y) {
    return Comercial(id, nom, ville, TypeBatiment::Cinema, 100, 500.0, 0, 5, 10, 30, 2.5, x, y, 2, 1, 10.0);
}

Comercial Comercial::createMall(int id, const string &nom, Ville *ville,
                                  int x, int y) {
    return Comercial(id, nom, ville, TypeBatiment::Mall, 100, 2000.0, 0, 50, 400, 600, 8.0, x, y, 3, 3, 20.0);
}

Comercial Comercial::createBank(int id, const string &nom, Ville *ville,
                                  int x, int y) {
    return Comercial(id, nom, ville, TypeBatiment::Bank, -20, 2000.0, 0, 10, 10, 30, 2.0, x, y, 1, 1, 50.0);
}

// Methods
void Comercial::afficheDetails() const {
  Service::afficheDetails();
  std::cout << "Profit :\t" << profit << endl;
}

// Getters
double Comercial::getProfit() { return profit; }
