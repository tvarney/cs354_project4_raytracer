
#include "Thread.hpp"

#include "Atomic.hpp"

using namespace cs354;

volatile uint64_t Thread::NextId = 0;

Thread::Thread() :
    _id(Atomic::Inc<uint64_t>(Thread::NextId))
{
    
}
Thread::~Thread() {
    join();
}

static void * run_thread(void *ptr) {
    ((Thread *)ptr)->run();
    return NULL;
}
void Thread::start() {
    pthread_create(&_handle, NULL, &run_thread, this);
}

uint64_t Thread::id() const {
    return _id;
}

void Thread::join() const {
    pthread_join(_handle, NULL);
}
void Thread::cancel() {
    pthread_cancel(_handle);
}

pthread_t Thread::handle() {
    return _handle;
}

