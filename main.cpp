#include "vehicle_info.hpp"
#include "vehicle_simulation.hpp"

int main() {
  cout << "STARTING SIMULATION\n\n";

  uint32_t maxChargers, maxVehicles;
  double totalSimulationHrs, simulationStepSize;

  // Prompt user for simulation parameters
  cout << "Enter the number of vehicles: ";
  cin >> maxVehicles;
  if (maxVehicles <= 0) {
    cout << "Invalid input for number of vehicles. Exiting simulation.\n";
    return 1;
  }

  cout << "Enter the number of chargers: ";
  cin >> maxChargers;
  if (maxChargers <= 0) {
    cout << "Invalid input for number of chargers. Exiting simulation.\n";
    return 1;
  }

  cout << "Enter the maximum simulation time: ";
  cin >> totalSimulationHrs;
  if (totalSimulationHrs <= 0) {
    cout << "Invalid input for total simulation hours. Exiting simulation.\n";
    return 1;
  }

  cout << "Enter the step size for simulation: ";
  cin >> simulationStepSize;
  if (simulationStepSize <= 0) {
    cout << "Invalid input for simulation step size. Exiting simulation.\n";
    return 1;
  }

  Simulation simulation(maxChargers, maxVehicles, totalSimulationHrs,
                        simulationStepSize);
  simulation.insertVehicleType({"Alpha", 120, 320, 0.6, 1.6, 4, 0.25});
  simulation.insertVehicleType({"Bravo", 100, 100, 0.2, 1.5, 5, 0.10});
  simulation.insertVehicleType({"Charlie", 160, 220, 0.8, 2.2, 3, 0.05});
  simulation.insertVehicleType({"Delta", 90, 120, 0.62, 0.8, 2, 0.22});
  simulation.insertVehicleType({"Echo", 30, 150, 0.3, 5.8, 2, 0.61});
  simulation.listVehicleData();

  simulation.distributeVehiclePool();
  simulation.listVehiclePool();

  simulation.startSimulation();
  simulation.listResult();

  return 42;
}