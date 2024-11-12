#pragma once

#include "Curves/Definitions.h"
#include "Curves/AbstractCurve.h"



class CURVES_API Helix : public AbstractCurve
{
public:
    Helix() = delete;
    Helix(double radius, double step);

    double GetRadius() const;
    double GetStep() const;

    virtual Vec3 GetPosition(double t) const override;
    virtual Vec3 GetDerivative(double t) const override;

    virtual CurveType   GetType() const override;
    virtual std::string GetName() const override;


private:
    double radius;
    // slope = step/2Pi, 
    // I think we'll call GetStep (see definition) 
    // rarerly than GetPosition or GetDerivative,
    // so we save on divisions
    double slope;
};