
#include "Ray.hpp"

using namespace cs354;

Ray::Ray() { }
Ray::Ray(const Point3d origin, const Vector3d direction) :
    origin(origin), direction(direction)
{ }
Ray::Ray(const Ray &source) :
    origin(source.origin), direction(source.direction)
{ }
Ray::~Ray() { }

Ray Ray::transform(const Point3d obj) const {
    return Ray(Point3d(origin.x - obj.x, origin.y - obj.y, origin.z - obj.z),
               direction);
}

Ray & Ray::operator=(const Ray rhs) {
    origin = rhs.origin;
    direction = rhs.direction;
    return *this;
}
