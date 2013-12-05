
#include "Sphere.hpp"

#include <cstdio>
#include "Geometry.hpp"

using namespace cs354;

Sphere::Sphere(const Point3d &pos, double radius, const Material &material) :
    Object(material), pos(pos), radius(radius)
{ }
Sphere::Sphere(const Sphere &source) :
    Object(source.mat), pos(source.pos), radius(source.radius)
{ }

Sphere::~Sphere() { }

bool Sphere::intersect(const Ray &ray, Ray &result) const {
    Ray r = ray.transform(pos);
    double a = r.direction.dot(ray.direction);
    double b = 2.0 * (r.direction.x * r.origin.x + r.direction.y * r.origin.y +
                      r.direction.z * r.origin.z);
    double c = (r.origin.x * r.origin.x + r.origin.y * r.origin.y +
                r.origin.z * r.origin.z) - radius * radius;
    
    double disc = b*b - 4 * a * c;
    if(disc < 0) {
        return false;
    }
    
    double disc_sqrt = std::sqrt(disc);
    double q;
    if(b < 0) {
        q = (-b - disc_sqrt) * 0.5;
    }else {
        q = (-b + disc_sqrt) * 0.5;
    }
    
    double t0 = q / a;
    float t1 = c / q;
    
    if(t1 <= 0) {
        return false;
    }
    double t = (t0 < 0 ? t1 : t0);
    
    result.origin = ray.origin + t * ray.direction;
    result.direction = normalize(result.origin - pos);
    return true;
}

bool Sphere::bisect(const Ray &ray, Ray &result) const {
    Ray r = ray.transform(pos);
    double a = dot(r.direction, ray.direction);
    double b = 2.0 * (r.direction.x * r.origin.x + r.direction.y * r.origin.y +
                      r.direction.z * r.origin.z);
    double c = (r.origin.x * r.origin.x + r.origin.y * r.origin.y +
                r.origin.z * r.origin.z) - radius * radius;
    
    double disc = b*b - 4 * a * c;
    if(disc < 0) {
        return false;
    }
    
    double disc_sqrt = std::sqrt(disc);
    double q;
    if(b < 0) {
        q = (-b - disc_sqrt) * 0.5;
    }else {
        q = (-b + disc_sqrt) * 0.5;
    }
    
    double t0 = q / a;
    double t1 = c / q;
    
    if(t1 < 0) {
        return false;
    }
    
    double t = (t0 <= 0 ? t1 : t0);
    
    result.origin = ray.origin + ray.direction * t;
    result.direction = (result.origin - pos) / radius;
    
    return true;
}

void Sphere::move(Vector3d direction) {
    pos = pos + direction;
}

Sphere * Sphere::clone() const {
    return new Sphere(pos, radius, mat);
}
