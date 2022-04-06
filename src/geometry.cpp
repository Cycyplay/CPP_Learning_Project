#include "geometry.hpp"

#include <iostream>

void test_generic_points()
{
    std::cout << "TEST GENERIC POINTS" << std::endl;

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

    // TEST Point2D with 3 parameters
    //  auto p10 = Point2D { 1, 2, 3 };
    //  std::cout << p10.x() << ", " << p10.y() << ", " << p10.z() << std::endl;

    // TEST Point3D with 2 parameters -> must not compile
    //  auto p11 = Point3D { 1, 2 };
    //  std::cout << p11.x() << ", " << p11.y() << ", " << p11.z() << std::endl;

    // Test Point2D z() access -> must not compile
    // auto p12 = Point2D { 1, 2 };
    // std::cout << p12.x() << ", " << p12.y() << ", " << p12.z() << std::endl;

    std::cout << "END TEST GENERIC POINTS" << std::endl;
}
