

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib>
#include <vector>
#include <memory>
#include <chrono>
#include <random>
#include <iomanip>
#include <algorithm>
#include <type_traits>

#include <omp.h>

#include "Curves/Circle.h"
#include "Curves/Ellipse.h"
#include "Curves/Helix.h"

#define RANDOM (static_cast<double>(rand()) / RAND_MAX)

#define MAX_RADIUS 1000
#define MIN_RADIUS 1
#define MAX_STEP 1000
#define MAX_STEP 1000

#define CURVES_COUNT_DEFAULT 100

#define RANDOM_RADIUS (RANDOM * (MAX_RADIUS - MIN_RADIUS) + MIN_RADIUS)
#define RANDOM_STEP (RANDOM * MAX_STEP)

using SharedCurv = std::shared_ptr<AbstractCurve>;
using SharedCircle = std::shared_ptr<Circle>;

using CurvesVec = std::vector<SharedCurv>;
using CirclesVec = std::vector<SharedCircle>;

void FillWithRandomCurves(CurvesVec& vec, size_t count)
{
    srand(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    vec.resize(count);
    
    for(auto& curv : vec)
    {
        switch(rand() % 3)
        {
        case 0:
            curv = std::make_shared<Circle>(RANDOM_RADIUS);
            break;
        case 1:
            curv = std::make_shared<Ellipse>(RANDOM_RADIUS, RANDOM_RADIUS);
            break;
        case 2:
            curv = std::make_shared<Helix>(RANDOM_RADIUS, RANDOM_STEP);
            break;
        default:
            CURVES_ASSERT(false, "default case must be unreachable here");
        }

    }
}

template<class T>
void Print(const std::vector<std::shared_ptr<T>>& vec, double t)
{
    for(const auto& curv : vec)
    {
        std::cout 
        << "Name: "
        << curv->GetName()
        << "\tPos: "
        << std::fixed
        << curv->GetPosition(t)
        << "\tDer: "
        << curv->GetDerivative(t)
        << std::endl;
    }
}

// 4 ways available : 
// typeid;
// dynamic_cast;
// GetType;
// GetName.
//
// GetType and GetName may fail if 
// library user creates their own class 
// and returns information from Circle.
//
// typeid is only for exact Circle class 
// but not for its derived classes.
//
// check with dynamic_cast can also pass 
// Circle's derived classes
inline bool IsCircle(const AbstractCurve& curv)
{
    return (typeid(curv) == typeid(Circle));
    // or
    // return (curv.GetType() == CurveType::Circle);
    // or
    // return (curv.GetName() == "Circle");
    // or
    //return dynamic_cast<const Circle*>(&curv);
}

void FillterCircles(const CurvesVec& in, CirclesVec& out)
{
    out.reserve(in.size()/3);
    for (auto& curv : in)
    {
        if(IsCircle(*curv))
            out.push_back(std::static_pointer_cast<Circle>(curv));
    }
}





int main(int argc, const char* argv[])
{
    // can specify how many curves to process
    size_t curvesCount;
    if(argc > 1)
    {
        curvesCount = static_cast<size_t>(atoll(argv[1]));
        if(!curvesCount)
        {
            std::cerr << "Bad argument given";
            return -1;
        }
    }
    else
        curvesCount = CURVES_COUNT_DEFAULT;

#ifndef CURVES_USE_ASSERTIONS
    try
    {
        Circle(-2.0);
    }
    catch(const std::out_of_range& e)
    {
        std::cout << "Caught planned exception: " << e.what() << std::endl << std::endl;
    }
#endif

    CurvesVec fullVector; // std::vector< std::shared_ptr<AbstractCurve> >
    CirclesVec filteredVector; // std::vector <std::shared_ptr<Circle> >

    // filling fullVector
    FillWithRandomCurves(fullVector, curvesCount);

    // skip printing if there are too many curves
    if(curvesCount <= 200)
    {
        std::cout << "\nFull Vector :\n\n";
        Print(fullVector, M_PI/4);
    }


    // filtering circles
    FillterCircles(fullVector, filteredVector);
    
    // ascending sort 
    std::sort(filteredVector.begin(), filteredVector.end(),
        [](const SharedCircle& cur1, const SharedCircle& cur2) 
        { 
            return cur1->GetRadius() < cur2->GetRadius();
        });
    
    
    // skip printing if there are too many curves
    if(curvesCount <= 200)
    {
        std::cout << "\nFiltered and sorted Circles Vector :\n\n";
        Print(filteredVector, M_PI/4);
    }


    double radiusSum = 0;
    double radiusSumOMP = 0;

    using namespace std::chrono;

    // for comparing time parallel vs single thread
    decltype(high_resolution_clock::now()) tp1, tp2;
    
    tp1 = high_resolution_clock::now();

    long long signedSize = static_cast<long long int>(filteredVector.size());

    // explicitly avoiding optimization 
    #pragma omp parallel for num_threads(1)
    for(long long int i = 0; i < signedSize; ++i)
    {
        radiusSum += filteredVector[i]->GetRadius();
    }
    
    tp2 = high_resolution_clock::now();
    std::cout << "Time OpenMP single thread:    " << duration_cast<nanoseconds>(tp2 - tp1).count() << " ns\n";

    tp1 = high_resolution_clock::now();

    // explicitly making OMP optimization
    // for low curvesCount this one is slower.
    // potential cache race in std::vector
    #pragma omp parallel for reduction(+:radiusSumOMP)
    for(long long int i = 0; i < signedSize; ++i)
    {
        radiusSumOMP += filteredVector[i]->GetRadius();
    }

    tp2 = high_resolution_clock::now();

    
    std::cout << "Time OpenMP parralel threads: " << duration_cast<nanoseconds>(tp2 - tp1).count() << " ns\n";


    
    std::cout << "\nRadius Sum single  : " << radiusSum;
    std::cout << "\nRadius Sum parralel: " << radiusSumOMP;
    
    
    return 0;

}




