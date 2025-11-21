#ifndef CINEMA
#define CINEMA

#include "batiment.hpp"
#include "../utils.hpp"

using namespace std;

class Cinema : public Batiment {
public:
  Cinema(int id, string nom, string type, int effectSatisfication, double cost,
       double consommationEau, double consommationElectricite, Position position, Surface surface,
       int effectBienEtre);

  Cinema(int id, string nom, string type, int effectSatisfication, double cost,
       double consommationEau, double consommationElectricite, int x, int y, int largeur, int longeur,
       int effectBienEtre);

  void ameliorerBienEtre();

private:
  int effectBienEtre;
};

#endif // !CINEMA
