//
// Created by Wesley Moncrief on 4/9/16.
//

#ifndef RAYTRACING_PLANE_H
#define RAYTRACING_PLANE_H


#include <iostream>
#include <vector>
#include "Point.h"
#include "Pixel.h"
#include "Ray.h"
#include "Color.h"
#include "LightSource.h"
#include "Shape.h"
#include "Sphere.h"


class Plane : public Shape {
    double d;
    Vec3 normal;
    Color plane_color;
    //color of object
    double reflection_coeff;
    double ambient_coeff = .4;
    double diffuse_coeff = .5;
    double specular_refl_coeff = .7;
    double specular_n_value = 5; //this is the exponent
    bool get_intersect_pt(Ray ray, Point &pt);

public:

    Point eye_pt;

    //when two solutions, this returns the minimum

    Plane(Point plane_pt, Vec3 plane_norm, Color color) : normal(plane_norm),
                                                          plane_color(color) {
        normal.normalize();
        d = (plane_norm.x * plane_pt.x) + (plane_norm.y * plane_pt.y) + (plane_norm.z * plane_pt.z);
        d = -d;
        reflection_coeff = 0;
    }

    Plane(Point plane_pt, Vec3 plane_norm, Color color, double reflection_coeff) : normal(plane_norm),
                                                          plane_color(color), reflection_coeff(reflection_coeff) {
        normal.normalize();
        d = (plane_norm.x * plane_pt.x) + (plane_norm.y * plane_pt.y) + (plane_norm.z * plane_pt.z);
        d = -d;
    }

    Plane(Point plane_pt, const Vec3 &plane_norm, const Color &plane_color, double reflection_coeff, double ambient_coeff,
          double diffuse_coeff, double specular_refl_coeff, double specular_n_value) : normal(plane_norm),
                                                                                       plane_color(plane_color),
                                                                                       reflection_coeff(
                                                                                               reflection_coeff),
                                                                                       ambient_coeff(ambient_coeff),
                                                                                       diffuse_coeff(diffuse_coeff),
                                                                                       specular_refl_coeff(
                                                                                               specular_refl_coeff),
                                                                                       specular_n_value(
                                                                                               specular_n_value) {
        normal.normalize();
        d = (plane_norm.x * plane_pt.x) + (plane_norm.y * plane_pt.y) + (plane_norm.z * plane_pt.z);
        d = -d;
    }

    Plane(double d, Vec3 plane_norm, Color color) : d(d), normal(plane_norm),
                                                    plane_color(color) {
        normal.normalize();
    }

//    Sphere(Point center, double radius, const Color &color)
//    : center(center), radius(radius), sphere_color(color) { }

    //this returns a boolean and modifies the pixel so that it has color and location information.
    //Pixel information can be used if a ray intersects multiple
    //objects. it will help determine which one to draw.
    //boolean is useful for when there is no intersection.
    bool intersect(const Ray &ray, const vector<LightSource> &lights, vector<Shape *> shapes, int count, Pixel &pixel);

    Color calc_ambient();

    bool is_occluding(const Ray &shadow_ray, const LightSource &light) const;

    bool is_occluded(Ray shadow_ray, vector<Shape *> shapes, const LightSource &light);

    Color calc_diffuse(Point intersect_pt, const vector<LightSource> &lights, vector<Shape *> shapes);

    Color calc_specular(Point intersect_pt, const vector<LightSource> &lights, vector<Shape *> shapes);
};


#endif //RAYTRACING_PLANE_H
