#pragma once

#include "aircraft.hpp"

#include <memory>

class AircraftManager : public GL::DynamicObject
{
private:
    using SimulationAircrafts = std::vector<std::unique_ptr<Aircraft>>;

    SimulationAircrafts aircrafts = {};

public:
    AircraftManager() {}

    void move() override;

    void add_aircraft_to_simulation(std::unique_ptr<Aircraft>& aircraft);

    unsigned int get_required_fuel() const;
};