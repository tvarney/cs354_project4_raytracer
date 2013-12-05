
#ifndef CS354_PROJECT4_OBJECT_HPP
#define CS354_PROJECT4_OBJECT_HPP

#include "Material.hpp"
#include "Ray.hpp"

namespace cs354 {
    class Object {
    public:
        virtual ~Object();
        
        /* Check for intersection; if the method returns true, intersect is
         * set to the point at which the ray intersected the object and
         * normal is set to the normal vector of the surface. */
        virtual bool intersect(const Ray &source, Ray &result) const = 0;
        /* Find exit point of transparent object. */
        virtual bool bisect(const Ray &source, Ray &result) const = 0;
        
        virtual const Material & material() const;
        virtual void material(const Material &material);
        
        virtual Object* clone() const = 0;
    protected:
        Object(const Material &mat = Material::Default);
        
        Material mat;
    };
}

#endif
