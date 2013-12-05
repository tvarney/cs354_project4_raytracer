
#ifndef CS354_PROJECT4_THREAD_HPP
#define CS354_PROJECT4_THREAD_HPP

#include <pthread.h>
#include <stdint.h>

namespace cs354 {
    class Thread {
    public:
        virtual ~Thread();
        
        virtual void run() = 0;
        
        virtual void start();
        uint64_t id() const;
        void cancel();
        void join() const;
        
        static void Exit(void *status = NULL);
    protected:
        Thread();
        pthread_t handle();
        
    private:
        uint64_t _id;
        pthread_t _handle;
        static volatile uint64_t NextId;
    };
}

#endif
