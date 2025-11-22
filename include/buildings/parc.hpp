#ifndef PARC
#define PARC

#include "../utils.hpp"
#include "batiment.hpp"

using namespace std;

class Parc : public Batiment {
public:
  // Constructors
  Parc(int id, const string &nom, Ville *ville, int effectSatisfication,
       double cost, double consommationEau, double consommationElectricite,
       float polution, Position position, int effectBienEtre,
       unsigned int EmployeesNeeded);

  Parc(int id, const string &nom, Ville *ville, int effectSatisfication,
       double cost, double consommationEau, double consommationElectricite,
       float polution, int x, int y, int effectBienEtre,
       unsigned int EmployeesNeeded);

  // Methods
  void afficheDetails() const override;
  void ameliorerBienEtre();
  void diminuerPollution();

private:
  static constexpr int POLLUTION_REDUCTION_FACTOR = 10;
  int effectBienEtre;
  unsigned int EmployeesNeeded;
  unsigned int Employees;
};

#endif // !PARC
