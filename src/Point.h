//
// Created by Wesley Moncrief on 4/5/16.
//

#ifndef RAYTRACING_POINT_H
#define RAYTRACING_POINT_H


#include <cmath>

class Point {
public:
    double x;
    double y;
    double z;

    Point() { x = 0, y = 0, z = 0;}

    Point(double x, double y, double z) : x(x), y(y), z(z) { }


    double distance(Point pt) const {
        return sqrt((pt.x - x) * (pt.x - x) + (pt.y - y) * (pt.y - y) + (pt.z - z) * (pt.z - z));
    }
};


#endif //RAYTRACING_POINT_H
