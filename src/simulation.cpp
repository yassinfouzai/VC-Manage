#include "../include/cycle/simulation.hpp"
#include "../include/buildings/batiment.hpp"
#include "../include/evenement.hpp"
#include <iostream>

Simulation::Simulation(const string &nomVille, Difficulty difficulty)
    : ville(nomVille,
            (difficulty == Difficulty::Easy     ? 2000.0
             : difficulty == Difficulty::Medium ? 1000.0
                                                : 500.0),
            500, Resources(0.0, 0.0), BatimentList{}) {

  TimePerCycle = (difficulty == Difficulty::Easy     ? 120.0
                  : difficulty == Difficulty::Medium ? 60.0
                                                     : 30.0);
  this->difficulty = difficulty;
  cycleActuel = 0;
  
  // Initialize event system
  eventManager.initialiserEvenements();
  evenementActuel = nullptr;
  
  // Initialize job assignments so first cycle shows correct employment
  ville.assignerEmplois();
  
  demarerCycle();
}

bool Simulation::canInteract() const { return state == SimState::Running; }

void Simulation::terminerCycle() {
  std::cout << "Terminer working\n";
  state = SimState::Evaluating;

  // Computing stats
  // Compute utilities availability for this cycle (production vs consumption)
  {
    Resources cons = ville.calculerconsommationTotale();
    Resources prod = ville.calculerProductionTotale();
    float waterAvail = 1.0f;
    float powerAvail = 1.0f;
    if (cons.eau > 0.0) {
      waterAvail = static_cast<float>(prod.eau / cons.eau);
    }
    if (cons.electricite > 0.0) {
      powerAvail = static_cast<float>(prod.electricite / cons.electricite);
    }
    // Clamp 0..1 and set on city for this cycle's calculations
    waterAvail = std::max(0.0f, std::min(1.0f, waterAvail));
    powerAvail = std::max(0.0f, std::min(1.0f, powerAvail));
    ville.setWaterAvailability(waterAvail);
    ville.setPowerAvailability(powerAvail);
    std::cout << "Utilities: Water " << (waterAvail * 100.0f) << "%, Power " << (powerAvail * 100.0f) << "%" << std::endl;
  }

  ville.collectProfit();
  
  // Apply per-cycle upkeep costs (taxes, maintenance, salaries)
  // Hardened: higher base and per-unit coefficients for gameplay challenge
  unsigned int pop = ville.getPopulation();
  size_t numBuildings = ville.batiments.size();
  double upkeepCost = 12.0 + (pop * 1.2) + (numBuildings * 6.0);
  
  // Slightly stronger exponential growth with population
  double exponentialFactor = 1.0 + (pop / 18000.0);
  upkeepCost *= exponentialFactor;
  
  double currentBudget = ville.getBudget();
  ville.setBudget(currentBudget - upkeepCost);
  
  std::cout << "Upkeep costs this cycle: $" << upkeepCost << std::endl;
  
  ville.calculerPolutionTotale();
  ville.calculerSatisfactionTotale();
  ville.updatePopulation();       // Changes population based on satisfaction
  ville.assignerEmplois();        // Reassign jobs AFTER population changes
  cycleActuel++;

  // GAME OVER check
  if (ville.getPopulation() <= 0 && ville.getBudget() <= 0 &&
      ville.getSatisfaction() <= 0) {
    state = SimState::GameOver;
    return;
  }

  demarerCycle();
}

void Simulation::terminerCycleEarly() {
  std::cout << "Early working\n";
  if (state != SimState::Running)
    return;

  currentTime = TimePerCycle;

  terminerCycle();
}

void Simulation::demarerCycle() {
  state = SimState::Running;
  std::cout << "\n\n";
  std::cout << "CYCLE " << cycleActuel + 1 << " COMMENCE\n";
  std::cout << "\n" << std::endl;
  currentTime = 0;
  
  // Clear previous cycle's event
  evenementActuel = nullptr;
  
  // Try to trigger a random event
  declencherEvenement();
}

void Simulation::declencherEvenement() {
  // Attempt to generate a random event
  evenementActuel = eventManager.genererEvenementAleatoire(&ville);
  
  if (evenementActuel) {
    // Apply the event
    evenementActuel->appliquer(&ville);
  } else {
    std::cout << "Aucun événement ce cycle. Tout est calme." << std::endl;
  }
}

void Simulation::tick(float delta) {
  if (state != SimState::Running)
    return;

  currentTime += delta;

  if (currentTime >= TimePerCycle)
    terminerCycle();
}

// Getters
int Simulation::getCycle() const { return cycleActuel; }
float Simulation::getTimePerCycle() const { return TimePerCycle; }
float Simulation::getCurrentTime() const { return currentTime; }
SimState Simulation::getState() const { return state; }
const Ville &Simulation::getVille() const { return ville; }
Ville &Simulation::getVille() { return ville; }
const Evenement* Simulation::getEvenementActuel() const { 
  return evenementActuel.get(); 
}
