
#ifndef CS354_PROJECT4_RAY_HPP
#define CS354_PROJECT4_RAY_HPP

#include "Point.hpp"
#include "Vector.hpp"

namespace cs354 {
    struct Ray {
        Ray();
        Ray(const Point3d origin, const Vector3d direction);
        Ray(const Ray &source);
        ~Ray();
        
        Ray project(double distance) const;
        Ray project(double distance, const Vector3d newdir) const;
        Ray transform(const Point3d object_origin) const;
        
        Ray & operator=(const Ray rhs);
        
        Point3d origin;
        Vector3d direction;
    };
}

#endif
