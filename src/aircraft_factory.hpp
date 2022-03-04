#pragma once

#include "aircraft.hpp"
#include "airport.hpp"

#include <memory>
#include <string>
#include <unordered_set>

struct AircraftType;

class AircraftFactory
{
private:
    using AircraftFlightNumber = std::unordered_set<std::string>;

    const std::string airlines[8]          = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    const static size_t NUM_AIRCRAFT_TYPES = 3;
    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};

    AircraftFlightNumber flight_numbers = {};

    bool exists(const std::string& flight_number) const;

public:
    AircraftFactory()
    {
        {
            aircraft_types[0] = new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } };
            aircraft_types[1] = new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } };
            aircraft_types[2] = new AircraftType { .02f, .1f, .04f, MediaPath { "concorde_af.png" } };
        }
    }

    std::unique_ptr<Aircraft> create_aircraft(Airport* airport, const AircraftType& type);
    std::unique_ptr<Aircraft> create_random_aircraft(Airport* airport);
};