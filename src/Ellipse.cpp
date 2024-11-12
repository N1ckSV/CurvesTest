

#include <math.h>

#include "Curves/Ellipse.h"


Ellipse::Ellipse(double RadiusA, double RadiusB) : radiusA(RadiusA), radiusB(RadiusB)
{
#ifdef CURVES_USE_ASSERTIONS
    CURVES_ASSERT((radiusA > 0 && radiusB > 0), "RadiusA and RadiusB must be positive values");
#else
    if(radiusA <= 0 || radiusB <= 0)
        throw std::out_of_range("RadiusA and RadiusB must be positive values");
#endif
};

double Ellipse::GetRadiusA() const
{
    return radiusA;
}

double Ellipse::GetRadiusB() const
{
    return radiusB;
}

Vec3 Ellipse::GetPosition(double t) const
{
    return { radiusA * std::cos(t),  radiusB * std::sin(t), posZ };
}

Vec3 Ellipse::GetDerivative(double t) const
{
    return { - radiusA * std::sin(t),  radiusB * std::cos(t), 0 };
}

CurveType   Ellipse::GetType() const
{
    return CurveType::Ellipse;
}

std::string Ellipse::GetName() const
{
    return "Ellipse";
}
