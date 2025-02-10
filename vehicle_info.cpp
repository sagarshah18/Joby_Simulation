#include "vehicle_info.hpp"

VehicleType::VehicleType(const string nameFp, const double cruiseSpeedMphFp,
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

void VehicleType::display() const {
  cout << "***************************************************************"
          "*****\n";
  cout << "Vehicle: " << name << "\n";
  cout << "Cruise Speed (mph): " << cruiseSpeedMph << "\n";
  cout << "Battery Capacity (kWh): " << batteryCapacityKwh << "\n";
  cout << "Time to Charge (hours): " << timeToChargeHrs << "\n";
  cout << "Energy use at Cruise (kWh/mile): " << energyUseAtCruiseKwhMile
       << "\n";
  cout << "Passenger Count: " << passengerCount << "\n";
  cout << "Probability of fault per hour: " << probabilityOfFaultPerHr << "\n";
  cout << "***************************************************************"
          "*****\n";
};

Vehicle::Vehicle(VehicleType &vT) : vType(vT) {
  // starting with full capacity
  data.currentBatteryChargeInKwh = vType.batteryCapacityKwh;
}
