#ifndef BATIMENT
#define BATIMENT

#include "../utils.hpp"
#include <string>

using namespace std;

class Batiment {
public:
  Batiment(int id, string nom, string type, int effectSatisfication,
           double cost, double consommationEau, double consommationElectricite,
           int x, int y, int largeur, int longeur);

  Batiment(int id, string nom, string type, int effectSatisfication,
           double cost, double consommationEau, double consommationElectricite,
           Position position, Surface surface);
  virtual ~Batiment() = default; // For the Polymorphic deletion
  void afficheDetails();
  int calculerImpactRessources();
  int getID();
  int getSatisfaction();
  Resources getConsummation();

protected:
  int id;
  string nom;
  string type;
  Resources consommation;
  int effectSatisfication;
  Position position;
  Surface surface;
  double cost;
};

#endif // !BATIMENT
