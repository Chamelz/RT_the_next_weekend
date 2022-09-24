//
// Created by Chamelz on 2022/8/26.
//

#ifndef RAY_TRACING_IN_ONE_WEEKEND_COLOR_H
#define RAY_TRACING_IN_ONE_WEEKEND_COLOR_H
#include "vec3.h"

#include <iostream>

void write_color(std::ostream &out, color pixel_color, int sampler_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples and gamma-correct for gamma=2.0.
    // raising the color to the power 1/gamma, or in our simple case 1/2, which is just square-root
    auto scale = 1.0 / sampler_per_pixel;
    r = sqrt(r * scale);
    g = sqrt(g * scale);
    b = sqrt(b * scale);

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(255.999 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(255.999 * clamp(b, 0.0, 0.999)) << '\n';
}
#endif //RAY_TRACING_IN_ONE_WEEKEND_COLOR_H
