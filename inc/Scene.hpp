
#ifndef CS354_PROJECT4_SCENE_HPP
#define CS354_PROJECT4_SCENE_HPP

#include <vector>
#include "Light.hpp"
#include "Object.hpp"
#include "Ray.hpp"

namespace cs354 {
    /**
     * The class that manages a scene and the raytracing algorithm proper.
     */
    class Scene {
    public:
        Scene();
        Scene(const Color ambient);
        Scene(double cutoff);
        Scene(const Color ambient, double cutoff);
        ~Scene();
        
        void add(const Object &object);
        void add(const Light light);
        
        void clear();
        
        const std::vector<Object *> objects() const;
        const std::vector<Light> lights() const;
        void ambient(const Color color);
        Color ambient() const;
        void cutoff(double value);
        double cutoff() const;
        void reflect(bool value);
        bool reflect() const;
        
        /**
         * Trace the given ray through the scene, with the maximum depth as
         * given here. The ray will be stopped if it's contribution to the
         * final color is determined to be less than the cutoff.
         */
        Color trace(const Ray ray, uint32_t depth = 10) const;
    protected:
        /**
         * Protected method to implement the raytracing with the given
         * contribution factor. Only called if the ray doesn't stop on the
         * first trace.
         */
        Color trace(const Ray ray, uint32_t depth, double c,
                    Object *parent) const;
        /**
         * Find and return data about the closest object in the scene.
         */
        Object* intersect(const Ray ray, Ray &normal,
                          const Object *ignore = NULL) const;
        
        /* I might change this to a oct-tree if I figure out how to implement
         * one well. The good news is that _objs won't be changing during
         * rendering, so the oct-tree would only need to be built once then
         * provide a big speedup for complex scenes.
         */
        /*TODO: Implement an Oct-tree */
        std::vector<Object *> _objs;
        std::vector<Light> _lights;
        Color _ambient;
        double _cutoff;
        bool _reflect;
    };
}

#endif
