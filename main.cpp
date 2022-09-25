#include "rtweekend.h"

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "color.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"
#include "material.h"
#include "moving_sphere.h"
#include "bvh.h"
#define PICPATH "../pic/Image_2_Spheres_on_checkered_ground.ppm"

using namespace std;

// Image
auto aspect_ratio = 16.0 / 9.0;
int img_width = 400;
int img_height = static_cast<int>(img_width / aspect_ratio);
int samples_per_pixel = 100;
const int max_depth = 50;

color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0,0,0);

    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return color(0,0,0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}


hittable_list random_scene() {
    hittable_list world;

    // auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    // world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));
    auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(checker)));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    auto center2 = center + vec3(0, random_double(0,.5), 0);
                    world.add(make_shared<moving_sphere>(
                            center, center2, 0.0, 1.0, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}

tm get_time(){
    time_t rawtime;
    struct tm *ptminfo;
    time(&rawtime);
    ptminfo = localtime(&rawtime);
    return *ptminfo;
}

int main() {
    auto start_time = get_time();
    std::cout << "START_TIME:" << start_time.tm_hour << ':' << start_time.tm_min << ':' << start_time.tm_sec << std::endl;

    // World
    auto world = random_scene();

    // camera
    point3 lookfrom(13,2,3);
    point3 lookat(0,0,0);
    vec3 vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);
    // Render
    ofstream Image;
    Image.open(PICPATH);
    if (Image.fail())
    {
        cout << "Unable to create image.ppm" << endl;
        getchar();
        return 0;
    }

    Image << "P3\n" << img_width << ' ' << img_height << "\n255\n" << endl;
    for(int j=img_height-1;j>=0;j--){
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for(int i=0;i<img_width;i++){
            color pixel_color(0, 0, 0);
            for(int s=0;s<samples_per_pixel;s++){
                auto u = (i + random_double()) / (img_width - 1);
                auto v = (j + random_double()) / (img_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(Image, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
    Image.close();
    auto over_time = get_time();
    int cost_hour = over_time.tm_hour - start_time.tm_hour;
    if(cost_hour < 0)   cost_hour += 24;
    int cost_min = over_time.tm_min - start_time.tm_min;
    if(cost_min < 0){
        cost_hour--;
        cost_min += 60;
    }
    int cost_sec = over_time.tm_sec - start_time.tm_sec;
    if(cost_sec < 0){
        cost_min--;
        cost_sec += 60;
    }
    std::cout << "OVER_TIME:" << over_time.tm_hour << ':' << over_time.tm_min << ':' << over_time.tm_sec << std::endl;
    std::cout << "COST:" << cost_hour << ':' << cost_min << ':' << cost_sec << std::endl;
    return 0;
}
