
#ifndef CS354_GENERIC_COLOR_HPP
#define CS354_GENERIC_COLOR_HPP

#include <stdint.h>
#include <iostream>

namespace cs354 {
    class Color {
    public:
        Color();
        Color(double r, double g, double b);
        Color(const Color &source);
        ~Color();
        
        Color & set(double r, double g, double b);
        
        double red() const;
        double green() const;
        double blue() const;
        
        Color & red(double newvalue);
        Color & green(double newvalue);
        Color & blue(double newvalue);
        
        void normalize();
        
        Color operator+(const Color rhs) const;
        Color operator+(double rhs) const;
        Color operator-(const Color rhs) const;
        Color operator-(double rhs) const;
        Color operator*(const Color rhs) const;
        Color operator*(double rhs) const;
        Color operator/(const Color rhs) const;
        Color operator/(double rhs) const;
        
        Color & operator=(const Color rhs);
        Color & operator+=(const Color rhs);
        Color & operator+=(double rhs);
        Color & operator-=(const Color rhs);
        Color & operator-=(double rhs);
        Color & operator*=(const Color rhs);
        Color & operator*=(double rhs);
        Color & operator/=(const Color rhs);
        Color & operator/=(double rhs);
        
        /* Standard Web Colors */
        static const Color White, Silver, Gray, Black, Red, Maroon, Yellow;
        static const Color Olive, Lime, Green, Aqua, Teal, Blue, Navy;
        static const Color Fuchsia, Purple;
    private:
        double _r, _g, _b;
    };
    
    std::ostream & operator<<(std::ostream &out, const Color &color);
}

#endif
