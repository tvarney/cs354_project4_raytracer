
#include "Material.hpp"

using namespace cs354;

Material::Material() :
    kd(1.0), ks(40), kt(0.0), kr(0.0), ior(0.0), base(Color::Silver),
    highlight(Color::White)
{ }
Material::Material(double kd, double ks, double kt, double kr, double ior,
                   Color basecolor, Color highlightcolor) :
    kd(kd), ks(ks), kt(kt), kr(kr), ior(ior), base(basecolor),
    highlight(highlightcolor)
{ }
Material::Material(const Material &source) :
    kd(source.kd), ks(source.ks), kt(source.kt), kr(source.kr),
    ior(source.ior), base(source.base), highlight(source.highlight)
{ }

Material::~Material() { }

Material & Material::operator=(const Material &rhs) {
    kd = rhs.kd;
    ks = rhs.ks;
    kt = rhs.kt;
    kr = rhs.kr;
    ior = rhs.ior;
    base = rhs.base;
    highlight = rhs.highlight;
    return *this;
}

const Material Material::Default = Material();
const Material Material::Glass(1.0, 100, 0.75, 0.0, 1.4919,
                               Color(0.1, 0.1, 0.1),
                               Color(0.5, 0.5, 0.5));
const Material Material::Mirror(1.0, 100.0, 0.0, 0.95, 1.4919,
                                Color(0.9, 0.9, 0.9),
                                Color::White);
const Material Material::RedGlass(1.0, 128, 0.95, 0.0, 1.4919,
                                  Color(1.0, 0.5, 0.5),
                                  Color(1.0, 0.75, 0.75));
