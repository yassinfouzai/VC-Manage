#ifndef USINE
#define USINE

#include "../utils.hpp"
#include "batiment.hpp"

using namespace std;

class Usine : public Batiment {
public:
  Usine(int id, const string& nom, const string& type, int effectSatisfication, double cost,
        double consommationEau, double consommationElectricite, Position position, Surface surface,
        double pollution, Resources produireRessources);
  Usine(int id, const string& nom, const string& type, int effectSatisfication, double cost,
        double consommationEau, double consommationElectricite, int x, int y, int largeur, int longeur,
        double pollution, Resources produireRessources);
  void produireRessources();
  double calculerPollution();

private:
  double pollution;
  Resources productionRessources;
};

#endif // !USINE
