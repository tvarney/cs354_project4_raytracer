
#include "Texture.hpp"
#include <cmath>
#include <stddef.h>

using namespace cs354;

Texture::Texture(TextureType type, PixelFormat format, uint32_t size) :
    _format(format), _size(size),
    _data((size != 0) ? new uint8_t[GetPixelDepth(format) * size] : NULL),
    _filter(FILTER_LINEAR),
    _type(type)
{ }
Texture::~Texture() {
    if(_data != NULL) {
        delete [] _data;
        _data = NULL;
    }
}

uint32_t Texture::get(double s) {
    return get(s, 0.0, 0.0);
}
uint32_t Texture::get(double s, double t) {
    return get(s, t, 0.0);
}

uint8_t * Texture::data() {
    return _data;
}
const uint8_t * Texture::data() const {
    return _data;
}
uint32_t Texture::size() const {
    return _size;
}
PixelFormat Texture::format() const {
    return _format;
}
Filter Texture::filter() const {
    return _filter;
}
TextureType Texture::type() const {
    return _type;
}

void Texture::filter(Filter newfilter) {
    _filter = newfilter;
}

uint32_t Texture::getraw(uint32_t addr) const {
    uint32_t x = GetPixelDepth(_format) * addr;
    switch(_format) {
    case PF_GRAY:
        return _data[x];
    case PF_RGB:
        return (_data[x] << SHIFT_RED) | (_data[x + 1] << SHIFT_GREEN) |
            (_data[x + 2] << SHIFT_BLUE);
    case PF_RGBA:
        return (_data[x] << SHIFT_RED) | (_data[x + 1] << SHIFT_GREEN) |
            (_data[x + 2] << SHIFT_BLUE) | (_data[x + 3] << SHIFT_ALPHA);
    }
    return 0;
}

static uint32_t _pixeldepth[] = {
    1, 3, 4
};
uint32_t Texture::GetPixelDepth(PixelFormat format) {
    return _pixeldepth[format];
}

Texture1D::Texture1D(PixelFormat format, uint32_t width) :
    Texture(TEXTURE_1D, format, width),
    width(width)
{ }
Texture1D::~Texture1D() { }

/* Sampling textures is going to be SLOW */
uint32_t Texture1D::get(double s, double t, double r) {
    double x = s * double(width);
    double w1 = std::fmod(x, 1.0);
    double w2 = 1.0 - w1;
    uint32_t x1 = ((uint32_t)x) % width;
    uint32_t x2 = (x1 + 1) % width;
    
    uint32_t v1 = getraw(x1);
    uint32_t v2 = getraw(x2);
    switch(_filter) {
    case FILTER_NEAREST:
        return (w1 <= 0.5 ? v1 : v2);
    case FILTER_LINEAR:
    default:
        return ((uint32_t)(v1 * w2)) + ((uint32_t)(v2 * w1));
    }
}

Texture2D::Texture2D(PixelFormat format, uint32_t width, uint32_t height) :
    Texture(TEXTURE_2D, format, width * height),
    width(width), height(height)
{ }
Texture2D::~Texture2D() { }

uint32_t Texture2D::get(double s, double t, double r) {
    /* Expand coordinates to texture size */
    double x = s * double(width);
    double y = t * double(height);
    /* Calculate weights */
    double wx1 = std::fmod(x, 1.0);
    double wx2 = 1.0 - wx1;
    double wy1 = std::fmod(y, 1.0);
    double wy2 = 1.0 - wy1;
    /* Wrap coordinates to texture size */
    uint32_t x1 = ((uint32_t)x) % width;
    uint32_t x2 = (x1 + 1) % width;
    uint32_t y1 = ((uint32_t)y) % height;
    uint32_t y2 = (y1 + 1) % width;
    /* Grab the values of nearest 4 pixels*/
    uint32_t v11 = getraw(x1 + y1 * width);
    uint32_t v21 = getraw(x2 + y1 * width);
    uint32_t v12 = getraw(x1 + y2 * width);
    uint32_t v22 = getraw(x2 + y2 * width);
    switch(_filter) {
    case FILTER_NEAREST:
        /* Select nearest */
        if(wx1 <= 0.5 ? (wy1 <= 0.5 ? v12 : v11) : (wy1 <= 0.5 ? v22 : v21));
    case FILTER_LINEAR:
        /* Interpolate between the 4 points */
        return ((uint32_t)(v11 * wx2 * wy2)) + ((uint32_t)(v12 * wx2 * wy1)) +
            ((uint32_t)(v21 * wx1 * wy2)) + ((uint32_t)(v22 * wx1 * wy1));
    }
    return 0.0;
}

Texture3D::Texture3D(PixelFormat format, uint32_t width, uint32_t height,
                     uint32_t depth) :
    Texture(TEXTURE_3D, format, width * height * depth),
    width(width), height(height), depth(depth)
{ }
Texture3D::~Texture3D() { }

uint32_t Texture3D::get(double s, double t, double r) {
    //double x = s * double(width);
    //double y = t * double(height);
    //double z = r * double(depth);
    return 0;
}
