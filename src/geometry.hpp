#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>

template <unsigned int dimension, typename type> struct Point
{
    Point() = default;

    Point(type x, type y) : values { x, y }
    {
        std::cout << "ménon" << std::endl;
        static_assert(dimension == 2, "Must be dimension 2 only");
    }
    Point(type x, type y, type z) : values { x, y, z }
    {
        static_assert(dimension == 3, "Must be dimension 3 only");
    }

    type& x()
    {
        static_assert(dimension > 0, "Dimension is too small for x call");
        return values.at(0);
    }
    type x() const
    {

        static_assert(dimension > 0, "Dimension is too small for x call");
        return values.at(0);
    }

    type& y()
    {
        static_assert(dimension > 1, "Dimension is too small for y call");
        return values.at(1);
    }
    type y() const
    {
        static_assert(dimension > 1, "Dimension is too small for y call");
        return values.at(1);
    }

    type& z()
    {

        static_assert(dimension > 2, "Dimension is too small for z call");
        return values.at(2);
    }
    type z() const
    {
        static_assert(dimension > 2, "Dimension is too small for z call");
        return values.at(2);
    }

    std::array<type, dimension> values = {};

    Point<dimension, type>& operator+=(const Point<dimension, type>& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       [](type coord, type other_coord) { return coord + other_coord; });
        return *this;
    }

    Point<dimension, type>& operator-=(const Point<dimension, type>& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       [](type coord, type other_coord) { return coord - other_coord; });
        return *this;
    }

    Point<dimension, type>& operator*=(const type scalar)
    {
        std::transform(values.begin(), values.end(), values.begin(),
                       [scalar](type coord) { return coord * scalar; });
        return *this;
    }

    Point<dimension, type>& operator*=(const Point<dimension, type>& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       [](type coord, type other_coord) { return coord * other_coord; });
        return *this;
    }

    Point<dimension, type> operator+(const Point<dimension, type>& other) const
    {
        Point<dimension, type> result = *this;
        result += other;
        return result;
    }

    Point<dimension, type> operator-(const Point<dimension, type>& other) const
    {
        Point<dimension, type> result = *this;
        result -= other;
        return result;
    }

    Point<dimension, type> operator*(const type scalar) const
    {
        Point<dimension, type> result = *this;
        result *= scalar;
        return result;
    }

    Point<dimension, type> operator*(const Point<dimension, type>& other) const
    {
        Point<dimension, type> result = *this;
        result *= other;
        return result;
    }

    float length() const
    {
        return std::sqrt(std::accumulate(values.begin(), values.end(), 0.f,
                                         [](float acc, float coord) { return acc + coord * coord; }));
    }

    float distance_to(const Point<dimension, type>& other) const { return (*this - other).length(); }

    Point<dimension, type>& normalize(const float target_len = 1.0f)
    {
        const float current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Point<dimension, type>& cap_length(const float max_len)
    {
        assert(max_len > 0);

        const float current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }

    Point<dimension, type> operator-() const { return Point<dimension, type> { -x(), -y(), -z() }; }
};

using Point2D = Point<2, float>;
using Point3D = Point<3, float>;

// our 3D-coordinate system will be tied to the airport: the runway is parallel to the x-axis, the z-axis
// points towards the sky, and y is perpendicular to both thus,
// {1,0,0} --> {.5,.5}   {0,1,0} --> {-.5,.5}   {0,0,1} --> {0,1}
inline Point2D project_2D(const Point3D& p)
{
    return { .5f * p.x() - .5f * p.y(), .5f * p.x() + .5f * p.y() + p.z() };
}

void test_generic_points();
