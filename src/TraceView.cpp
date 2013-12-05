
#include "TraceView.hpp"

#include <cstdio>
#include "Geometry.hpp"
#include "InfinitePlane.hpp"

#include "Util.hpp"

using namespace cs354;

static Material _mat = Material(1.2, 50, 0.0, 0.0, 0.0,
                                Color(0.8, 0.6, 0.8), Color(1.0, 0.8, 1.0));
TraceView::TraceView() :
    s1(Point3d(0, 0, 50), 30, Material::Mirror),
    s2(Point3d(15, 0, 10), 2, _mat),
    light1(Point3d(100, 25, 100), Color::Red),
    light2(Point3d(0, 20, -2)),
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
    do_light1 = false;
    
    load(NULL);
}

void TraceView::end() {
    canvas.resize(0, 0);
}

static double _pixel_to_meter = 0.05;

void TraceView::display() {
    Sphere glass(s2);
    glass.material(Material::Glass);
    InfinitePlane floor(Vector3d(0, 1, 0), -100, Material::Mirror);
    
    scene.clear();
    scene.add(floor);
    scene.add(s1);
    if(make_glass) {
        scene.add(glass);
    }else {
        scene.add(s2);
    }
    if(do_light1) {
        scene.add(light1);
    }
    if(do_light2) {
        scene.add(light2);
    }
    
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
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
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
        s2.move(Vector3d(-1, 0, 0));
        render = true;
        View::PostRedisplay();
        break;
    case KEY_RIGHT:
        s2.move(Vector3d(1, 0, 0));
        render = true;
        View::PostRedisplay();
        break;
    case KEY_DOWN:
        s2.move(Vector3d(0, 1, 0));
        render = true;
        View::PostRedisplay();
        break;
    case KEY_UP:
        s2.move(Vector3d(0, -1, 0));
        render = true;
        View::PostRedisplay();
        break;
    }
}

void TraceView::mousePressed(MouseButton button, ButtonState state) {
    BasicView::mousePressed(button, state);
}

void TraceView::load(const char *fname) {
}
