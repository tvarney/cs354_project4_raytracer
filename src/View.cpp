
#include "View.hpp"

#include <stddef.h>
#include <setjmp.h>
#include "common.hpp"
#include "Window.hpp"

using namespace cs354;

View * View::CurrentView = NULL;
bool View::Init = false, View::InMainLoop = false;

View::View() { }
View::~View() { }

void View::InitViewSystem(int argc, char **argv, Window *window) {
    if(!View::Init) {
        glutInit(&argc, argv);
        const char *title = "";
        if(window != NULL) {
            title = window->title.c_str();
            glutInitWindowSize(window->width, window->height);
            glutInitWindowPosition(window->x, window->y);
            glutInitDisplayMode(window->mode);
        }
        glutCreateWindow(title);
    }
    
    glutDisplayFunc(View::DisplayCallback);
    glutOverlayDisplayFunc(View::OverlayCallback);
    glutReshapeFunc(View::ReshapeCallback);
    glutKeyboardFunc(View::KeyboardCallback);
    glutSpecialFunc(View::SpecialCallback);
    glutMouseFunc(View::MouseCallback);
    glutMotionFunc(View::MotionCallback);
    glutPassiveMotionFunc(View::PassiveMotionCallback);
    glutEntryFunc(View::EntryCallback);
    glutIdleFunc(View::IdleCallback);
}

static jmp_buf environment;
void View::EnterMainLoop(View &initial) {
    View::SetCurrent(initial);
    if(!View::InMainLoop) {
        View::InMainLoop = true;
        
        if(setjmp(environment)) {
            /* We have called View::Exit */
            View::InMainLoop = false;
            return;
        }
        
        /* After initializing our environment, start the glutMainLoop. */
        glutMainLoop();
    }
}

void View::Exit() {
    if(View::InMainLoop) {
        longjmp(environment, 1);
    }
}

void View::EndViewSystem() {
    View::CurrentView = NULL;
    View::Init = false;
    
    glutDisplayFunc(NULL);
    glutOverlayDisplayFunc(NULL);
    glutReshapeFunc(NULL);
    glutKeyboardFunc(NULL);
    glutSpecialFunc(NULL);
    glutMouseFunc(NULL);
    glutMotionFunc(NULL);
    glutPassiveMotionFunc(NULL);
    glutEntryFunc(NULL);
    glutIdleFunc(NULL);
}
void View::RegisterTimer(TimerFn_t timerfn, int value, int ms) {
    glutTimerFunc(ms, timerfn, value);
}

void View::PostRedisplay() {
    glutPostRedisplay();
}
void View::SetCurrent(View &view) {
    if(View::CurrentView != NULL) {
        View::CurrentView->end();
    }
    View::CurrentView = &view;
    view.init();
    PostRedisplay();
}

void View::DisplayCallback() {
    if(View::CurrentView) {
        View::CurrentView->display();
        
        glFlush();
        glutSwapBuffers();
    }
}
void View::OverlayCallback() {
    if(View::CurrentView) {
        View::CurrentView->overlay();
    }
}
void View::ReshapeCallback(int width, int height) {
    if(View::CurrentView) {
        View::CurrentView->reshape(width, height);
    }
}
void View::KeyboardCallback(unsigned char ch, int x, int y) {
    if(View::CurrentView) {
        View::CurrentView->keyPressed(ch);
    }
}
#define ADJUST_GLUT_KEYCODE(ch) ((ch) << 8)
void View::SpecialCallback(int ch, int x, int y) {
    if(View::CurrentView) {
        View::CurrentView->keyPressed(ADJUST_GLUT_KEYCODE(ch));
    }
}
void View::MouseCallback(int button, int state, int x, int y) {
    if(View::CurrentView) {
        MouseButton mButton = MOUSE_BUTTON_LEFT;
        ButtonState mState = (state == GLUT_UP ? BUTTON_UP : BUTTON_DOWN);
        switch(button) {
        case GLUT_LEFT_BUTTON:
            mButton = MOUSE_BUTTON_LEFT;
            break;
        case GLUT_RIGHT_BUTTON:
            mButton = MOUSE_BUTTON_RIGHT;
            break;
        case GLUT_MIDDLE_BUTTON:
            mButton = MOUSE_BUTTON_MIDDLE;
            break;
        default:
            return;
        }
        
        View::CurrentView->mousePressed(mButton, mState);
    }
}
void View::MotionCallback(int x, int y) {
    if(View::CurrentView) {
        View::CurrentView->motion(x, y);
    }
}
void View::PassiveMotionCallback(int x, int y) {
    if(View::CurrentView) {
        View::CurrentView->passiveMotion(x, y);
    }
}
void View::EntryCallback(int state) {
    if(View::CurrentView) {
        View::CurrentView->entry(state);
    }
}
void View::IdleCallback() {
    if(View::CurrentView) {
        View::CurrentView->idle();
    }
}

BasicView::BasicView() {
    win.dim.width = glutGet(GLUT_WINDOW_WIDTH);
    win.dim.height = glutGet(GLUT_WINDOW_HEIGHT);
    win.aspect_ratio = double(win.dim.width) / double(win.dim.height);
}
BasicView::~BasicView() { }

/* Stubbed functions */
void BasicView::init() {
    win.dim.width = glutGet(GLUT_WINDOW_WIDTH);
    win.dim.height = glutGet(GLUT_WINDOW_HEIGHT);
    win.aspect_ratio = double(win.dim.width) / double(win.dim.height);
}
void BasicView::end() { }
void BasicView::overlay() { }
void BasicView::reshape(int width, int height) {
    win.aspect_ratio = (double(width) / double(height));
    win.dim.width = width;
    win.dim.height = height;
}
void BasicView::keyPressed(int ch) { }
void BasicView::idle() { }

/* Implemented functions  */
void BasicView::mousePressed(MouseButton button, ButtonState state) {
    uint32_t bmask = (uint32_t)button;
    if(state == BUTTON_UP) {
        mouse.state &= ~bmask;
    }else {
        mouse.state |= bmask;
    }
}

void BasicView::passiveMotion(int x, int y) {
    mouse.pos.x = x;
    mouse.pos.y = y;
}

void BasicView::motion(int x, int y) {
    mouse.pos.x = x;
    mouse.pos.y = y;
}

void BasicView::entry(int state) {
    mouse.isInWindow = (state = GLUT_ENTERED);
}
