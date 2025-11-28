#include "../include/cycle/simulation.hpp"
#include "../include/buildings/batiment.hpp"

Simulation::Simulation(const string &nomVille, Difficulty difficulty)
    : ville(nomVille,
            (difficulty == Difficulty::Easy     ? 2000.0
             : difficulty == Difficulty::Medium ? 1000.0
                                                : 500.0),
            0, Resources(0.0, 0.0), BatimentList{}) {

  TimePerCycle = (difficulty == Difficulty::Easy     ? 120
                  : difficulty == Difficulty::Medium ? 60
                                                     : 30);
  currentTime = 0;
  this->difficulty = difficulty;
  cycleActuel = 0;
  state = SimState::Running;
}

bool Simulation::canInteract() const { return state == SimState::Running; }

void Simulation::terminerCycle() {
  state = SimState::Evaluating;

  // Computing stats
  ville.collectProfit();
  ville.calculerSatisfactionTotale();
  ville.updatePopulation();
  cycleActuel++;

  // GAME OVER check
  if (ville.getPopulation() <= 0 || ville.getBudget() <= 0 ||
      ville.getSatisfaction() <= 0) {
    state = SimState::GameOver;
    return;
  }

  demarerCycle();
}

void Simulation::terminerCycleEarly() {
    if (state != SimState::Running) return;

    currentTime = TimePerCycle;

    terminerCycle();
}

void Simulation::demarerCycle() {
  currentTime = 0;
  state = SimState::Running;
}

void Simulation::tick(unsigned int delta) {
    if (state != SimState::Running) return;

    currentTime += delta;

    if (currentTime >= TimePerCycle) terminerCycle();
}

SimState Simulation::getState() { return state; }
