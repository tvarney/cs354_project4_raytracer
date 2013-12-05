#ifndef CS354_GENERIC_VIEW_HPP
#define CS354_GENERIC_VIEW_HPP

#define CS354_GENERIC_IMPL
#include "common.hpp"

#include <stdint.h>

namespace cs354 {
    struct Window;
    
    typedef void (*TimerFn_t)(int);
    
    enum MouseButton {
        MOUSE_BUTTON_LEFT = 1,
        MOUSE_BUTTON_RIGHT = 1 << 1,
        MOUSE_BUTTON_MIDDLE = 1 << 2
    };
    enum ButtonState {
        BUTTON_UP = 0,
        BUTTON_DOWN = 1
    };
    
    enum Key {
        KEY_F1        = 0x0100,
        KEY_F2        = 0x0200,
        KEY_F3        = 0x0300,
        KEY_F4        = 0x0400,
        KEY_F5        = 0x0500,
        KEY_F6        = 0x0600,
        KEY_F7        = 0x0700,
        KEY_F8        = 0x0800,
        KEY_F9        = 0x0900,
        KEY_F10       = 0x0A00,
        KEY_F11       = 0x0B00,
        KEY_F12       = 0x0C00,
        KEY_LEFT      = 0x6400,
        KEY_UP        = 0x6500,
        KEY_RIGHT     = 0x6600,
        KEY_DOWN      = 0x6700,
        KEY_PAGE_UP   = 0x6800,
        KEY_PAGE_DOWN = 0x6900,
        KEY_HOME      = 0x6A00,
        KEY_END       = 0x6B00,
        KEY_INSERT    = 0x6C00
    };
    
    class View {
    public:
        virtual ~View();
        
        virtual void display() = 0;
        
        virtual void init() = 0;
        virtual void end() = 0;
        
        virtual void overlay() = 0;
        virtual void reshape(int width, int height) = 0;
        virtual void keyPressed(int ch) = 0;
        virtual void mousePressed(MouseButton button, ButtonState state) = 0;
        virtual void motion(int x, int y) = 0;
        virtual void passiveMotion(int x, int y) = 0;
        virtual void entry(int state) = 0;
        virtual void idle() = 0;
        
        static void InitViewSystem(int argc, char **argv, Window *window);
        static void EnterMainLoop(View &initial);
        static void Exit();
        static void EndViewSystem();
        static void RegisterTimer(TimerFn_t timerfn, int value, int ms);
        static void PostRedisplay();
        static void SetCurrent(View &view);
    protected:
        View();
    private:
        static View *CurrentView;
        static bool Init, InMainLoop;
        
        static void DisplayCallback();
        static void OverlayCallback();
        static void ReshapeCallback(int width, int height);
        static void KeyboardCallback(unsigned char ch, int x, int y);
        static void SpecialCallback(int ch, int x, int y);
        static void MouseCallback(int button, int state, int x, int y);
        static void MotionCallback(int x, int y);
        static void PassiveMotionCallback(int x, int y);
        static void EntryCallback(int state);
        static void IdleCallback();
    };
    
    class BasicView : public View {
    public:
        virtual ~BasicView();
        
        virtual void init();
        virtual void end();
        virtual void overlay();
        virtual void reshape(int width, int height);
        virtual void keyPressed(int ch);
        virtual void mousePressed(MouseButton button, ButtonState state);
        virtual void motion(int x, int y);
        virtual void passiveMotion(int x, int y);
        virtual void entry(int state);
        virtual void idle();
    protected:
        BasicView();
        
        struct {
            struct {
                int x, y;
            } pos;
            uint32_t state;
            bool isInWindow;
        } mouse;
        
        struct {
            double aspect_ratio;
            struct {
                int width, height;
            } dim;
        } win;
    };
}

#endif
