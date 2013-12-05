
#include "Color.hpp"
#include <cmath>

using namespace cs354;

#define CLAMP(v, min, max) ((v) < (min) ? (min) : ((v) > (max) ? (max) : (v)))

Color::Color() :
    _r(0.0), _g(0.0), _b(0.0)
{ }
Color::Color(double r, double g, double b) :
    _r(r < 0.0 ? 0.0 : r), _g(g < 0.0 ? 0.0 : g), _b(b < 0.0 ? 0.0 : b)
{
    normalize();
}
Color::Color(const Color &source) :
    _r(source._r), _g(source._g), _b(source._b)
{ }
Color::~Color() { }

Color & Color::set(double r, double g, double b) {
    _r = r;
    _g = g;
    _b = b;
    normalize();
    return *this;
}

double Color::red() const {
    return _r;
}
double Color::green() const {
    return _g;
}
double Color::blue() const {
    return _b;
}

Color & Color::red(double newvalue) {
    _r = newvalue;
    if(newvalue > 1.0) {
        double factor = 1.0 / newvalue;
        _r = 1.0;
        _g *= factor;
        _b *= factor;
    }
    return *this;
}
Color & Color::green(double newvalue) {
    _g = newvalue;
    if(newvalue > 1.0) {
        double factor = 1.0 / newvalue;
        _r *= factor;
        _g *= 1.0;
        _b *= factor;
    }
    return *this;
}
Color & Color::blue(double newvalue) {
    _b = newvalue;
    if(newvalue > 1.0) {
        double factor = 1.0 / newvalue;
        _r *= factor;
        _g *= factor;
        _b *= 1.0;
    }
    return *this;
}

void Color::normalize() {
    double max = (_r > _g ? (_r > _b ? _r : _b) : (_g > _b ? _g : _b));
    if(max > 1.0) {
        double factor = 1.0 / max;
        _r *= factor;
        _g *= factor;
        _b *= factor;
    }
}

Color & Color::operator=(const Color source) {
    _r = source._r;
    _g = source._g;
    _b = source._b;
    return *this;
}

Color Color::operator+(const Color rhs) const {
    return Color(_r + rhs._r, _g + rhs._g, _b + rhs._b);
}
Color Color::operator+(double rhs) const {
    return Color(_r + rhs, _g + rhs, _b + rhs);
}
Color Color::operator-(const Color rhs) const {
    return Color(_r - rhs._r, _g - rhs._g, _b - rhs._b);
}
Color Color::operator-(double rhs) const {
    return Color(_r - rhs, _g - rhs, _b - rhs);
}
Color Color::operator*(const Color rhs) const {
    return Color(_r * rhs._r, _g * rhs._g, _b * rhs._b);
}
Color Color::operator*(double rhs) const {
    return Color(_r * rhs, _g * rhs, _b * rhs);
}
Color Color::operator/(const Color rhs) const {
    return Color(_r / rhs._r, _g / rhs._g, _b / rhs._b);
}
Color Color::operator/(double rhs) const {
    double inv = 1.0 / rhs;
    return Color(_r * inv, _g * inv, _b * inv);
}

Color & Color::operator+=(const Color rhs) {
    return (*this = *this + rhs);
}
Color & Color::operator+=(double rhs) {
    return (*this = *this + rhs);
}
Color & Color::operator-=(const Color rhs) {
    return (*this = *this - rhs);
}
Color & Color::operator-=(double rhs) {
    return (*this = *this - rhs);
}
Color & Color::operator*=(const Color rhs) {
    return (*this = *this * rhs);
}
Color & Color::operator*=(double rhs) {
    return (*this = *this * rhs);
}
Color & Color::operator/=(const Color rhs) {
    return (*this = *this / rhs);
}
Color & Color::operator/=(double rhs) {
    return (*this = *this / rhs);
}

std::ostream & cs354::operator<<(std::ostream &out, const Color &color) {
    return (out << "color(" << color.red() << ", " << color.green() << ", " <<
            color.blue() << ")");
}

const Color Color::White(1.0, 1.0, 1.0);
const Color Color::Silver(0.75, 0.75, 0.75);
const Color Color::Gray(0.5, 0.5, 0.5);
const Color Color::Black(0.0, 0.0, 0.0);
const Color Color::Red(1.0, 0.0, 0.0);
const Color Color::Maroon(0.5, 0.0, 0.0);
const Color Color::Yellow(1.0, 1.0, 0.0);
const Color Color::Olive(0.5, 0.5, 0.0);
const Color Color::Lime(0.0, 1.0, 0.0);
const Color Color::Green(0.0, 0.5, 0.0);
const Color Color::Aqua(0.0, 1.0, 1.0);
const Color Color::Teal(0.0, 0.5, 0.5);
const Color Color::Blue(0.0, 0.0, 1.0);
const Color Color::Navy(0.0, 0.0, 0.5);
const Color Color::Fuchsia(1.0, 0.0, 1.0);
const Color Color::Purple(0.5, 0.0, 0.5);
