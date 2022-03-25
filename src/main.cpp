#include "geometry.hpp"
#include "tower_sim.hpp"

void test_generic_points()
{
    Point<3, int> p1;
    Point<3, int> p2;
    auto p3 = p1 + p2;
    p1 += p3;
    p1 *= 3; // ou 3.f, ou 3.0 en fonction du type de Point

    Point<3, float> p4;
    Point<3, float> p5;
    auto p6 = p4 + p5;
    p4 += p6;
    p4 *= 3.f; // ou 3.f, ou 3.0 en fonction du type de Point

    Point<2, double> p7;
    Point<2, double> p8;
    auto p9 = p7 + p8;
    p7 += p9;
    p7 *= 3.0; // ou 3.f, ou 3.0 en fonction du type de Point
}

int main(int argc, char** argv)
{
    test_generic_points();

    TowerSimulation simulation { argc, argv };
    simulation.launch();

    return 0;
}