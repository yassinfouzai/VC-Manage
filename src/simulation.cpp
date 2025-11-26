#include "../include/cycle/simulation.hpp"

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
}

void Simulation::terminerCycle() {
  ville.collectProfit();
  ville.calculerSatisfactionTotale();
  ville.updatePopulation();
  cycleActuel++;
}

void Simulation::demarerCycle() { currentTime = 0; }
