#pragma once

#include "Curves/Vec3.h"


enum class CurveType
{
    Unknown,
    Circle,
    Ellipse,
    Helix,
    Size
};



class CURVES_API AbstractCurve
{
public:
    virtual Vec3 GetPosition(double) const = 0;
    virtual Vec3 GetDerivative(double) const = 0;

    // 2 ways to recognize curve type without typeid()
    virtual CurveType   GetType() const = 0;
    virtual std::string GetName() const = 0;

    virtual ~AbstractCurve() = default;

};
