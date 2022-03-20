#pragma once

#include "aircraft.hpp"

#include <memory>

class AircraftManager : public GL::DynamicObject
{
private:
    using SimulationAircrafts = std::vector<std::unique_ptr<Aircraft>>;

    SimulationAircrafts aircrafts = {};

    unsigned int crashed_aircraft_count = 0;

public:
    AircraftManager() {}

    void move() override;

    void add_aircraft_to_simulation(std::unique_ptr<Aircraft>& aircraft);

    int get_required_fuel() const;

    unsigned int get_crashed_aircraft_count() const { return crashed_aircraft_count; };
};