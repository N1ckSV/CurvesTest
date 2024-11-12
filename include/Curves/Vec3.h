#pragma once

#include <ostream>


struct Vec3
{
    double x, y, z;

    Vec3() = delete;

    Vec3(double X, double Y, double Z) : x(X), y(Y), z(Z) {};


    friend Vec3 operator + (const Vec3& lh, const Vec3& rh)
    {
        return {lh.x + rh.x, lh.y + rh.y, lh.z + rh.z};
    }

    friend Vec3 operator - (const Vec3& lh, const Vec3& rh)
    {
        return {lh.x - rh.x, lh.y - rh.y, lh.z - rh.z};
    }
    
    friend std::ostream& operator << (std::ostream& os, const Vec3& vec)
    {
        return (os << "{ " << vec.x << ", " << vec.y << ", " << vec.z << " }");
    }

    Vec3& operator += (const Vec3& other)
    {
        return (*this = *this + other);
    }

    Vec3& operator -= (const Vec3& other)
    {
        return (*this = *this - other);
    }

};