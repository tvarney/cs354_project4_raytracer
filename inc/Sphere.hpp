
#ifndef CS354_PROJECT4_SPHERE_HPP
#define CS354_PROJECT4_SPHERE_HPP

#include "Object.hpp"

namespace cs354 {
    class Sphere : public Object {
    public:
        Sphere(const Point3d &pos, double radius = 1.0,
               const Material &material = Material::Default);
        Sphere(const Sphere &sphere);
        virtual ~Sphere();
        
        virtual bool intersect(const Ray &ray, Ray &result) const;
        virtual bool bisect(const Ray &ray, Ray &result) const;
        
        void move(Vector3d direction);
        
        virtual Sphere * clone() const;
    protected:
        Point3d pos;
        double radius;
    };
}

#endif
