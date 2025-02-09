#include "vehicle_simulation.hpp"
#include "vehicle_info.hpp"

bool simulation::insertVehicleType(vehicleType vT) {
  if (!vehicleCompanyNames.insert(vT.name).second) {
    cout << "Vehicle: " << vT.name << " already present\n";
    return false;
  }
  vehicleTypes.push_back(vT);
  return true;
}

void simulation::distributeVehiclePool() {
  uniform_int_distribution<uint32_t> intDistribution(
      0, (uint32_t)vehicleTypes.size() - 1);

  for (uint32_t i = 0; i < MAX_NUMBER_OF_VEHICLE; i++) {
    vehicle vehicleForPool(&vehicleTypes[intDistribution(generator)]);
    vehicles.emplace_back(vehicleForPool);
  }
}

void simulation::listVehicleData() {
  cout << "VEHICLES FOR SIMULATION:\n\n\n";
  for (const vehicleType &v : vehicleTypes) {
    v.display();
  }
}

void simulation::listVehiclePool() {
  int j = 1;
  cout << "VEHICLE POOL:\n";
  for (int i = 0; i < vehicles.size(); i++) {
    cout << "Vehicle: " << j << " " << vehicles[i].vType->name;
    cout << " | ";
    if (!(j % 5) || !(j % 10) || !(j % 15) || !(j % 20)) {
      cout << "\n";
    }
    j++;
  }
}

// void simulation::startSimulation()
// {
//     cout << "Total steps: " << NUMBER_OF_STEPS << "\n";

//     for(uint32_t i = 0; i < NUMBER_OF_STEPS; i++)
//     {
//         for(vehicle& v : vehicles)
//         {

//         }
//         step()
//     }
// }