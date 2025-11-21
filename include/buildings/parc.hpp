#ifndef PARC
#define PARC

#include "../utils.hpp"
#include "batiment.hpp"

using namespace std;

class Parc : public Batiment {
public:
  Parc(int id, const string& nom, Ville* ville, const string& type, int effectSatisfication, double cost,
       double consommationEau, double consommationElectricite,
       Position position, Surface surface, int effectBienEtre);

  Parc(int id, const string& nom, Ville* ville, const string& type, int effectSatisfication, double cost,
       double consommationEau, double consommationElectricite, int x, int y,
       int largeur, int longeur, int effectBienEtre);

  void ameliorerBienEtre();
  void diminuerPollution();

private:
  static constexpr int POLLUTION_REDUCTION_FACTOR = 10;
  int effectBienEtre;
};

#endif // !PARC
