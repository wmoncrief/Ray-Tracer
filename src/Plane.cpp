//
// Created by Wesley Moncrief on 4/9/16.
//

#include "Plane.h"

bool Plane::get_intersect_pt(Ray ray, Point &pt) {
    //t = -(Po dot N + d) / (V dot N), V is ray vector, N is plane vector, Po is ray point
    //P = Po + tV

    //t = -(ray.point dot normal + d) / (ray.vec dot N)
    double PoDotN = Vec3(ray.start).dotProduct(normal);
    double numerator = -1 *(PoDotN + d);
    double denom = ray.V.dotProduct(normal);
    double t = numerator / denom;
    if (t <0 ) return false; // no intersection. https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html
    Vec3 dist = ray.V.scaled(t);
    pt = Point(ray.start.x + dist.x, ray.start.y + dist.y, ray.start.z + dist.z);

    return true;
}

bool Plane::intersect(Ray ray, vector<LightSource> lights, vector<Shape *> shapes, Pixel &pixel) {
    Point intersect_pt;
    if (!get_intersect_pt(ray, intersect_pt)) return false; //else the intersect_pt is updated

    //color is Direct (ambient + diffuse + specular) + reflected + //refracted...
    //if i add attenuation to plane, should I add it here?
    Color ambient = calc_ambient();
    Color diffuse = calc_diffuse(intersect_pt, lights, shapes);
    Color direct_color = ambient.sum(diffuse);
    Color specular = calc_specular(intersect_pt, lights, shapes);
    direct_color = direct_color.sum(specular);
//    pixel = Pixel(intersect_pt, direct_color);
    pixel = Pixel(intersect_pt, direct_color);
    return true;
}

Color Plane::calc_ambient() {
    return Color(plane_color.scaled(ambient_coeff));
}

bool Plane::is_occluded(Ray shadow_ray, vector<Shape *> shapes, LightSource light) {
    return false;
}

bool Plane::is_occluding(Ray shadow_ray, LightSource light) {
    return false;
}

Color Plane::calc_diffuse(Point intersect_pt, vector<LightSource> lights, vector<Shape *> shapes) {
    Color total_diffuse = Color(0, 0, 0);

    //run this for each light source. Light sources are additive in their effects.
    for (int i = 0; i < lights.size(); ++i) {
        LightSource ls = lights.at(i);
        //vec3 , from intersect pt to lightsource.pt
        Vec3 occlu_vec(ls.light_center.x - intersect_pt.x, ls.light_center.y - intersect_pt.y,
                       ls.light_center.z - intersect_pt.z);

        if (!is_occluded(Ray(intersect_pt, occlu_vec), shapes, ls)) {
            //I = intensity of point light * diffuse reflection coefficient * (light vector dotted with normal vector)

            //should L, N be unit vectors? N should probably be...
            //N is normal

            //L is lightsource vector
            Vec3 L = Vec3(ls.light_center.x - intersect_pt.x, ls.light_center.y - intersect_pt.y,
                          ls.light_center.z - intersect_pt.z);
            L.normalize();
            double LdotN = L.dotProduct(normal);
            double coeff = diffuse_coeff * LdotN;
            total_diffuse = total_diffuse.sum(ls.light_color.scaled(coeff));
        }
    }

    return total_diffuse;
}

Color Plane::calc_specular(Point intersect_pt, vector<LightSource> lights, vector<Shape *> shapes) {
    //i'm assuming all the vectors described are normalized
    //I = C * spec_refl_coeff * (R dot E) ^spec_n_value

    Vec3 E(eye_pt.x - intersect_pt.x, eye_pt.y - intersect_pt.y, eye_pt.z - intersect_pt.z);
    E.normalize();

    Color total_specular = Color(0, 0, 0);

    for (int i = 0; i < lights.size(); ++i) { //lights from different sources are additive
        LightSource ls = lights.at(i);

        Vec3 occlu_vec(ls.light_center.x - intersect_pt.x, ls.light_center.y - intersect_pt.y,
                       ls.light_center.z - intersect_pt.z);

        if (!is_occluded(Ray(intersect_pt, occlu_vec), shapes, ls)) {
            Vec3 L = Vec3(ls.light_center.x - intersect_pt.x, ls.light_center.y - intersect_pt.y,
                          ls.light_center.z - intersect_pt.z);
            L.normalize();

            //using normal for N
            double n_coef = 2 * L.dotProduct(normal);
            Vec3 R(n_coef * normal.x - L.x, n_coef * normal.y - L.y, n_coef * normal.z - L.z);
            R.normalize(); //not sure if this is necessary or not

            double RdotE = R.dotProduct(E);
            double powerRdotE = pow(RdotE, specular_n_value);
            double full_coeff = specular_refl_coeff * powerRdotE;
            if (full_coeff < 0) full_coeff = 0;

            total_specular = total_specular.sum(ls.light_color.scaled(full_coeff));
        }

    }

    return total_specular;
}













