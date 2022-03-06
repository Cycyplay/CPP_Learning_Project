#include "aircraft_manager.hpp"

#include <algorithm>
#include <memory>

void AircraftManager::move()
{
    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),
                                   [](std::unique_ptr<Aircraft>& aircraft)
                                   { return !aircraft->move() || aircraft->remaining_fuel() == 0; }),
                    aircrafts.end());
}

void AircraftManager::add_aircraft_to_simulation(std::unique_ptr<Aircraft>& aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}