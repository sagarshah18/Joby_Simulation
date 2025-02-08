#include <cstdint>
#include <iostream>

using namespace std;

const uint32_t MAX_NUMBER_OF_VEHICLE = 20;
const uint32_t MAX_NUMBER_OF_CHARGERS = 3;
const double TOTAL_SIMULATION_IN_HRS = 3.0;
const double SIMULATION_STEP_SIZE_IN_HRS = 1.0 / 3600.0;

// Vehicle state machine
enum class vehicleState {
  FLYING = 0,
  IN_QUEUE_FOR_CHARGER,
  CHARGING,
};

struct totalVehicleData {
  double chargeTimeHrs = 0;
  double timeInWaitHrs = 0;
  uint32_t numberOfCharges = 0;
  uint32_t numberOfWaitings = 0;
  double flightDurationHrs = 0;
  uint32_t numberOfFlights = 0;
  double distanceInMiles = 0;
  uint32_t totalFaultsOccured = 0;

  vehicleState currentState = vehicleState::FLYING;
  vehicleState lastState = vehicleState::CHARGING;

  double currentBatteryChargeInKwh;
};

// Individual structures used for each vehicle
struct individualVehicleData {
  // Given tracking for each vehicle type
  double avgFlightTimePerFlight = 0;
  double avgDistanceTraveledPerFlight = 0;
  double avgTimeChargingPerChargeSession = 0;
  uint32_t totalNumberOfFaults = 0;
  double totalNumberOFPassengerMiles = 0;

  // supporting variables
  double totalChargeTimeHrs = 0;
  double totalTimeInWaitHrs = 0;
  uint32_t totalNumberOfCharges = 0;
  uint32_t totalNumberOfWaitings = 0;
  double totalFlightDurationHrs = 0;
  uint32_t totalNumberOfFlights = 0;
  double totalDistanceInMiles = 0;
  uint32_t totalVehicleUsedInPool = 0;
};

struct vehicleType {
  // Given parameters
  const string name;
  const double cruiseSpeedMph;
  const double batteryCapacityKwh;
  const double timeToChargeHrs;
  const double energyUseAtCruiseKwhMile;
  const uint32_t passengerCount;
  const double probabilityOfFaultPerHr;

  individualVehicleData vehicleData;

  vehicleType(const string nameFp, const double cruiseSpeedMphFp,
              const double batteryCapacityKwhFp, const double timeToChargeHrsFp,
              const double energyUseAtCruiseKwhMileFp,
              const uint32_t passengerCountFp,
              const double probabilityOfFaultPerHrFp);

  // Hidden parameters
  const double singleChargeMaxRangeMiles;
  const double singleChargeMaxFlightTimeInHrs;
  const double cruisePowerKw;

  void display() const;
};

struct vehicle {
  vehicle(vehicleType *vTypeFp);
  vehicleType *vType;
  totalVehicleData data;
};