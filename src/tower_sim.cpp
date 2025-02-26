#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "aircraft.hpp"
#include "aircraft_factory.hpp"
#include "aircraft_manager.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <utility>

using namespace std::string_literals;

TowerSimulation::TowerSimulation(int argc, char** argv) :
    help { (argc > 1) && (std::string { argv[1] } == "--help"s || std::string { argv[1] } == "-h"s) },
    initializer { ContextInitializer(argc, argv) },
    aircraft_factory { new AircraftFactory() }
{
    create_keystrokes();
}

TowerSimulation::~TowerSimulation()
{
    delete airport;
}

void TowerSimulation::create_aircraft() const
{
    assert(aircraft_manager);

    auto aircraft = aircraft_factory->create_random_aircraft(*airport);
    auto move_ptr = std::move(aircraft);

    aircraft_manager->add_aircraft_to_simulation(move_ptr);
}

void TowerSimulation::create_keystrokes()
{
    assert(!has_init_keystroke);

    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c', [this]() { create_aircraft(); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });

    GL::keystrokes.emplace(':', []() { GL::ticks_per_sec++; });
    GL::keystrokes.emplace(';', []() { GL::ticks_per_sec--; });
    GL::keystrokes.emplace('p', []() { GL::toggle_pause(); });

    GL::keystrokes.emplace('m',
                           [this]()
                           {
                               std::cout << "Crashed Aircraft Count : "
                                         << this->aircraft_manager->get_crashed_aircraft_count() << std::endl;
                           });

    unsigned int airlines_count = aircraft_factory->get_airlines_count();
    for (unsigned int i = 0; i < airlines_count; i++)
    {
        GL::keystrokes.emplace(i + '0', [this, i]() { aircraft_factory->print_airlines_aircraft_count(i); });
    }

    has_init_keystroke = true;
}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    for (const auto& [key, lambda] : GL::keystrokes)
    {
        std::cout << key << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    assert(airport == nullptr);

    airport = new Airport { one_lane_airport, Point3D { 0, 0, 0 },
                            new img::Image { one_lane_airport_sprite_path.get_full_path() } };

    GL::move_queue.emplace(airport);
}

void TowerSimulation::init_aircraft_manager()
{
    assert(aircraft_manager == nullptr);

    aircraft_manager = new AircraftManager();

    GL::move_queue.emplace(aircraft_manager);
}

void TowerSimulation::launch()
{
    if (help)
    {
        display_help();
        return;
    }

    init_airport();
    init_aircraft_manager();
    airport->set_aircraft_manager(aircraft_manager);

    GL::loop();
}
