#include "aircraft_manager.hpp"

void AircraftManager::move()
{
    std::unordered_set<Aircraft*> to_remove;

    for (auto& aircraft : aircrafts)
    {
        if (!aircraft->move())
        {
            to_remove.emplace(aircraft);
        }
    }

    for (auto& aircraft : to_remove)
    {
        aircrafts.erase(aircraft);
        delete aircraft;
    }
}

void AircraftManager::add_aircraft_to_simulation(Aircraft* aircraft)
{
    aircrafts.emplace(aircraft);
}