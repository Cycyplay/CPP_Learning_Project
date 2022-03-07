#include "aircraft_manager.hpp"

#include <algorithm>
#include <memory>

void AircraftManager::move()
{
    std::sort(aircrafts.begin(), aircrafts.end(),
              [](std::unique_ptr<Aircraft>& first, std::unique_ptr<Aircraft>& second)
              {
                  if (first->has_terminal() && second->has_terminal())
                  {
                      return first->remaining_fuel() < second->remaining_fuel();
                  }

                  if (first->has_terminal())
                  {
                      return true;
                  }

                  if (second->has_terminal())
                  {
                      return false;
                  }

                  return first->remaining_fuel() < second->remaining_fuel();
              });

    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),
                                   [](std::unique_ptr<Aircraft>& aircraft)
                                   { return !aircraft->move() || aircraft->remaining_fuel() == 0; }),
                    aircrafts.end());
}

void AircraftManager::add_aircraft_to_simulation(std::unique_ptr<Aircraft>& aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}