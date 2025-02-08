#include "utility.hpp"

vehicle::vehicle(const string nameFp, const double cruiseSpeedMphFp,
                 const double batteryCapacityKwhFp,
                 const double timeToChargeHrsFp,
                 const double energyUseAtCruiseKwhMileFp,
                 const uint32_t passengerCountFp,
                 const double probabilityOfFaultPerHrFp)
    : name(nameFp), cruiseSpeedMph(cruiseSpeedMphFp),
      batteryCapacityKwh(batteryCapacityKwhFp),
      timeToChargeHrs(timeToChargeHrsFp),
      energyUseAtCruiseKwhMile(energyUseAtCruiseKwhMileFp),
      passengerCount(passengerCountFp),
      probabilityOfFaultPerHr(probabilityOfFaultPerHrFp) {}

int main() {
  cout << "Dummy\n";
  return 42;
}