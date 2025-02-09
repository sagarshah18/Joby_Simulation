#pragma once

#include "vehicle_info.hpp"
#include <random>
#include <unordered_set>
#include <vector>

class simulation {
private:
  vector<vehicleType> vehicleTypes;
  vector<vehicle> vehicles;
  unordered_set<string> vehicleCompanyNames;

  // TODO: we can make this user friendly by adding this via command line input
  const uint32_t MAX_NUMBER_OF_CHARGERS = 3;
  const uint32_t MAX_NUMBER_OF_VEHICLE = 20;
  const double TOTAL_SIMULATION_IN_HRS = 3.0;
  const double SIMULATION_STEP_SIZE_IN_HRS = 1.0 / 3600.0;
  const uint32_t NUMBER_OF_STEPS =
      uint32_t(TOTAL_SIMULATION_IN_HRS / SIMULATION_STEP_SIZE_IN_HRS);

  uint32_t numberOfChargerAvailable;

  // random number generation logic
  random_device randomDevice;
  mt19937 generator{randomDevice()};
  uniform_real_distribution<double> doubleDistribution{0.0, 1.0};

  void faultCheck(vehicle &vehicle);
  void charge(vehicle &vehicle);
  void step(vehicle &vehicle);

public:
  simulation() {}

  bool insertVehicleType(vehicleType vehicleTypeFp);
  void distributeVehiclePool();
  void listVehicleData();
  void listVehiclePool();
  void startSimulation();
  void listResult();
};
