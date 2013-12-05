
#include "InfinitePlane.hpp"

#include "Geometry.hpp"

using namespace cs354;

InfinitePlane::InfinitePlane(const Vector3d &normal, double distance,
                             const Material &material) :
    Object(material), normal(normal), distance(distance)
{
    
}
InfinitePlane::InfinitePlane(const InfinitePlane &source) :
    Object(source.material()), normal(source.normal), distance(source.distance)
{ }
InfinitePlane::~InfinitePlane() { }

bool InfinitePlane::intersect(const Ray &source, Ray &result) const {
    double denom = dot(source.direction, normal);
    if(denom == 0.0) {
        return false; /*< Parallel */
    }
    
    double t = (distance - dot(source.origin, normal)) / denom;
    if(t < 0.0) {
        return false; /* Plane is behind the origin */
    }
    
    result = source.project(t, (denom < 0.0 ? normal : -normal));
    return true;
}

/* A plane is infinitely thin, bisection returns the source ray */
bool InfinitePlane::bisect(const Ray &source, Ray &result) const {
    result.origin = source.origin;
    result.direction = source.direction;
    return true;
}

InfinitePlane * InfinitePlane::clone() const {
    return new InfinitePlane(normal, distance, material());
}
