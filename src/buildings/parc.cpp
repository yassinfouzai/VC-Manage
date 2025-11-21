#include "../../include/buildings/parc.hpp"

Parc::Parc(int id, const string& nom, Ville* ville, const string& type, int effectSatisfication,
           double cost, double consommationEau, double consommationElectricite,
           Position position, Surface surface, int effectBienEtre)
    : effectBienEtre(effectBienEtre),
      Batiment(id, nom, ville, type, effectSatisfication, cost, consommationEau,
               consommationElectricite, position, surface) {}

Parc::Parc(int id, const string& nom, Ville* ville, const string& type, int effectSatisfication,
           double cost, double consommationEau, double consommationElectricite,
           int x, int y, int largeur, int longeur, int effectBienEtre)
    : effectBienEtre(effectBienEtre),
      Batiment(id, nom, ville, type, effectSatisfication, cost, consommationEau,
               consommationElectricite, x, y, largeur, longeur) {}

void Parc::diminuerPollution() {
    ville->setPolution(ville->getPolution() - (surface.largeur * surface.longeur * Parc::POLLUTION_REDUCTION_FACTOR));
}

void Parc::ameliorerBienEtre() {
    ville->setSatisfaction(ville->getSatisfaction() + (float)(surface.largeur * surface.longeur * effectBienEtre));
}
