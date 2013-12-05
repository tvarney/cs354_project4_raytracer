
#include "Window.hpp"

#define CS354_GENERIC_IMPL
#include "common.hpp"

using namespace cs354;

const int Window::RGBA = GLUT_RGBA;
const int Window::RGB = GLUT_RGB;
const int Window::INDEX = GLUT_INDEX;
const int Window::SINGLE = GLUT_SINGLE;
const int Window::DOUBLE = GLUT_DOUBLE;
const int Window::ACCUM = GLUT_ACCUM;
const int Window::ALPHA = GLUT_ALPHA;
const int Window::DEPTH = GLUT_DEPTH;
const int Window::STENCIL = GLUT_STENCIL;
const int Window::MULTISAMPLE = GLUT_MULTISAMPLE;
const int Window::STEREO = GLUT_STEREO;
const int Window::LUMINANCE = GLUT_LUMINANCE;

Window::Window(const char *title, int width, int height) :
    title(title), width(width), height(height), x(10), y(10), mode(0)
{ }
Window::Window(const char *title, int width, int height, int mode) :
    title(title), width(width), height(height), x(10), y(10), mode(mode)
{ }
Window::Window(const char *title, int width, int height, int x, int y) :
    title(title), width(width), height(height), x(x), y(y), mode(0)
{ }
Window::Window(const char *title, int width, int height, int x, int y,
               int mode) :
    title(title), width(width), height(height), x(x), y(y), mode(mode)
{ }
Window::~Window() { }
