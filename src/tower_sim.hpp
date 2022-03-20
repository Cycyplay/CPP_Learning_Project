#pragma once

#include "GL/opengl_interface.hpp"
#include "config.hpp"

#include <cstdlib>
#include <ctime>

struct ContextInitializer
{
public:
    ContextInitializer(int argc, char** argv)
    {
        MediaPath::initialize(argv[0]);
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        GL::init_gl(argc, argv, "Airport Tower Simulation");
    }
};

class Airport;
class AircraftManager;
class AircraftFactory;

class TowerSimulation
{
private:
    bool help = false;
    ContextInitializer initializer;
    AircraftFactory* aircraft_factory;

    Airport* airport                  = nullptr;
    AircraftManager* aircraft_manager = nullptr;

    TowerSimulation(const TowerSimulation&) = delete;
    TowerSimulation& operator=(const TowerSimulation&) = delete;

    void create_aircraft() const;

    void create_keystrokes();
    void display_help() const;

    void init_airport();
    void init_aircraft_manager();

    bool has_init_keystroke = false;

public:
    TowerSimulation(int argc, char** argv);
    ~TowerSimulation();

    void launch();
};
