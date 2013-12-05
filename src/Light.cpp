
#include "Light.hpp"

#include <cmath>
#include <cstdio>
#include <iostream>
#include "Geometry.hpp"
#include "Util.hpp"

using namespace cs354;

double Light::Attenuation = 0.02;
bool Light::Ambient = true;
bool Light::Diffuse = true;
bool Light::Specular = true;
bool Light::Half = true;
bool Light::Attenuate = true;

Light::Light() :
    point(true), x(0.0), y(0.0), z(0.0), color(Color::White)
{ }
Light::Light(const Point3d location, const Color color) :
    point(true), x(location.x), y(location.y), z(location.z), color(color)
{ }
Light::Light(const Vector3d direction, const Color color) :
    point(false), x(direction.x), y(direction.x), z(direction.z), color(color)
{ }
Light::Light(const Light &source) :
    point(source.point), x(source.x), y(source.y), z(source.z),
    color(source.color)
{ }
Light::~Light() { }

static inline double saturate(double val) {
    return (val > 1.0 ? 1.0 : (val < 0.0 ? 0.0 : val));
}
Color Light::get(const Ray &ray, const Ray &normal, const Material &mat,
                 Color *diffuse, Color *specular) const
{
    if(!Light::Diffuse && !Light::Specular) {
        if(!Light::Ambient) {
            Vector3d ld = direction(normal.origin);
            double ndotl = saturate(dot(normal.direction, ld));
            Color diff(ndotl, ndotl, ndotl);
            *diffuse = diff;
            //return NormalToColor(normal.direction);
        }
        return Color::Black;
    }
    
    Vector3d light_dir;
    double attenuation;
    if(point) {
        light_dir = Point3d(x, y, z) - normal.origin;
        //light_dir = normal.origin - Point3d(x, y, z);
        double distance = light_dir.magnitude();
        light_dir /= distance;
        if(Light::Attenuate) {
            attenuation = 1.0 / (Light::Attenuation * distance);
        }else {
            attenuation = 1.0;
        }
    }else {
        light_dir = Vector3d(-x, -y, -z);
        attenuation = 1.0;
    }
    Color cdiff;
    if(Light::Diffuse) {
        double ndotl = saturate(dot(normal.direction, light_dir));
        cdiff = mat.base * (color * (mat.kd * ndotl * attenuation));
    }
    
    Color cspec;
    if(Light::Specular && specular) {
        Vector3d eye_dir = -(ray.direction);
        /* Reflect L about normal.direction  */
        double base;
        if(Light::Half) {
            Vector3d half = normalize(light_dir + eye_dir);
            base = saturate(dot(half, normal.direction));
        }else {
            Vector3d reflected = reflect(light_dir,normal.direction);
            base = saturate(dot(normalize(reflected), eye_dir));
        }
        cspec = mat.highlight * (color * std::pow(base, mat.ks) * attenuation);
    }
    if(diffuse != NULL) {
        *diffuse = cdiff;
    }
    if(specular != NULL) {
        *specular = cspec;
    }
    return cdiff + cspec;
}

Light & Light::operator=(const Light &light) {
    point = light.point;
    x = light.x;
    y = light.y;
    z = light.z;
    color = light.color;
    return *this;
}

Vector3d Light::direction(const Point3d &at) const {
    if(!point) {
        return Vector3d(-x, -y, -z);
    }
    
    return (Point3d(x, y, z) - at).normalize();
}
