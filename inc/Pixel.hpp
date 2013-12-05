
#ifndef CS354_PROJECT4_PIXEL_HPP
#define CS354_PROJECT4_PIXEL_HPP

namespace cs354 {
    enum PixelMask {
        MASK_RED = 0xFF000000,
        MASK_GREEN = 0x00FF0000,
        MASK_BLUE = 0x0000FF00,
        MASK_ALPHA = 0x000000FF
    };
    enum PixelShift {
        SHIFT_RED = 24,
        SHIFT_GREEN = 16,
        SHIFT_BLUE = 8,
        SHIFT_ALPHA = 0
    };
    enum PixelFormat {
        PF_GRAY = 0,
        PF_RGB = 1,
        PF_RGBA = 2,
    };
}

#endif
