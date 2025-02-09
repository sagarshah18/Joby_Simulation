#include "vehicle_info.hpp"
#include "vehicle_simulation.hpp"

int main() {
  cout << "STARTING SIMULATION\n\n";

  simulation simulationL;
  simulationL.insertVehicleType({"Alpha", 120, 320, 0.6, 1.6, 4, 0.25});
  simulationL.insertVehicleType({"Bravo", 100, 100, 0.2, 1.5, 5, 0.10});
  simulationL.insertVehicleType({"Charlie", 160, 220, 0.8, 2.2, 3, 0.05});
  simulationL.insertVehicleType({"Delta", 90, 120, 0.62, 0.8, 2, 0.22});
  simulationL.insertVehicleType({"Echo", 30, 150, 0.3, 5.8, 2, 0.61});
  simulationL.listVehicleData();

  simulationL.distributeVehiclePool();
  simulationL.listVehiclePool();

  return 42;
}