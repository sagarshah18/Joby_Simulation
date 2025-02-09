#include "vehicle_info.hpp"

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
  cout << "********************************************************************"
          "******************************************************\n";
  cout << "Given parameters for vehicle: " << name << "\n";
  cout << "********************************************************************"
          "******************************************************\n";
  cout << "Cruise Speed (mph): " << cruiseSpeedMph;
  cout << " | Battery Capacity (kWh): " << batteryCapacityKwh;
  cout << " | Time to Charge (hours): " << timeToChargeHrs << "\n";
  cout << "Energy use at Cruise (kWh/mile): " << energyUseAtCruiseKwhMile;
  cout << " | Passenger Count: " << passengerCount;
  cout << " | Probability of fault per hour: " << probabilityOfFaultPerHr
       << "\n";
  cout << "********************************************************************"
          "******************************************************\n";
  cout << "Hidden parameters for vehicle: " << name << "\n";
  cout << "********************************************************************"
          "******************************************************\n";
  cout << "Max Range in Single Charge (miles): " << singleChargeMaxRangeMiles;
  cout << " | Max Flight time in Single Charge (hours): "
       << singleChargeMaxFlightTimeInHrs;
  cout << " | Cruise Power (kW): " << cruisePowerKw << "\n\n\n";
};

vehicle::vehicle(vehicleType *vTypeFp) : vType(vTypeFp) {
  // starting with full capacity
  data.currentBatteryChargeInKwh = vType->batteryCapacityKwh;
}
