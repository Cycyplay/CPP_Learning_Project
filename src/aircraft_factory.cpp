#include "aircraft_factory.hpp"

#include "airport_type.hpp"
#include "geometry.hpp"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>

bool AircraftFactory::exists(const std::string& flight_number) const
{
    return flight_numbers.find(flight_number) != flight_numbers.end();
}

std::unique_ptr<Aircraft> AircraftFactory::create_aircraft(Airport& airport, const AircraftType& type)
{
    assert(&airport); // make sure the airport is initialized before creating aircraft

    std::string flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    while (exists(flight_number))
    {
        flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    }

    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();

    flight_numbers.emplace(flight_number);
    return std::make_unique<Aircraft>(type, flight_number, start, direction, *(&airport.get_tower()));
}

std::unique_ptr<Aircraft> AircraftFactory::create_random_aircraft(Airport& airport)
{
    return create_aircraft(airport, *(aircraft_types[rand() % 3]));
}

void AircraftFactory::get_airlines_aircraft_count(const unsigned int airline) const
{
    if (airline >= airlines.size())
    {
        std::cout << "Invalid input for 'get_airlines_aircraft_count'" << std::endl;
    }

    std::cout << airlines[airline] << " : "
              << std::count_if(flight_numbers.begin(), flight_numbers.end(),
                               [this, airline](std::string flight)
                               { return airlines[airline].compare(0, 2, flight, 0, 2) == 0; })
              << std::endl;
}