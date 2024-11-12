#pragma once

#include "Curves/Definitions.h"
#include "Curves/AbstractCurve.h"



class CURVES_API Ellipse : public AbstractCurve
{
public:
    Ellipse() = delete;
    Ellipse(double radiusA, double radiusB);

    double GetRadiusA() const;
    double GetRadiusB() const;

    virtual Vec3 GetPosition(double t) const override;
    virtual Vec3 GetDerivative(double t) const override;

    virtual CurveType   GetType() const override;
    virtual std::string GetName() const override;


private:
    double radiusA;
    double radiusB;
    constexpr static double posZ = 0.0;
};