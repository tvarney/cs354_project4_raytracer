
#ifndef CS354_GENERIC_WINDOW_INFO_HPP
#define CS354_GENERIC_WINDOW_INFO_HPP

#include <string>

namespace cs354 {
    struct Window {
        /* Mode values */
        static const int RGBA, RGB, INDEX;
        static const int SINGLE, DOUBLE;
        static const int ACCUM, ALPHA, DEPTH, STENCIL, MULTISAMPLE;
        static const int STEREO, LUMINANCE;
        
        /* Window information */
        std::string title;
        int width, height;
        int x, y;
        int mode;
        
        /* Constructors */
        Window(const char *title, int width, int height);
        Window(const char *title, int width, int height, int mode);
        Window(const char *title, int width, int height, int x, int y);
        Window(const char *title, int width, int height, int x, int y,
               int mode);
        ~Window();
    };
}

#endif
