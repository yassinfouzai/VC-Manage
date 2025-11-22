#include "../../include/buildings/batiment.hpp"
#include <iostream>
#include <string>

using namespace std;

// Constructors
Batiment::Batiment(int id, const string &nom, Ville *ville, TypeBatiment type,
                   int effectSatisfication, double cost, unsigned int Employees,
                   unsigned int EmployeesNeeded, double consommationEau,
                   double consommationElectricite, float polution, int x, int y,
                   int largeur, int longeur)
    : id(id), nom(nom), ville(ville), type(type),
      effectSatisfication(effectSatisfication), cost(cost),
      Employees(Employees), EmployeesNeeded(EmployeesNeeded),
      consommation(consommationEau, consommationElectricite), position(x, y),
      surface(largeur, longeur) {}

Batiment::Batiment(int id, const string &nom, Ville *ville, TypeBatiment type,
                   int effectSatisfication, double cost, unsigned int Employees,
                   unsigned int EmployeesNeeded, double consommationEau,
                   double consommationElectricite, float polution,
                   Position position, Surface surface)
    : id(id), nom(nom), ville(ville), type(type),
      effectSatisfication(effectSatisfication), cost(cost),
      Employees(Employees), EmployeesNeeded(EmployeesNeeded),
      consommation(consommationEau, consommationElectricite),
      position(position), surface(surface) {}

// methods
void Batiment::afficheDetails() const {
  std::cout << "Batiment Info :" << endl;
  std::cout << "ID :\t" << id << endl;
  std::cout << "Nom :\t" << nom << endl;
  std::cout << "Nom de ville :\t" << (ville ? ville->getNom() : "N/A") << endl;
  std::cout << "effectSatisfication :\t" << effectSatisfication << endl;
  std::cout << "consommationEau  :\t" << consommation.eau << "Liter/s" << endl;
  std::cout << "consommationElectricite  :\t" << consommation.electricite
            << "Watt/s" << endl;
  std::cout << "Position : (" << position.x << ", " << position.y << ")"
            << endl;
  std::cout << "Surface : (" << surface.largeur << ", " << surface.longeur
            << ")" << endl;
}

int Batiment::calculerImpactRessources() { return 0; }

// getters
int Batiment::getID() { return id; }
Resources Batiment::getConsummation() { return consommation; }
int Batiment::getSatisfaction() { return effectSatisfication; }
float Batiment::getPolution() { return polution; }
