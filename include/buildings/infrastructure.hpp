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

  Resources productionRessources;

public:
  // Building costs (static for reuse)
  static double COST_POWER_PLANT;
  static double COST_WATER_TREATMENT;
  static double COST_UTILITY;
  
  // Methods
  void produireRessources();
  void impacterRessources() override;
  double calculerPollution(); // TO-DO
  // Production getter used by city to aggregate availability
  const Resources& getProductionRessources() const { return productionRessources; }

  static BatPtr createPowerPlant(Ville *ville, int x, int y);
  static BatPtr createWaterTreatmentPlant(Ville *ville, int x, int y);
  static BatPtr createUtilityPlant(Ville *ville, int x, int y);
};

#endif // !INFRASTRUCTURE
