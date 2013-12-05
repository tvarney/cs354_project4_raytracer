
#include "InfinitePlane.hpp"

#include "Geometry.hpp"

using namespace cs354;

InfinitePlane::InfinitePlane(const Vector3d &normal, const Point3d &point,
                             const Material &material) :
    Object(material), normal(normal), point(point)
{
    
}
InfinitePlane::InfinitePlane(const InfinitePlane &source) :
    Object(source.material()), normal(source.normal), point(source.point)
{ }
InfinitePlane::~InfinitePlane() { }

bool InfinitePlane::intersect(const Ray &source, Ray &result) const {
    double denom = source.origin.x * source.direction.x +
        source.origin.y * source.direction.y +
        source.origin.z * source.direction.z;
    if(denom == 0.0) {
        /* Ray is parallel to plane */
        return false;
    }
    
    double t = dot(normal, point - source.origin) / denom;
    if(t < 0.0) {
        /* Plane is behind the origin of the eye */
        return false;
    }
    
    result.origin = source.origin + source.direction * t;
    result.direction = normal;
    return true;
}

bool InfinitePlane::bisect(const Ray &source, Ray &result) const {
    result.origin = source.origin;
    result.direction = source.direction;
    return true;
}

InfinitePlane * InfinitePlane::clone() const {
    return new InfinitePlane(normal, point, material());
}
