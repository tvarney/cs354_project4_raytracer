
#ifndef CS354_PROJECT4_CANVAS_HPP
#define CS354_PROJECT4_CANVAS_HPP

#include <stddef.h>
#include <stdint.h>

#include "Color.hpp"
#include "Pixel.hpp"

namespace cs354 {
    /**
     * Raster Image
     */
    class Canvas {
    public:
        Canvas();
        Canvas(size_t width, size_t height);
        ~Canvas();
        
        Color get(size_t x, size_t y) const;
        uint8_t get(size_t x, size_t y, PixelMask mask) const;
        void set(size_t x, size_t y, const Color value);
        void set(size_t x, size_t y, uint8_t pixel, PixelMask mask);
        
        void resize(size_t width, size_t height);
        void clear(const Color &color = Color::Black);
        
        const uint8_t * data() const;
        size_t width() const;
        size_t height() const;
        size_t pixels() const;
        size_t memsize() const;
    protected:
        size_t _width, _height, _pixels, _memsize;
        uint8_t *_data;
    };
}

#endif
