
#include "TraceView.hpp"

#include <cstdio>
#include "Cylinder.hpp"
#include "Geometry.hpp"
#include "InfinitePlane.hpp"
#include "Sphere.hpp"

#include "Util.hpp"

using namespace cs354;

TraceView::TraceView() :
    do_light1(true), do_light2(true),
    fov(75.0), render(true), trace_done(false), resize(false), last_update(0)
{ }
TraceView::~TraceView() { }

void TraceView::init() {
    BasicView::init();
    std::printf("Window size: %llux%llu\n",
                (unsigned long long)win.dim.width,
                (unsigned long long)win.dim.height);
    render = true;
    trace_done = false;
    resize = true;
    make_glass = false;
    do_light1 = true;
    do_light2 = true;
    move = Vector3d();
    
    load(NULL);
}

void TraceView::end() {
    canvas.resize(0, 0);
}

static double _pixel_to_meter = 0.05;

static Material _purple =
    Material(1.0, 20, 0.0, 0.0, 0.0,
             Color(0.6, 0.4, 0.6), Color(1.0, 0.8, 1.0));
static Material _red =
    Material(1.0, 100, 0.25, 0.0, 0.0,
             Color(0.4, 0.1, 0.1), Color(0.9, 0.3, 0.3));
static Material _green =
    Material(1.0, 10, 0.0, 0.0, 0.0,
             Color(0.1, 0.33, 0.1), Color(0.4, 0.9, 0.4));

void TraceView::display() {
    Light light1(Point3d(30, 25, 30), Color(0.75, 0.75, 0.75));
    Light light2(Point3d(0, -10, -1), Color(0.75, 0.75, 0.75));
    Light light3(Point3d(-50, 20, 50), Color(0.75,0.1,0.1));
    Sphere s1(Point3d(0,0,100), 30, Material::Mirror);
    Sphere s2(Point3d(14, 0, 60), 5, _purple);
    Sphere s3(Point3d(-20,0, 30), 5, Material::Glass);
    Sphere s4(Point3d(-35, 15, 25), 15, _purple);
    Sphere s5(Point3d(35, 5, 100), 5, _purple);
    InfinitePlane floor(Vector3d(0, -1, 0), -32, _green);
    Cylinder cylinder(Point3d(100, 0, 50), 1, 100, _purple);
    
    scene.clear();
    
    scene.add(floor);
    scene.add(s1);
    scene.add(s2);
    scene.add(s3);
    scene.add(s4);
    scene.add(s5);
    scene.add(cylinder);
    if(do_light1) {
        scene.add(light1);
    }
    if(do_light2) {
        scene.add(light2);
    }
    //scene.add(light3);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    
    double width, height, half_width, half_height;
    if(resize) {
        canvas.resize(win.dim.width, win.dim.height);
        width = double(canvas.width()) * _pixel_to_meter;
        height = double(canvas.height()) * _pixel_to_meter;
        half_width = width * 0.5;
        half_height = height * 0.5;
        double r_d = 2.0 * std::sin((M_PI / 180.0) * (fov * 0.5));
        double r = width / r_d;
        z_camera = -(std::sqrt(r * r - half_width * half_width));
        resize = false;
    }else {
        width = double(canvas.width()) * _pixel_to_meter;
        height = double(canvas.height()) * _pixel_to_meter;
        half_width = width * 0.5;
        half_height = height * 0.5;
    }
    
    if(render) {
        Ray r;
        Point3d origin(0, 0, z_camera);
        for(size_t y = 0; y < canvas.height(); ++y) {
            for(size_t x = 0; x < canvas.width(); ++x) {
                r.origin = Point3d(double(x) * _pixel_to_meter - half_width,
                                   half_height - double(y) * _pixel_to_meter,
                                   0.0);
                
                r.direction = (r.origin - origin).normalize();
                canvas.set(x, y, scene.trace(r));
            }
        }
        render = false;
    }
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glRasterPos2i(0,0);
    /* Drawing pixels */
    glDrawPixels(canvas.width(), canvas.height(), GL_RGB, GL_UNSIGNED_BYTE,
                 canvas.data());
}

void TraceView::reshape(int width, int height) {
    BasicView::reshape(width, height);
    resize = true;
    render = true;
    View::PostRedisplay();
}

void TraceView::keyPressed(int ch) {
    switch(ch) {
    case 'q':
        View::Exit();
        break;
    case 'a':
        Light::Ambient = !Light::Ambient;
        render = true;
        View::PostRedisplay();
        break;
    case 'd':
        Light::Diffuse = !Light::Diffuse;
        render = true;
        View::PostRedisplay();
        break;
    case 's':
        Light::Specular = !Light::Specular;
        render = true;
        View::PostRedisplay();
        break;
    case '1':
        do_light1 = !do_light1;
        render = true;
        View::PostRedisplay();
        break;
    case '2':
        do_light2 = !do_light2;
        render = true;
        View::PostRedisplay();
        break;
    case 'r':
        scene.reflect(!scene.reflect());
        render = true;
        View::PostRedisplay();
        break;
    case 'g':
        make_glass = !make_glass;
        render = true;
        View::PostRedisplay();
        break;
    case 'h':
        Light::Half = !Light::Half;
        render = true;
        View::PostRedisplay();
        break;
    case 'A':
        Light::Attenuate = !Light::Attenuate;
        render = true;
        View::PostRedisplay();
        break;
    case KEY_LEFT:
        move += Vector3d(-1, 0, 0);
        //render = true;
        View::PostRedisplay();
        break;
    case KEY_RIGHT:
        move += Vector3d(1, 0, 0);
        //render = true;
        View::PostRedisplay();
        break;
    case KEY_DOWN:
        move += Vector3d(0, 1, 0);
        //render = true;
        View::PostRedisplay();
        break;
    case KEY_UP:
        move += Vector3d(0, -1, 0);
        //render = true;
        View::PostRedisplay();
        break;
    }
}

void TraceView::mousePressed(MouseButton button, ButtonState state) {
    BasicView::mousePressed(button, state);
}

void TraceView::load(const char *fname) {
}
