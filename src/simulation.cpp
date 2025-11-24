#include "../include/cycle/simulation.hpp"

Simulation::Simulation(const string &nomVille, Difficulty difficulty)
    : difficulty(difficulty), cycleActuel(0),
      ville(nomVille,
            (difficulty == Difficulty::Easy     ? 2000.0
             : difficulty == Difficulty::Medium ? 1000.0
                                                : 500.0),
            0, Resources(0.0, 0.0), BatimentList{}) {}
