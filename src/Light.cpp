
#include "Light.hpp"

#include <cmath>
#include <cstdio>
#include "Geometry.hpp"
#include "Util.hpp"

using namespace cs354;

double Light::Attenuation = 0.05;
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
Color Light::get(const Ray &ray, const Ray &normal, const Material &mat)
    const
{
    if(!Light::Diffuse && !Light::Specular) {
        if(!Light::Ambient) {
            return NormalToColor(normal.direction);
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
        light_dir = Vector3d(x, y, z);
        attenuation = 1.0;
    }
    Color result;
    if(Light::Diffuse) {
        double ndotl = saturate(dot(normal.direction, light_dir));
        result += mat.base * (color * (mat.kd * ndotl * attenuation));
    }
    
    if(Light::Specular) {
        Vector3d eye_dir = -(ray.direction);
        /* Reflect L about normal.direction  */
        double base;
        if(Light::Half) {
            Vector3d half = normalize(light_dir + eye_dir);
            //Vector3d half = normalize(reflected + normal.direction);
            base = saturate(dot(half, normal.direction));
        }else {
            Vector3d reflected = reflect(light_dir,normal.direction);
            base = saturate(dot(normalize(reflected), eye_dir));
        }
        result += mat.highlight * (color * std::pow(base, mat.ks) *
                                   attenuation);
    }
    return result;
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
