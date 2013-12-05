
#ifndef CS354_GENERIC_VECTOR_HPP
#define CS354_GENERIC_VECTOR_HPP

#include <cmath>
#include <ostream>

namespace cs354 {
    template <typename T>
    struct Vector {
        T x, y, z;
        
        Vector() : x((T)0), y((T)0), z((T)0) { }
        Vector(T x, T y, T z) : x(x), y(y), z(z) { }
        Vector(const T data[3]) :
            x((T)data[0]), y((T)data[1]), z((T)data[2])
        { }
        Vector(const Vector<T> &source) :
            x(source.x), y(source.y), z(source.z)
        { }
        ~Vector() { }
        
        T & operator[](unsigned int i) {
            switch(i) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            }
        }
        const T & operator[](unsigned int i) const {
            switch(i) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            }
        }
        Vector<T> operator+() const {
            return Vector<T>(*this);
        }
        Vector<T> operator-() const {
            return Vector<T>(-x, -y, -z);
        }
        Vector<T> operator+(const Vector &rhs) const {
            return Vector<T>(x + rhs.x, y + rhs.y, z + rhs.z);
        }
        Vector<T> operator-(const Vector &rhs) const {
            return Vector<T>(x - rhs.x, y - rhs.y, z + rhs.z);
        }
        Vector<T> operator*(const Vector &rhs) const {
            return Vector<T>(y * rhs.z - z * rhs.y, x * rhs.z - z * rhs.x,
                             x * rhs.y - y * rhs.x);
        }
        Vector<T> operator/(const Vector &rhs) const {
            return Vector<T>(y / rhs.z - z / rhs.y, x / rhs.z - z / rhs.x,
                             x / rhs.y - y / rhs.x);
        }
        Vector<T> operator*(T scalar) const {
            return Vector<T>(x*scalar, y*scalar, z*scalar);
        }
        Vector<T> operator/(T scalar) const {
            return Vector<T>(x/scalar, y/scalar, z/scalar);
        }
        
        Vector<T> reflect(Vector<T> normal) const {
            return (normal * (this->dot(normal) * ((T)2.0))) - *this;
        }
        Vector<T> refract(Vector<T> normal, T n1, T n2) {
            /* This should give us snells law */
            double factor = double(n1) / double(n2);
            double cos1 = this->dot(-normal);
            double cos2 = std::sqrt(1 - factor * factor * (1 - cos1 * cos1));
            return *this * factor + normal * (factor * cos1 - cos2);
        }
        Vector<T> inverse() const {
            return Vector<T>(((T)1.0)/x, ((T)1.0)/y, ((T)1.0)/z);
        }
        Vector<T> normalize() const {
            T mag = magnitude();
            return (mag != ((T)0) ? (*this / mag) : Vector<T>());
        }
        Vector<T> shuffle(int xs, int ys, int zs) const {
            return Vector<T>((*this)[xs], (*this)[ys], (*this)[zs]);
        }
        
        T dot(const Vector &rhs) const {
            return x*rhs.x + y*rhs.y + z*rhs.z;
        }
        T magsquared() const {
            return x*x + y*y + z*z;
        }
        T magnitude() const {
            return std::sqrt(magsquared());
        }
        
        Vector<T> & operator=(const Vector<T> &rhs) {
            x = rhs.x;
            y = rhs.y;
            z = rhs.z;
            return *this;
        }
        Vector<T> & operator+=(const Vector<T> &rhs) {
            return *this = *this + rhs;
        }
        Vector<T> & operator-=(const Vector<T> &rhs) {
            return *this = *this - rhs;
        }
        Vector<T> & operator*=(const Vector<T> &rhs) {
            return *this = *this * rhs;
        }
        Vector<T> & operator/=(const Vector<T> &rhs) {
            return *this = *this / rhs;
        }
        Vector<T> & operator*=(T scalar) {
            return *this = *this * scalar;
        }
        Vector<T> & operator/=(T scalar) {
            return *this = *this / scalar;
        }

        T & getX() {
            return x;
        }
        T & getY() {
            return y;
        }
        T & getZ() {
            return z;
        }
    };
    
    typedef Vector<double> Vector3d;
    typedef Vector<float> Vector3f;
    
    template <typename T>
    std::ostream & operator<<(std::ostream &out, const Vector<T> &vec) {
        out << "<" << vec.x << ", " << vec.y << ", " <<
            vec.z << ">";
        return out;
    }
}

#endif
