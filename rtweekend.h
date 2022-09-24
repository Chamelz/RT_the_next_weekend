//
// Created by Chamelz on 2022/9/4.
//

#ifndef RAY_TRACING_IN_ONE_WEEKEND_RTWEEKEND_H
#define RAY_TRACING_IN_ONE_WEEKEND_RTWEEKEND_H
#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

// Using
using std::sqrt;
using std::make_shared;
using std::shared_ptr;

// Constants

const double INF = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;
const double infinity = std::numeric_limits<double>::infinity();

// Utility Funcution
inline double degrees_to_radians(double degrees){
    return (degrees/180.0 * PI);
}
inline double random_double(){
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}
inline double random_double(double min, double max){
    return min + (max-min)*random_double();
}
inline double clamp(double x, double min, double max){
    if(x < min) return min;
    if(x > max) return max;
    return x;
}

// Common Headers
#include "ray.h"
#include "vec3.h"
#include "hittable.h"

#endif //RAY_TRACING_IN_ONE_WEEKEND_RTWEEKEND_H
