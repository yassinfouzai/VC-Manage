#ifndef SIMULATION
#define SIMULATION

#include "../ville/ville.hpp"

using namespace std;

class Simulation {
public:
  Simulation(Ville ville);
  void demarerCycle();
  void terminerCycle();
  void declencherCycle();

private:
  Ville ville;
};

#endif // !SIMULATION
