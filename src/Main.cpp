
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

void test_reflect(Vector3d v, Vector3d n) {
    std::cout << "reflect(" << v << ", " << n << ") = " << reflect(v, n) <<
        std::endl;
}
void test() {
    Vector3d n1(1, 0, 0);
    Vector3d n2(0, 1, 0);
    Vector3d n3(0, 0, 1);
    
    Vector3d v1 = normalize(Vector3d(5, 2, 4));
    Vector3d v2 = normalize(Vector3d(1, 0, 2));
    Vector3d v3 = normalize(Vector3d(2, 3, 0));
    
    test_reflect(v1, n1);
    test_reflect(v2, n1);
    test_reflect(v3, n1);
    std::cout << std::endl;
    
    test_reflect(v1, n2);
    test_reflect(v2, n2);
    test_reflect(v3, n2);
    std::cout << std::endl;
    
    test_reflect(v1, n3);
    test_reflect(v2, n3);
    test_reflect(v3, n3);
    std::cout << std::endl;
}

static int _width = 640;
static int _height = 480;

int main(int argc, char **argv) {
    test();
    Window win("Raytrace - Troy Varney", _width, _height, 10, 10,
               Window::RGB | Window::DOUBLE);
    View::InitViewSystem(argc, argv, &win);
    TraceView traceview;
    View::EnterMainLoop(traceview);
    
    std::printf("Total running time: %llu ms\n",
                (unsigned long long)Time.getTimeMillis());
    return 0;
}
