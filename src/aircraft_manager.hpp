#pragma once

#include "aircraft.hpp"

class AircraftManager : public GL::DynamicObject
{
private:
    using SimulationAircrafts = std::unordered_set<Aircraft*>;

    SimulationAircrafts aircrafts = {};

public:
    AircraftManager() {}

    void move() override;

    void add_aircraft_to_simulation(Aircraft* aircraft);
};