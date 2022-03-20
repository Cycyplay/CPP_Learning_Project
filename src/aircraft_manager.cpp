#include "aircraft_manager.hpp"

#include "config.hpp"

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
                                   [this](std::unique_ptr<Aircraft>& aircraft)
                                   {
                                       try
                                       {
                                           return !aircraft->move();
                                       } catch (const AircraftCrash& crash)
                                       {
                                           // si l'avion se crash, c'est qu'il ne peut plus se déplacer
                                           // la fonction remove_if s'occupera de tout déréférencer
                                           std::cerr << crash.what() << std::endl;
                                           crashed_aircraft_count++;
                                           return true;
                                       }
                                   }),

                    aircrafts.end());
}

void AircraftManager::add_aircraft_to_simulation(std::unique_ptr<Aircraft>& aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

int AircraftManager::get_required_fuel() const
{
    return std::accumulate(aircrafts.begin(), aircrafts.end(), 0,
                           [](unsigned int acc, const std::unique_ptr<Aircraft>& aircraft)
                           {
                               if (aircraft->is_low_on_fuel() && aircraft->is_aircraft_at_terminal())
                               {
                                   return acc + (3000 - aircraft->remaining_fuel());
                               }
                               return acc;
                           });
}