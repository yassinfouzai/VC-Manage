#ifndef COMERCIAL
#define COMERCIAL

#include "service.hpp"

using namespace std;

class Comercial : public Service {
protected:
  // Constructors
  Comercial(int id, const string &nom, Ville *ville, TypeBatiment type,
            int effectSatisfication, double cost, unsigned int employees,
            unsigned int employeesNeeded, double consommationEau,
            double consommationElectricite, float polution, int x, int y,
            int largeur, int longeur, double profit);

  Comercial(int id, const string &nom, Ville *ville, TypeBatiment type,
            int effectSatisfication, double cost, unsigned int employees,
            unsigned int employeesNeeded, Resources consommation,
            float polution, Position position, Surface surface, double profit);

public:
  // Methods
  void afficheDetails() const override;
  static Comercial createCinema(int id, const string &nom, Ville *ville, int x,
                          int y);
  static Comercial createMall(int id, const string &nom, Ville *ville, int x, int y);
  static Comercial createBank(int id, const string &nom, Ville *ville, int x, int y);

  // Getters
  double getProfit();

private:
  double profit;
};

#endif // !COMERCIAL
