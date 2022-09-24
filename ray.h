//
// Created by Chamelz on 2022/8/26.
//

#ifndef RAY_TRACING_IN_ONE_WEEKEND_RAY_H
#define RAY_TRACING_IN_ONE_WEEKEND_RAY_H
#include "vec3.h"
class ray {
public:
    ray() {}
    ray(const point3& origin, const vec3& direction)
            : orig(origin), dir(direction), tm(0)
    {}

    ray(const point3& origin, const vec3& direction, double time)
            : orig(origin), dir(direction), tm(time)
    {}

    point3 origin() const  { return orig; }
    vec3 direction() const { return dir; }
    double time() const    { return tm; }

    point3 at(double t) const {
        return orig + t*dir;
    }

public:
    point3 orig;
    vec3 dir;
    double tm;
};
#endif //RAY_TRACING_IN_ONE_WEEKEND_RAY_H
