#include "vehicle_simulation.hpp"
#include "vehicle_info.hpp"

Simulation::Simulation(const uint32_t maxChargers, const uint32_t maxVehicles,
                       const double totalSimulationHrs,
                       const double simulationStepSize)
    : maxChargers(maxChargers), maxVehicles(maxVehicles),
      totalSimulationHrs(totalSimulationHrs),
      simulationStepSize(simulationStepSize),
      simulationStepSizeHrs(simulationStepSize / 3600.0),
      totalSteps((uint32_t)(totalSimulationHrs / simulationStepSizeHrs)),
      generator(rD()), doubleDistribution(0.0, 1.0),
      chargerSemaphore(maxChargers){};

bool Simulation::insertVehicleType(const VehicleType &vT) {
  if (!vehicleCompanyNames.insert(vT.name).second) {
    cout << "Vehicle: " << vT.name << " already present\n";
    return false;
  }
  vehicleTypes.push_back(vT);
  return true;
}

void Simulation::distributeVehiclePool() {
  uniform_int_distribution<uint32_t> intDistribution(
      0, (uint32_t)vehicleTypes.size() - 1);

  for (uint32_t i = 0; i < maxVehicles; i++) {
    vehicles.emplace_back(vehicleTypes[intDistribution(generator)]);
  }
}

void Simulation::listVehicleData() const {
  cout << "VEHICLES FOR SIMULATION:\n\n\n";
  for (const VehicleType &v : vehicleTypes) {
    v.display();
  }
}

void Simulation::listVehiclePool() const {
  int j = 1;
  cout << "VEHICLE POOL:\n";
  for (int i = 0; i < vehicles.size(); i++) {
    cout << "Vehicle: " << j << " " << vehicles[i].vType.name;
    cout << " | ";
    if (j % 5 == 0) {
      cout << "\n";
    }
    j++;
  }
  cout << "\n";
}

// TODO we can use threadPool here instead of current implementation to avoid
// potential memory leak
void Simulation::startSimulation() {
  cout << "Total steps: " << totalSteps << "\n";

  for (uint32_t i = 0; i < totalSteps; i++) {
    operationThreadPool.clear(); // Clear thread pool per step

    for (Vehicle &v : vehicles) {
      operationThreadPool.emplace_back(&Simulation::vehicleOperation, this,
                                       ref(v));
    }

    // Wait for all threads to complete before proceeding
    for (thread &t : operationThreadPool) {
      if (t.joinable())
        t.join();
    }
  }

  cout << "SIMULATION IS COMPLETE. WE WILL CALCULATE FINAL RESULTS\n";

  calculateIndividualVehicleData();
  calculateAvglVehicleData();
}

void Simulation::vehicleOperation(Vehicle &v) {
  unique_lock<mutex> lock(chargerLock); // Protect shared state
  VehicleState startState = v.data.currentState;

  switch (v.data.currentState) {
  case VehicleState::FLYING:
    handleFlyingState(v);
    break;

  case VehicleState::IN_QUEUE_FOR_CHARGER:
    handleQueueState(v);
    break;

  case VehicleState::CHARGING:
    handleChargingState(v);
    break;
  }

  v.data.lastState = startState;
}

void Simulation::handleFlyingState(Vehicle &v) {
  if (v.data.lastState == VehicleState::CHARGING) {
    (v.data.numberOfFlights)++;
  }

  v.data.flightDurationHrs += simulationStepSizeHrs;
  v.vType.currentRideMiles = (v.vType.cruiseSpeedMph * simulationStepSizeHrs);
  v.data.distanceInMiles += v.vType.currentRideMiles;

  faultCheck(v);

  v.vType.currentRideEnergyUsageKwh =
      (v.vType.currentRideMiles * v.vType.energyUseAtCruiseKwhMile);
  v.data.currentBatteryChargeInKwh -= v.vType.currentRideEnergyUsageKwh;

  if (v.data.currentBatteryChargeInKwh <= 0) {
    chargerStation(v);
  }
}

void Simulation::handleQueueState(Vehicle &v) {
  if (v.data.lastState != VehicleState::IN_QUEUE_FOR_CHARGER) {
    (v.data.numberOfWaitings)++;
  }

  v.data.timeInWaitHrs += simulationStepSizeHrs;
  chargerStation(v);
}

