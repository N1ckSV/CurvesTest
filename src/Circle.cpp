

#include <math.h>

#include "Curves/Circle.h"



Circle::Circle(double Radius) : radius(Radius)
{
#ifdef CURVES_USE_ASSERTIONS
    CURVES_ASSERT(radius > 0, "Radius must be a positive value");
#else
    if(radius <= 0)
        throw std::out_of_range("Radius must be a positive value");
#endif
};

double Circle::GetRadius() const
{
    return radius;
}

Vec3 Circle::GetPosition(double t) const
{
    return { radius * std::cos(t), radius * std::sin(t), posZ };
}

Vec3 Circle::GetDerivative(double t) const
{
    return { - radius * std::sin(t), radius * std::cos(t), 0.0 };
}

CurveType   Circle::GetType() const
{
    return CurveType::Circle;
}

std::string Circle::GetName() const
{
    return "Circle";
}