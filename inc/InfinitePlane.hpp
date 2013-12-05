
#ifndef CS354_PROJECT4_INFINITE_PLANE_HPP
#define CS354_PROJECT4_INFINITE_PLANE_HPP

#include "Object.hpp"
#include "Point.hpp"
#include "Vector.hpp"

namespace cs354 {
    class InfinitePlane : public Object {
    public:
        InfinitePlane(const Vector3d &normal, double distance,
                      const Material &material = Material::Default);
        InfinitePlane(const InfinitePlane &source);
        virtual ~InfinitePlane();
        
        virtual bool intersect(const Ray &source, Ray &result) const;
        virtual bool bisect(const Ray &source, Ray &result) const;
        
        virtual InfinitePlane * clone() const;
    protected:
        Vector3d normal;
        double distance;
    };
}

#endif
