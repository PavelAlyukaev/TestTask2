#pragma once
#include "Point.h"

class Vector
{
public:
    Vector(double x, double y, double z);
    Vector(const Point& a, const Point& b);
    Vector(const Point2D& a, const Point2D& b);

    Vector operator+(const Vector& other) const;
    Vector operator*(double scalar) const;

    [[nodiscard]] double dot(const Vector& other) const;
    [[nodiscard]] Vector cross(const Vector& other) const;
    [[nodiscard]] double length() const;
    [[nodiscard]] Vector normalized() const;
    [[nodiscard]] Point toPoint() const;

    [[nodiscard]] double getX() const;
    [[nodiscard]] double getY() const;
    [[nodiscard]] double getZ() const;

    auto operator <=>(const Vector&) const = default;


private:
    double m_x, m_y, m_z;
};
