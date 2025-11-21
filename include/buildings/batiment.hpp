#ifndef BATIMENT
#define BATIMENT

#include "../utils.hpp"
#include "../ville/ville.hpp"
#include <string>

using namespace std;

class Batiment {
public:
  Surface surface;
  Position position;
  Ville* ville;

  // Constructors
  Batiment(int id, const string& nom, Ville* ville, const string& type, int effectSatisfication,
           double cost, double consommationEau, double consommationElectricite,
           int x, int y, int largeur, int longeur);

  Batiment(int id, const string& nom, Ville* ville, const string& type, int effectSatisfication,
           double cost, double consommationEau, double consommationElectricite,
           Position position, Surface surface);
  virtual ~Batiment() = default; // For the Polymorphic deletion

  virtual void afficheDetails() const;
  int calculerImpactRessources();

  // Getters
  int getID();
  int getSatisfaction();
  Resources getConsummation();

protected:
  int id;
  string nom;
  string type;
  Resources consommation;
  int effectSatisfication;
  double cost;
};

#endif // !BATIMENT
