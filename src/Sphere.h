//
// Created by Wesley Moncrief on 4/5/16.
//

#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

#include <iostream>
#include <vector>
#include "Point.h"
#include "Pixel.h"
#include "Ray.h"
#include "Color.h"
#include "LightSource.h"
#include "Shape.h"

using namespace std;

class Sphere : public Shape {
    Point center;
    double radius;
    Color sphere_color;
    //color of object
    double ambient_coeff = .5;
    double diffuse_coeff = .6;
    double specular_refl_coeff = .7;
    double specular_n_value = 50; //this is the exponent
    bool get_intersect_pt(Ray ray, Point& pt);

public:

    Point eye_pt;

    //when two solutions, this returns the minimum

    Sphere(Point center, double radius, const Color &color)
            : center(center), radius(radius), sphere_color(color) { }

    //this returns a boolean and modifies the pixel so that it has color and location information.
    //Pixel information can be used if a ray intersects multiple
    //objects. it will help determine which one to draw.
    //boolean is useful for when there is no intersection.
    bool intersect(Ray ray, vector<LightSource> lights, vector<Shape*> shapes, int count, Pixel& pixel);

    Color calc_ambient();

    bool is_occluding(Ray shadow_ray, LightSource light);

    bool is_occluded(Ray shadow_ray, vector<Shape *> shapes, LightSource light);

    Color calc_diffuse(Point intersect_pt, vector<LightSource> lights, vector<Shape *> shapes);

    Color calc_specular(Point intersect_pt, vector<LightSource> lights, vector<Shape *> shapes);
};


#endif //RAYTRACING_SPHERE_H