// TODO we can add priority queue in future instead of below implementation
void Simulation::handleChargingState(Vehicle &v) {
  v.data.chargeTimeHrs += simulationStepSizeHrs;

  v.vType.currentSessionChargeEnergyKwh =
      ((v.vType.batteryCapacityKwh / v.vType.timeToChargeHrs) *
       simulationStepSizeHrs);
  v.data.currentBatteryChargeInKwh += v.vType.currentSessionChargeEnergyKwh;

  if (v.data.currentBatteryChargeInKwh >= v.vType.batteryCapacityKwh) {
    chargerSemaphore.release(); // Release charger when done
    v.data.currentState = VehicleState::FLYING;
  }
}

void Simulation::calculateIndividualVehicleData() {
  for (Vehicle &v : vehicles) {
    (v.vType.vehicleData.totalVehicleUsedInPool)++;
    v.vType.vehicleData.totalNumberOfFlights += v.data.numberOfFlights;
    v.vType.vehicleData.totalFlightDurationHrs += v.data.flightDurationHrs;
    v.vType.vehicleData.totalDistanceInMiles += v.data.distanceInMiles;
    v.vType.vehicleData.totalNumberOfFaults += v.data.totalFaultsOccured;
    v.vType.vehicleData.totalNumberOfWaitings += v.data.numberOfWaitings;
    v.vType.vehicleData.totalNumberOfCharges += v.data.numberOfCharges;
    v.vType.vehicleData.totalTimeInWaitHrs += v.data.timeInWaitHrs;
    v.vType.vehicleData.totalChargeTimeHrs += v.data.chargeTimeHrs;
  }
}

void Simulation::calculateAvglVehicleData() {
  for (VehicleType &vT : vehicleTypes) {
    vT.vehicleData.totalNumberOFPassengerMiles =
        vT.vehicleData.totalVehicleUsedInPool * vT.passengerCount *
        vT.vehicleData.totalDistanceInMiles;

    vT.vehicleData.avgDistanceTraveledPerFlight =
        vT.vehicleData.totalDistanceInMiles /
        vT.vehicleData.totalNumberOfFlights;

    vT.vehicleData.avgFlightTimePerFlight =
        vT.vehicleData.totalFlightDurationHrs /
        vT.vehicleData.totalNumberOfFlights;

    vT.vehicleData.avgTimeChargingPerChargeSession =
        vT.vehicleData.totalChargeTimeHrs / vT.vehicleData.totalNumberOfCharges;
  }
}

void Simulation::faultCheck(Vehicle &v) {
  double currentProbabilityOfFault =
      v.vType.probabilityOfFaultPerHr * simulationStepSizeHrs;
  if (doubleDistribution(generator) <= currentProbabilityOfFault) {
    (v.data.totalFaultsOccured)++;
  }
}

void Simulation::chargerStation(Vehicle &v) {
  if (chargerSemaphore.try_acquire()) {
    v.data.currentState = VehicleState::CHARGING;
    (v.data.numberOfCharges)++;
  } else {
    v.data.currentState = VehicleState::IN_QUEUE_FOR_CHARGER;
  }
}

void Simulation::listResult() const {
  cout << "SIMULATION RESULTS:\n";
  for (const VehicleType &vT : vehicleTypes) {
    cout << "Vehicle Type: " << vT.name << "\n";
    cout << "Average Flight Time (Hrs): "
         << vT.vehicleData.avgFlightTimePerFlight << "\n";
    cout << "Average Distance Traveled (Miles): "
         << vT.vehicleData.avgDistanceTraveledPerFlight << "\n";
    cout << "Average Charging Time (Hrs): "
         << vT.vehicleData.avgTimeChargingPerChargeSession << "\n";
    cout << "Total Faults: " << vT.vehicleData.totalNumberOfFaults << "\n";
    cout << "Total Passenger Miles: "
         << vT.vehicleData.totalNumberOFPassengerMiles << "\n";
    cout << "----------------------------------------\n";
#if 0
    cout << "BELOW RESULTS ARE FOR INTERNAL USE\n";
    cout << "Number of vehicles used in the pool: "
         << vT.vehicleData.totalVehicleUsedInPool;
    cout << " | Flights in total: " << vT.vehicleData.totalNumberOfFlights;
    cout << " | Total flight time in Hrs: "
         << vT.vehicleData.totalFlightDurationHrs << "\n";
    cout << "Total miles: " << vT.vehicleData.totalDistanceInMiles;
    cout << " | Number of time charged: "
         << vT.vehicleData.totalNumberOfCharges;
    cout << " | Total charge time in Hrs: " << vT.vehicleData.totalChargeTimeHrs
         << "\n";
    cout << "Number of time in charging queue: "
         << vT.vehicleData.totalNumberOfWaitings;
    cout << " | Total wait time in Hrs: " << vT.vehicleData.totalTimeInWaitHrs
         << "\n\n\n";
#endif //#if 0
  }
}
