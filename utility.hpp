

#include <cstdint>
#include <iostream>


using namespace std;

struct individualVehicleData {
  // Given tracking for each vehicle type
  double avgFlightTimePerFlight = 0;
  double avgDistanceTraveledPerFlight = 0;
  double avgTimeChargingPerChargeSession = 0;
  uint32_t totalNumberOfFaults = 0;
  double totalNumberOFPassengerMiles = 0;
};

struct vehicle {
  // Given parameters
  const string name;
  const double cruiseSpeedMph;
  const double batteryCapacityKwh;
  const double timeToChargeHrs;
  const double energyUseAtCruiseKwhMile;
  const uint32_t passengerCount;
  const double probabilityOfFaultPerHr;

  individualVehicleData vehicleData;

  vehicle(const string nameFp, const double cruiseSpeedMphFp,
          const double batteryCapacityKwhFp, const double timeToChargeHrsFp,
          const double energyUseAtCruiseKwhMileFp,
          const uint32_t passengerCountFp,
          const double probabilityOfFaultPerHrFp);
};