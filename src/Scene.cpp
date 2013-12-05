
#include "Scene.hpp"

#include <cmath>
#include <cstdio>
#include "Geometry.hpp"

using namespace cs354;

static const Color _DefaultAmbient(0.2, 0.2, 0.2);
static const double _DefaultCutoff = 0.05;

Scene::Scene() :
    _ambient(_DefaultAmbient), _cutoff(_DefaultCutoff), _reflect(true)
{ }
Scene::Scene(const Color ambient) :
    _ambient(ambient), _cutoff(_DefaultCutoff), _reflect(true)
{ }
Scene::Scene(double cutoff) :
    _ambient(_DefaultAmbient), _cutoff(_DefaultCutoff), _reflect(true)
{ }
Scene::Scene(const Color ambient, double cutoff) :
    _ambient(ambient), _cutoff(cutoff), _reflect(true)
{ }
Scene::~Scene() {
    for(size_t i = 0; i < _objs.size(); ++i) {
        delete _objs[i];
        _objs[i] = NULL;
    }
}

void Scene::add(const Object &object) {
    _objs.push_back(object.clone());
}
void Scene::add(const Light light) {
    _lights.push_back(light);
}

void Scene::clear() {
    _objs.erase(_objs.begin(), _objs.end());
    _lights.erase(_lights.begin(), _lights.end());
}

const std::vector<Object *> Scene::objects() const {
    return _objs;
}
const std::vector<Light> Scene::lights() const {
    return _lights;
}

void Scene::ambient(const Color color) {
    _ambient = color;
}
Color Scene::ambient() const {
    return _ambient;
}
double Scene::cutoff() const {
    return _cutoff;
}
void Scene::cutoff(double value) {
    _cutoff = value;
}
void Scene::reflect(bool value) {
    _reflect = value;
}
bool Scene::reflect() const {
    return _reflect;
}

Color Scene::trace(const Ray ray, uint32_t depth) const {
    return trace(ray, depth, 1.0, NULL);
}

Color Scene::trace(const Ray ray, uint32_t depth, double c, Object *parent)
    const
{
    Ray normal;
    Object *obj = intersect(ray, normal, parent);
    
    if(obj == NULL) {
        return (parent != NULL ? _ambient : Color::Black);
    }
    
    /* Initialize direct light contribution from scene ambient */
    Color direct;
    if(Light::Ambient) {
        direct += obj->material().base * _ambient;
    }
    
    Ray lightray, lightnorm;
    Object *blocking = NULL;
    for(size_t i = 0; i < _lights.size(); ++i) {
        /* Get new ray origin from intersection point - the origin of the ray
         * is displaced a tiny bit to keep it from intersecting with the same
         * position.
         */
        if(_lights[i].point == false) {
            direct += _lights[i].get(ray, normal, obj->material());
        }else {
            lightray.origin = normal.origin;
            lightray.direction = _lights[i].direction(lightray.origin);
            lightray.origin = lightray.origin + (lightray.direction * 0.001);
            blocking = intersect(lightray, lightnorm, NULL);
            /* TODO: Check if the blocking object is transparent;
             * if so, calculate refracted rays.
             */
            Point3d lightpos(_lights[i].x, _lights[i].y, _lights[i].z);
            if(blocking == NULL) {
                direct += _lights[i].get(ray, normal, obj->material());
            }else {
                double d1 = (lightpos - lightray.origin).magsquared();
                double d2 = (lightnorm.origin - lightray.origin).magsquared();
                if(d1 < d2) {
                    direct += _lights[i].get(ray, normal, obj->material());
                }else if(blocking->material().kt > 0.0) {
                    direct += _lights[i].get(ray, normal, obj->material()) *
                        blocking->material().kt;
                    
                }
            }
        }
    }
    
    double kr = obj->material().kr;
    double kt = obj->material().kt;
    /* */
    /* If reflective, get new ray and trace */
    Color reflection;
    if(_reflect && c * kr > _cutoff && depth > 1) {
        Ray reflect_ray;
        reflect_ray.origin = normal.origin;
        /* There is a problem with the reflection code; THIS PRODUCES THE
           RIGHT RESULTS */
        reflect_ray.direction =
            -cs354::reflect(ray.direction, normal.direction);
        reflect_ray.direction.z *= -1;
        reflection = trace(reflect_ray, depth - 1, c * kr, obj);
    }
    
    /* If translucent, get new ray and trace */
    Color c_refracted;
    double tamt = 0.0;
    if(c * kt > _cutoff && depth > 1) {
        //direct = Color::Black;
        c_refracted = trace(ray, depth - 1, c * kt, obj);
    }
    
    /*
    if(!_reflect) {
        kr = 0.0;
    }
    double total = tamt + kr;
    if(total > 1.0) {
        tamt /= total;
        kr /= total;
        total = 1.0;
    }
    double kd = 1.0 - total;
    */
    return (direct * c) + (reflection) + (c_refracted);
}

Object* Scene::intersect(const Ray ray, Ray & normal, const Object *ignore)
    const
{
    Object *obj = NULL;
    double dist = INFINITY, ndist;
    Ray inorm;
    
    size_t nobjs = _objs.size();
    for(size_t i = 0; i < nobjs; ++i) {
        if(_objs[i] == ignore) {
            continue;
        }
        if(_objs[i]->intersect(ray, inorm)) {
            ndist = (ray.origin - inorm.origin).magsquared();
            if(ndist < dist) {
                obj = _objs[i];
                normal = inorm;
                dist = ndist;
            }
        }
    }
    
    return obj;
}
