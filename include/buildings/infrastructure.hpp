#ifndef INFRASTRUCTURE
#define INFRASTRUCTURE

#include "../utils.hpp"
#include "service.hpp"

using namespace std;

class Infrastructure : public Service {
protected:
  Infrastructure(int id, const string &nom, Ville *ville, TypeBatiment type,
                 int effectSatisfication, double cost, unsigned int employees,
                 unsigned int employeesNeeded, double consommationEau,
                 double consommationElectricite, double pollution,
                 Position position, Surface surface,
                 Resources productionRessources);
  Infrastructure(int id, const string &nom, Ville *ville, TypeBatiment type,
                 int effectSatisfication, double cost, unsigned int employees,
                 unsigned int employeesNeeded, double consommationEau,
                 double consommationElectricite, double pollution, int x, int y,
                 int largeur, int longeur, Resources productionRessources);

public:
  void produireRessources();
  double calculerPollution();

private:
  Resources productionRessources;
};

#endif // !INFRASTRUCTURE
