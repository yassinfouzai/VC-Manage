#include "../../include/buildings/batiment.hpp"
#include <iostream>
#include <string>

using namespace std;

Batiment::Batiment(int id, string nom, string type, int effectSatisfication,
           double cost, double consommationEau, double consommationElectricite,
           int x, int y, int largeur, int longeur)
    : id(id), nom(nom), type(type), effectSatisfication(effectSatisfication),
      consommation(consommationEau, consommationElectricite), position(x,y), surface(largeur, longeur) {}

Batiment::Batiment(int id, string nom, string type, int effectSatisfication, double cost,
                   double consommationEau, double consommationElectricite, Position position, Surface surface)
    : id(id), nom(nom), type(type), effectSatisfication(effectSatisfication),
      consommation(consommationEau, consommationElectricite), position(position), surface(surface) {}


void Batiment::afficheDetails() {
  std::cout << "Batiment Info :" << endl;
  std::cout << "ID :\t" << id << endl;
  std::cout << "Nom :\t" << nom << endl;
  std::cout << "effectSatisfication :\t" << effectSatisfication << endl;
  std::cout << "consommationEau  :\t" << consommation.eau << "Liter/s" << endl;
  std::cout << "consommationElectricite  :\t" << consommation.electricite
            << "Watt/s" << endl;
    std::cout << "Position : (" << position.x << ", " << position.y << ")" << endl;
    std::cout << "Surface : (" << surface.largeur << ", " << surface.longeur << ")" << endl;
}

int Batiment::calculerImpactRessources() { return 0; }

// getters 
int Batiment::getID() { return id; }
Resources Batiment::getConsummation() { return consommation; }
int Batiment::getSatisfaction() { return effectSatisfication; }
