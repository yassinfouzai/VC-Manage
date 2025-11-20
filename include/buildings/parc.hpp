#ifndef PARC
#define PARC

#include "batiment.hpp"
#include "../utils.hpp"

using namespace std;

class Parc : public Batiment {
public:
  Parc(int id, string nom, string type, int effectSatisfication, double cost,
       double consommationEau, double consommationElectricite, Position position, Surface surface,
       int effectBienEtre);

  Parc(int id, string nom, string type, int effectSatisfication, double cost,
       double consommationEau, double consommationElectricite, int x, int y, int largeur, int longeur,
       int effectBienEtre);

  void ameliorerBienEtre();

private:
  int effectBienEtre;
};

#endif // !PARC
