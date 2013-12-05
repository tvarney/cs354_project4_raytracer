
#include "Canvas.hpp"
#include "Pixel.hpp"

using namespace cs354;

Canvas::Canvas() :
    _width(0), _height(0), _pixels(0), _memsize(0),
    _data(NULL)
{ }
Canvas::Canvas(size_t width, size_t height) :
    _width(width), _height(height), _pixels(width*height), _memsize(_pixels*3),
    _data(_memsize > 0 ? new uint8_t[_memsize] : NULL)
{ }
Canvas::~Canvas() {
    if(_data != NULL) {
        delete [] _data;
        _data = NULL;
    }
}

Color Canvas::get(size_t x, size_t y) const {
    size_t i = x + y * _width;
    return Color(float(_data[i])/255.0f, float(_data[i+1])/255.0f,
                 float(_data[i+2])/255.0f);
}
uint8_t Canvas::get(size_t x, size_t y, PixelMask mask) const {
    size_t i = x + y * _width;
    switch(mask) {
    case MASK_RED:
        return _data[i];
    case MASK_GREEN:
        return _data[i+1];
    case MASK_BLUE:
        return _data[i+2];
    case MASK_ALPHA:
    default:
        return 0;
    }
}
void Canvas::set(size_t x, size_t y, const Color value) {
    size_t i = 3 * x + 3 * y * _width;
    _data[i] = (uint8_t)(value.red() * 255.0f);
    _data[i+1] = (uint8_t)(value.green() * 255.0f);
    _data[i+2] = (uint8_t)(value.blue() * 255.0f);
}
void Canvas::set(size_t x, size_t y, uint8_t pixel, PixelMask mask) {
    size_t i = x + y * _width;
    switch(mask) {
    case MASK_RED:
        _data[i] = pixel;
        break;
    case MASK_GREEN:
        _data[i+1] = pixel;
        break;
    case MASK_BLUE:
        _data[i+2] = pixel;
        break;
    case MASK_ALPHA:
    default:
        break;
    }
}

void Canvas::resize(size_t nwidth, size_t nheight) {
    if(nwidth == 0 || nheight == 0) {
        if(_data != NULL) {
            delete _data;
        }
        _data = NULL;
        _width = 0;
        _height = 0;
        _pixels = 0;
        _memsize = 0;
    }else {
        _width = nwidth;
        _height = nheight;
        _pixels = nwidth * nheight;
        _memsize = _pixels * 3;
        if(_data != NULL) {
            delete _data;
        }
        _data = new uint8_t[_memsize];
        clear();
    }
}

void Canvas::clear(const Color &color) {
    uint8_t r = (uint8_t)(color.red() * 255);
    uint8_t g = (uint8_t)(color.green() * 255);
    uint8_t b = (uint8_t)(color.blue() * 255);
    
    for(size_t i = 0; i < _pixels; ++i) {
        _data[i * 3 + 0] = r;
        _data[i * 3 + 1] = g;
        _data[i * 3 + 2] = b;
    }
}

const uint8_t * Canvas::data() const {
    return _data;
}
size_t Canvas::width() const {
    return _width;
}
size_t Canvas::height() const {
    return _height;
}
size_t Canvas::pixels() const {
    return _pixels;
}
size_t Canvas::memsize() const {
    return _memsize;
}
