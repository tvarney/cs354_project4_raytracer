
#ifndef CS354_GENERIC_GEOMETRY_HPP
#define CS354_GENERIC_GEOMETRY_HPP

#include "Point.hpp"
#include "Vector.hpp"

namespace cs354 {
    template <typename T>
    Vector<T> operator-(const Point<T> lhs, const Point<T> rhs) {
        return Vector<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    }
    template <typename T>
    Point<T> operator+(const Point<T> rhs, const Vector<T> lhs) {
        return Point<T>(rhs.x + lhs.x, rhs.y + lhs.y, rhs.z + lhs.z);
    }
    template <typename T>
    Point<T> operator+(const Vector<T> rhs, const Point<T> lhs) {
        return Point<T>(rhs.x + lhs.x, rhs.y + lhs.y, rhs.z + lhs.z);
    }
    
    /* Hopefully the compiler recognizes the floating point versions can be
     * optimized to a multiply instead of a div.
     */
    template <typename T>
    Point<T> lerp(const Point<T> p1, const Point<T> p2) {
        return Point<T>(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z) / ((T)2);
    }
    template <typename T>
    Vector<T> lerp(const Vector<T> v1, const Vector<T> v2) {
        return (v1 + v2) / ((T)2);
    }
    
    template <typename T>
    T dot(const Vector<T> v1, const Vector<T> v2) {
        return v1.dot(v2);
    }
    template <typename T>
    Vector<T> normalize(const Vector<T> v1) {
        return v1.normalize();
    }
    template <typename T>
    Vector<T> reflect(const Vector<T> v1, const Vector<T> v2) {
        return v1.reflect(v2);
    }
    
    template <typename T>
    Vector<T> refract(const Vector<T> v, const Vector<T> normal, T n1, T n2) {
        return v.refract(normal, n1, n2);
    }
    
    template <typename T, typename value>
    Vector<T> operator*(value val, const Vector<T> v) {
        return Vector<T>(v.x * ((T)val), v.y * ((T)val), v.z * ((T)val));
    }
    
    /* So many things want to do a dot product with a point, that I'm adding
     * these
     */
    template <typename T>
    T dot(const Vector<T> &lhs, const Point<T> &rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }
    template <typename T>
    T dot(const Point<T> &lhs, const Vector<T> &rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }
    template <typename T>
    T dot(const Point<T> &lhs, const Point<T> &rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }
}

#endif
