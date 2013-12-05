
#ifndef CS354_PROJECT4_MATERIAL_HPP
#define CS354_PROJECT4_MATERIAL_HPP

#include "Color.hpp"
#include "Texture.hpp"

namespace cs354 {
    /**
     * kd:
     *   How much light is scattered by the material.
     * ks:
     *   The 'shininess' of the material.
     * kt:
     *   The transparancy of the material.
     * kr:
     *   The reflectivity of the material.
     * ior:
     *   The index of refraction for this material.
     * base:
     *   The color of the scattered light off the material
     * highlight:
     *   The color of any specular highlights in the material.
     */
    struct Material {
        Material();
        Material(double kd, double ks, double kt, double kr, double ior,
                 Color basecolor, Color highlightcolor);
        Material(const Material &source);
        ~Material();
        
        Material & operator=(const Material &rhs);
        
        double kd, ks, kt, kr, ior;
        Color base, highlight;
        
        static const Material Default;
        static const Material Glass, Mirror;
        static const Material RedGlass;
    };
}

#endif
