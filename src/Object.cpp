
#include "Object.hpp"

using namespace cs354;

Object::Object(const Material &mat) :
    mat(mat)
{ }
Object::~Object() { }

const Material & Object::material() const {
    return mat;
}

void Object::material(const Material &material) {
    mat = material;
}
