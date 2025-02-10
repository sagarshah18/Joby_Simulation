#pragma once

#include "vehicle_info.hpp"
#include <atomic>
#include <mutex>
#include <random>
#include <semaphore>
#include <thread>
#include <unordered_set>
#include <vector>

class Simulation {
private:
  vector<VehicleType> vehicleTypes;
  vector<Vehicle> vehicles;
  unordered_set<string> vehicleCompanyNames;

  const uint32_t maxChargers;
  const uint32_t maxVehicles;
  const double totalSimulationHrs;
  const double simulationStepSize;
  const double simulationStepSizeHrs;
  const uint32_t totalSteps;

  // random number generation logic
  random_device rD;
  mt19937 generator;
  uniform_real_distribution<double> doubleDistribution;

  counting_semaphore<> chargerSemaphore;
  vector<thread> operationThreadPool;
  mutex chargerLock;

  void faultCheck(Vehicle &v);
  void chargerStation(Vehicle &v);
  void vehicleOperation(Vehicle &v);
  void calculateIndividualVehicleData();
  void calculateAvglVehicleData();
  void handleFlyingState(Vehicle &v);
  void handleQueueState(Vehicle &v);
  void handleChargingState(Vehicle &v);

public:
  Simulation(const uint32_t maxChargers, const uint32_t maxVehicles,
             const double totalSimulationHrs,
             const double simulationStepSizeHrs);

  bool insertVehicleType(const VehicleType &vT);
  void distributeVehiclePool();
  void listVehicleData() const;
  void listVehiclePool() const;
  void startSimulation();
  void listResult() const;
};
