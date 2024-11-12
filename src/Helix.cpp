

#define _USE_MATH_DEFINES

#include <math.h>

#include "Curves/Helix.h"



Helix::Helix(double Radius, double Step) : radius(Radius), slope(Step/(2 * M_PI))
{
#ifdef CURVES_USE_ASSERTIONS
    CURVES_ASSERT(radius > 0, "Radius must be a positive value");
#else
    if(radius <= 0)
        throw std::out_of_range("Radius must be a positive value");
#endif
};

double Helix::GetRadius() const
{
    return radius;
}

double Helix::GetStep() const
{
    return slope * 2 * M_PI;
}

Vec3 Helix::GetPosition(double t) const
{
    return { radius * std::cos(t), radius * std::sin(t),  slope * t };
}

Vec3 Helix::GetDerivative(double t) const
{
    return { - radius * std::sin(t), radius * std::cos(t),  slope };
}

CurveType   Helix::GetType() const
{
    return CurveType::Helix;
}

std::string Helix::GetName() const
{
    return "Helix";
}
