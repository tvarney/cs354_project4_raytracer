
#ifndef CS354_PROJECT4_TEXTURE_HPP
#define CS354_PROJECT4_TEXTURE_HPP

#include <stdint.h>

#include "Pixel.hpp"

namespace cs354 {
    enum Filter {
        FILTER_NEAREST,
        FILTER_LINEAR,
    };
    enum TextureType {
        TEXTURE_1D,
        TEXTURE_2D,
        TEXTURE_3D
    };
    
    class Texture {
    public:
        virtual ~Texture();
        
        virtual uint32_t get(double s);
        virtual uint32_t get(double s, double t);
        virtual uint32_t get(double s, double t, double r) = 0;
        
        uint8_t * data();
        const uint8_t * data() const;
        uint32_t size() const;
        PixelFormat format() const;
        Filter filter() const;
        TextureType type() const;
        
        void filter(Filter filter);
        
        static uint32_t GetPixelDepth(PixelFormat format);
    protected:
        Texture(TextureType type, PixelFormat format, uint32_t size);
        uint32_t getraw(uint32_t addr) const;
        
        PixelFormat _format;
        uint32_t _size;
        uint8_t *_data;
        Filter _filter;
        TextureType _type;
    };
    
    class Texture1D : public Texture {
    public:
        Texture1D(PixelFormat format, uint32_t width);
        virtual ~Texture1D();
        
        virtual uint32_t get(double s, double t, double r);
    protected:
        uint32_t width;
    };
    
    class Texture2D : public Texture {
    public:
        Texture2D(PixelFormat format, uint32_t width, uint32_t height);
        virtual ~Texture2D();
        
        virtual uint32_t get(double s, double t, double r);
    protected:
        uint32_t width, height;
    };
    
    class Texture3D : public Texture {
    public:
        Texture3D(PixelFormat format, uint32_t width, uint32_t height,
                  uint32_t depth);
        virtual ~Texture3D();
        
        virtual uint32_t get(double s, double t, double r);
    protected:
        uint32_t width, height, depth;
    };
}

#endif
