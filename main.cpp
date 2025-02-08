#include "utility.hpp"

vehicleType::vehicleType(const string nameFp, const double cruiseSpeedMphFp,
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
      probabilityOfFaultPerHr(probabilityOfFaultPerHrFp),
      singleChargeMaxRangeMiles(batteryCapacityKwh / energyUseAtCruiseKwhMile),
      singleChargeMaxFlightTimeInHrs(singleChargeMaxRangeMiles /
                                     cruiseSpeedMph),
      cruisePowerKw(batteryCapacityKwh / singleChargeMaxFlightTimeInHrs){};

void vehicleType::display() const {
  cout << "Given parameters:\n";
  cout << "Company Name: " << name << "\n";
  cout << "Cruise Speed (mph): " << cruiseSpeedMph << "\n";
  cout << "Battery Capacity (kWh): " << batteryCapacityKwh << "\n";
  cout << "Time to Charge (hours): " << timeToChargeHrs << "\n";
  cout << "Energy use at Cruise (kWh/mile): " << energyUseAtCruiseKwhMile
       << "\n";
  cout << "Passenger Count: " << passengerCount << "\n";
  cout << "Probability of fault per hour: " << probabilityOfFaultPerHr << "\n";
  cout << "Hidden parameters:\n";
  cout << "Max Range in Single Charge (miles): " << singleChargeMaxRangeMiles
       << "\n";
  cout << "Max Flight time in Single Charge (hours): "
       << singleChargeMaxFlightTimeInHrs << "\n";
  cout << "Cruise Power (kW): " << cruisePowerKw << "\n";
};

vehicle::vehicle(vehicleType *vTypeFp) : vType(vTypeFp) {
  // starting with full capacity
  data.currentBatteryChargeInKwh = vType->batteryCapacityKwh;
}

int main() {
  cout << "Dummy\n";
  return 42;
}