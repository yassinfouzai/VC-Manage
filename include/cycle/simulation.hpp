#ifndef SIMULATION
#define SIMULATION

#include "../utils.hpp"
#include "../ville/ville.hpp"

using namespace std;

class Simulation {
public:
  // Constructor
  Simulation(const string &nomVille, Difficulty difficulty);

  // Methods
  void demarerCycle();
  void terminerCycle();
  void terminerCycleEarly();
  void declencherEvenement();
  void tick(unsigned int delta);
  bool canInteract() const;

  // Getters
  SimState getState();

private:
  Ville ville;
  unsigned int cycleActuel;
  Difficulty difficulty;
  unsigned int TimePerCycle;
  unsigned int currentTime;
  SimState state;
};

#endif // !SIMULATION
