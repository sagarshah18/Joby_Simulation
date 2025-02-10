#pragma once

#include <cstdint>
#include <iostream>

using namespace std;

// Vehicle state machine
enum class VehicleState {
  FLYING = 0,
  IN_QUEUE_FOR_CHARGER,
  CHARGING,
};

struct TotalVehicleData {
  double chargeTimeHrs = 0;
  double timeInWaitHrs = 0;
  uint32_t numberOfCharges = 0;
  uint32_t numberOfWaitings = 0;
  double flightDurationHrs = 0;
  uint32_t numberOfFlights = 0;
  double distanceInMiles = 0;
  uint32_t totalFaultsOccured = 0;

  VehicleState currentState = VehicleState::FLYING;
  VehicleState lastState = VehicleState::CHARGING;

  double currentBatteryChargeInKwh;
};

// Individual structures used for each vehicle
struct IndividualVehicleData {
  // Given tracking for each vehicle type
  double avgFlightTimePerFlight = 0;
  double avgDistanceTraveledPerFlight = 0;
  double avgTimeChargingPerChargeSession = 0;
  uint32_t totalNumberOfFaults = 0;
  double totalNumberOFPassengerMiles = 0;

  // supporting variables
  double totalChargeTimeHrs = 0;
  uint32_t totalNumberOfCharges = 0;
  double totalTimeInWaitHrs = 0;
  uint32_t totalNumberOfWaitings = 0;
  double totalFlightDurationHrs = 0;
  uint32_t totalNumberOfFlights = 0;
  double totalDistanceInMiles = 0;
  uint32_t totalVehicleUsedInPool = 0;
};

struct VehicleType {
  // Given parameters
  const string name;
  const double cruiseSpeedMph;
  const double batteryCapacityKwh;
  const double timeToChargeHrs;
  const double energyUseAtCruiseKwhMile;
  const uint32_t passengerCount;
  const double probabilityOfFaultPerHr;

  IndividualVehicleData vehicleData;

  VehicleType(const string nameFp, const double cruiseSpeedMphFp,
              const double batteryCapacityKwhFp, const double timeToChargeHrsFp,
              const double energyUseAtCruiseKwhMileFp,
              const uint32_t passengerCountFp,
              const double probabilityOfFaultPerHrFp);

  // Hidden parameters
  const double singleChargeMaxRangeMiles;
  const double singleChargeMaxFlightTimeInHrs;
  const double cruisePowerKw;
  double currentRideMiles;
  double currentRideEnergyUsageKwh;
  double currentSessionChargeEnergyKwh;

  void display() const;
};

struct Vehicle {
  Vehicle(VehicleType &vTypeFp);
  VehicleType &vType;
  TotalVehicleData data;
};