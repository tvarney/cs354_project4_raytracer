
#ifndef CS354_PROJECT4_RAY_THREAD_HPP
#define CS354_PROJECT4_RAY_THREAD_HPP

#include "Canvas.hpp"
#include "Scene.hpp"
#include "Thread.hpp"

namespace cs354 {
    class RayThread : public Thread {
        RayThread(Canvas &canvas, Scene &scene);
        virtual ~RayThread();
        
        virtual void run();
        
        void add(size_t row);
    protected:
        Canvas &canvas;
        Scene &scene;
        
        std::vector<size_t> rows;
    };
}

#endif
