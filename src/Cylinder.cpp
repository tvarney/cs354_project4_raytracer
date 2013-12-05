
#include "Cylinder.hpp"

#include <cmath>
#include <iostream>
#include "Geometry.hpp"

using namespace cs354;

Cylinder::Cylinder(const Point3d c, double r, double hl, const Material &m) :
    Object(m), center(c), radius(r), half_len(hl)
{ }
Cylinder::~Cylinder() { }

bool Cylinder::intersect(const Ray &source, Ray &result) const {
    double t0, t1;
    if(!get_dist(source, &t0, &t1)) {
        return false;
    }
    
    double t;
    if(t0 < 0) {
        if(t1 < 0) {
            std::cout << "Rejected after finding intersections" << std::endl;
            return false;
        }else {
            t = t0;
        }
    }else {
        if(t1 < 0) {
            t = t0;
        }else {
            t = (t1 < t0 ? t1 : t0);
        }
    }
    
    result = source.project(t);
    result.direction = Vector3d(result.origin - center);
    result.direction.y = 0;
    result.direction = normalize(result.direction);
    std::cout << "Cylinder intersection on object " << (void *)this <<
        "at " << result.origin << std::endl;
    return true;
}

bool Cylinder::bisect(const Ray &source, Ray &result) const {
    double t0, t1;
    if(!get_dist(source, &t0, &t1)) {
        return false;
    }
    
    double t;
    if(t0 < 0) {
        if(t1 < 0) {
            return false;
        }else {
            t = t0;
        }
    }else {
        if(t1 < 0) {
            t = t0;
        }else {
            /* Choose largest */
            t = (t1 > t0 ? t1 : t0);
        }
    }
    
    result = source.project(t);
    result.direction = Vector3d(result.origin - center);
    result.direction.y = 0;
    result.direction = normalize(result.direction);
    return true;
}

bool Cylinder::get_dist(const Ray &source, double *t0, double *t1) const {
    Ray r = source.transform(center);
    r.origin.y = 0;
    r.direction.y = 0;
    double a = dot(r.direction, r.direction);
    double b = dot(r.direction, r.origin);
    double c = dot(r.origin, r.origin) - radius * radius;
    
    double desc = b * b - 4 * a * c;
    if(desc < 0.0) {
        return false;
    }
    
    double denom = 2 * a;
    if(denom == 0.0) {
        return false;
    }
    
    desc = std::sqrt(desc);
    *t0 = (-b + desc) / denom;
    *t1 = (-b - desc) / denom;
    return true;
}

Cylinder * Cylinder::clone() const {
    return new Cylinder(center, radius, half_len);
}
