#pragma once

#include "Curves/Definitions.h"
#include "Curves/AbstractCurve.h"



class CURVES_API Circle : public AbstractCurve
{
public:
    Circle() = delete;
    Circle(double radius);

    double GetRadius() const;

    virtual Vec3 GetPosition(double t) const override;
    virtual Vec3 GetDerivative(double t) const override;

    virtual CurveType   GetType() const override;
    virtual std::string GetName() const override;


private:
    double radius;
    constexpr static double posZ = 0.0;
};