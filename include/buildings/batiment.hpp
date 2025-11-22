#ifndef BATIMENT
#define BATIMENT

#include "../utils.hpp"
#include "../ville/ville.hpp"
#include <string>

using namespace std;

class Batiment {
public:
  TypeBatiment type;
  Surface surface;
  Position position;
  Ville *ville;

  // Constructors
  Batiment(int id, const string &nom, Ville *ville, TypeBatiment type,
           int effectSatisfication, double cost, unsigned int Employees,
           unsigned int EmployeesNeeded, double consommationEau,
           double consommationElectricite, float polution, int x, int y,
           int largeur, int longeur);

  Batiment(int id, const string &nom, Ville *ville, TypeBatiment type,
           int effectSatisfication, double cost, unsigned int Employees,
           unsigned int EmployeesNeeded, double consommationEau,
           double consommationElectricite, float polution, Position position,
           Surface surface);
  virtual ~Batiment() = default; // For the Polymorphic deletion

  virtual void afficheDetails() const;
  int calculerImpactRessources();

  // Getters
  int getID();
  int getSatisfaction();
  float getPolution();
  Resources getConsummation();

protected:
  int id;
  string nom;
  Resources consommation;
  float polution;
  int effectSatisfication;
  unsigned int EmployeesNeeded;
  unsigned int Employees;
  double cost;
};

#endif // !BATIMENT
