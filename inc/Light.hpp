
#ifndef CS354_PROJECT4_LIGHT_HPP
#define CS354_PROJECT4_LIGHT_HPP

#include "Color.hpp"
#include "Material.hpp"
#include "Point.hpp"
#include "Ray.hpp"

namespace cs354 {
    struct Light {
        Light();
        Light(const Point3d location, const Color color = Color::White);
        Light(const Vector3d direction, const Color color = Color::White);
        Light(const Light &source);
        ~Light();
        
        Color get(const Ray &ray, const Ray &normal,
                  const Material &material, bool diffuse = true,
                  bool specular = true) const;
        
        Light & operator=(const Light &light);
        
        Vector3d direction(const Point3d &at) const;
        
        static double Attenuation;
        static bool Ambient, Diffuse, Specular, Half, Attenuate;
        
        bool point;
        double x, y, z;
        Color color;
    };
}

#endif
