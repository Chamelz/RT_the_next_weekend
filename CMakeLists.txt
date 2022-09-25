cmake_minimum_required(VERSION 3.22)
project(Ray_Tracing_in_One_Weekend)

set(CMAKE_CXX_STANDARD 11)
include_directories(/Users/xyz/include)
include_directories(/Users/xyz/include/glm/)
find_package(Eigen3 CONFIG REQUIRED)

add_executable(Ray_Tracing_in_One_Weekend main.cpp vec3.h color.h ray.h hittable.h sphere.h hittable_list.h rtweekend.h camera.h material.h moving_sphere.h aabb.h bvh.h)
target_link_libraries(Ray_Tracing_in_One_Weekend PRIVATE Eigen3::Eigen)
