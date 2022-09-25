//
// Created by Chamelz on 2022/9/25.
//

#ifndef RAY_TRACING_IN_ONE_WEEKEND_TEXTURE_H
#define RAY_TRACING_IN_ONE_WEEKEND_TEXTURE_H
#include "rtweekend.h"
#include "perlin.h"
class texture{
public:
    virtual color value(double u, double v, const point3& p) const = 0;
};

class solid_color : public texture{
public:
    solid_color(){}
    solid_color(color c) : color_value(c) {}
    solid_color(double red, double green, double blue) : color_value(color(red, green, blue)) {}

    virtual color value(double u, double v, const point3& p) const override{
        return color_value;
    }

private:
    color color_value;
};

class checker_texture : public texture{
public:
    checker_texture();
    checker_texture(shared_ptr<texture> _even, shared_ptr<texture> _odd) : even(_even), odd(_odd) {}
    checker_texture(color c1, color c2) : even(make_shared<solid_color>(c1)), odd(make_shared<solid_color>(c2)){}

    virtual color value(double u, double v, const point3& p) const override {
        auto sines = sin(10*p.x())*sin(10*p.y())*sin(10*p.z());
        if (sines < 0)
            return odd->value(u, v, p);
        else
            return even->value(u, v, p);
    }
private:
    shared_ptr<texture> odd;
    shared_ptr<texture> even;
};

class noise_texture : public texture{
public:
    noise_texture(){}
    virtual color value(double u, double v, const point3& p) const override{
        return color(1, 1, 1) * noise.nosie(p);
    }

public:
    perlin noise;
};
#endif //RAY_TRACING_IN_ONE_WEEKEND_TEXTURE_H
