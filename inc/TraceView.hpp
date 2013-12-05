
#ifndef CS354_PROJECT4_TRACE_VIEW_HPP
#define CS354_PROJECT4_TRACE_VIEW_HPP

#include <stdint.h>

#include "Canvas.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "View.hpp"

namespace cs354 {
    class TraceView : public BasicView {
    public:
        TraceView();
        virtual ~TraceView();
        
        virtual void init();
        virtual void end();
        virtual void display();
        
        virtual void reshape(int width, int height);
        virtual void keyPressed(int ch);
        virtual void mousePressed(MouseButton button, ButtonState state);
        
        void load(const char *fname);
    protected:
        Scene scene;
        Canvas canvas;
        
        Sphere s1, s2;
        Light light1, light2;
        bool do_light1, do_light2;
        bool make_glass;
        
        double fov;
        double z_camera;
        bool render, trace_done, resize;
        uint64_t last_update;
    };
}

#endif
