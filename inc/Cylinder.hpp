
#ifndef CS354_PROJECT4_CYLINDER_HPP
#define CS354_PROJECT4_CYLINDER_HPP

#include "Object.hpp"
#include "Point.hpp"
#include "Vector.hpp"

namespace cs354 {
    class Cylinder : public Object {
    public:
        Cylinder(const Point3d center, double radius, double half_len,
                 const Material &material = Material::Default);
        virtual ~Cylinder();
        
        virtual bool intersect(const Ray &source, Ray &result) const;
        virtual bool bisect(const Ray &source, Ray &result) const;
        
        Cylinder * clone() const;
    private:
        bool get_dist(const Ray &source, double *t0, double *t1) const;
        
        Point3d center;
        double radius, half_len;
    };
}

#endif
