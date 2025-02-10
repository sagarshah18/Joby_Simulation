# eVTOL Simulation Project

## Overview
This project simulates the operation of electric Vertical Takeoff and Landing (eVTOL) vehicles from five different manufacturers. The simulation tracks key statistics per vehicle type over a user-defined period, including flight time, distance traveled, charging time, faults, and passenger miles. The code is written in C++ with a focus on object-oriented design, modularity, and testability.

## Assumptions and Notes:
1. Each vehicle starts with a fully charged battery.
2. Vehicles instantaneously reach cruise speed.
3. Vehicles are airborne until their battery is depleted, after which they immediately queue for a charger.
4. Only three chargers are available for all vehicles, and each charger can only be used by one vehicle at a time.

## Potential Improvements:
1. Priority Queue for Charging: Implement a priority queue to manage charger access more efficiently.
2. Thread Pool Optimization: Use a more sophisticated thread pool to avoid potential memory leaks.
3. Refactoring: Refactor the database to use a hashmap instead of a raw array for better performance and scalability.

This simulation provides a robust framework for analyzing the performance of different eVTOL aircraft types under various conditions, making it a valuable tool for evaluating the operational efficiency and reliability of these vehicles.

## Features
- **OOP Design**: Utilizes classes (`Simulation`, `VehicleType`, `Vehicle`) to encapsulate data and behavior.
- **Multi-threaded Simulation**: Uses threads to simulate concurrent vehicle operations (flying, charging, queuing).
- **Resource Management**: Limits chargers to three shared resources managed via semaphores.
- **Statistical Tracking**: Records averages and totals per vehicle type for analysis.
- **Randomized Vehicle Distribution**: Assigns 20 vehicles randomly across five types (uniform distribution).

## Requirements
- **C++20 Compiler** (e.g., `g++ 14+`, `clang++ 12+`)
- **CMake** (For build automation)

## Build Instructions
## General Notes
1. Using VS Code for developing this project
2. Using GitKraken to handle Git commit/push
3. Using clang formate from Vs-Code extention to make code prettier
4. Using LLVM from "https://llvm.org/builds/" to support clang formatting
5. Using cmake from VS Code to build the project
6. Download cmake in windows from "https://cmake.org/download/"

## Build Process using Cmake
1. Press Ctrl + Shift + P and type "cmake"
2. Select "CMake: Build" from menu (You can also do this with F7)
3. "vehicleSimulator.exe" will be available under "project directory/build/debug"
