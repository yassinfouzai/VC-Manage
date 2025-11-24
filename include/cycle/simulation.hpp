#ifndef SIMULATION
#define SIMULATION

#include "../ville/ville.hpp"
#include "../utils.hpp"

using namespace std;

class Simulation {
public:
  Simulation(const string& nomVille, Difficulty difficulty);
  void demarerCycle();
  void terminerCycle();
  void declencherCycle();

private:
  Ville ville;
  unsigned int cycleActuel;
  Difficulty difficulty;
};

#endif // !SIMULATION
