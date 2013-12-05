
#include <cstdio>
#include <iostream>

#include "Time.hpp"
#include "TraceView.hpp"
#include "View.hpp"
#include "Window.hpp"

#include "Vector.hpp"
#include "Geometry.hpp"
#include "Point.hpp"

using namespace cs354;
static int _width = 640;
static int _height = 480;

int main(int argc, char **argv) {
    Window win("Raytrace - Troy Varney", _width, _height, 10, 10,
               Window::RGB | Window::DOUBLE);
    View::InitViewSystem(argc, argv, &win);
    TraceView traceview;
    View::EnterMainLoop(traceview);
    
    std::printf("Total running time: %llu ms\n",
                (unsigned long long)Time.getTimeMillis());
    return 0;
}
