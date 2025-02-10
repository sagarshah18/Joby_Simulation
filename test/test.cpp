// vehicle_simulation_test.cpp
#include "../src/vehicle_info.hpp"
#include "../src/vehicle_simulation.hpp"
#include <gtest/gtest.h>

// Test VehicleType initialization
TEST(VehicleTypeTest, Initialization) {
  VehicleType vt("Test", 100.0, 200.0, 2.0, 0.5, 4, 0.1);
  EXPECT_EQ(vt.name, "Test");
  EXPECT_EQ(vt.cruiseSpeedMph, 100.0);
  EXPECT_EQ(vt.batteryCapacityKwh, 200.0);
  EXPECT_EQ(vt.timeToChargeHrs, 2.0);
  EXPECT_EQ(vt.energyUseAtCruiseKwhMile, 0.5);
  EXPECT_EQ(vt.passengerCount, 4u);
  EXPECT_EQ(vt.probabilityOfFaultPerHr, 0.1);
}

// Test Vehicle initialization with full battery
TEST(VehicleTest, BatteryInitialization) {
  VehicleType vt("Test", 100.0, 200.0, 2.0, 0.5, 4, 0.1);
  Vehicle vehicle(vt);
  EXPECT_EQ(vehicle.data.currentBatteryChargeInKwh, 200.0);
}

// Test Simulation insertion of valid and duplicate VehicleTypes
TEST(SimulationTest, InsertVehicleType) {
  Simulation sim(2, 5, 24.0, 3600.0);
  bool success = sim.insertVehicleType({"Alpha", 120, 320, 0.6, 1.6, 4, 0.25});
  EXPECT_TRUE(success);
  success =
      sim.insertVehicleType({"Alpha", 0, 0, 0, 0, 0, 0}); // Duplicate name
  EXPECT_FALSE(success);
}

// Test vehicle pool distribution
TEST(SimulationTest, DistributeVehiclePool) {
  Simulation sim(2, 10, 24.0, 3600.0);
  sim.insertVehicleType({"Alpha", 120, 320, 0.6, 1.6, 4, 0.25});
  sim.distributeVehiclePool();
  sim.listVehiclePool(); // Verify output manually or capture cout
}

// Test charging semaphore logic
TEST(SimulationTest, ChargerAcquisition) {
  Simulation sim(2, 3, 1.0, 1.0); // 1 step
  sim.insertVehicleType(
      {"Test", 100, 100, 0.1, 10.0, 1, 0.0}); // High energy use
  sim.distributeVehiclePool();
  sim.startSimulation();
  // After one step, all vehicles should be in charging state
  // Verify via internal state or add accessors
}

// Test fault occurrence with mocked RNG
TEST(SimulationTest, FaultOccurrence) {
  Simulation sim(1, 1, 1.0, 3600.0);
  sim.insertVehicleType(
      {"Test", 100, 100, 1.0, 0.0, 1, 1.0}); // 100% fault probability
  sim.distributeVehiclePool();
  sim.startSimulation();
  // Check if totalFaultsOccured >=1 (deterministic due to probability=1)
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}