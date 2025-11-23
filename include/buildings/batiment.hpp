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
           int effectSatisfication, double cost, double consommationEau,
           double consommationElectricite, float polution, int x, int y,
           int largeur, int longeur);

  Batiment(int id, const string &nom, Ville *ville, TypeBatiment type,
           int effectSatisfication, double cost, Resources consommation,
           float polution, Position position, Surface surface);
  virtual ~Batiment() = default; // For the Polymorphic deletion

  virtual void afficheDetails() const;
  int calculerImpactRessources();

  // Getters
  int getID();
  int getSatisfaction();
  float getPolution();
  Resources getconsommation();

protected:
  int id;
  string nom;
  Resources consommation;
  float polution;
  int effectSatisfication;
  double cost;
};

#endif // !BATIMENT
