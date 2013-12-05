
#include "Time.hpp"

#include <cstdlib>
#include <cstdio>

#ifdef __MAC__
# include <CoreServices/CoreServices.h>
# include <mach/mach.h>
# include <mach/mach_time.h>
#else
# include <time.h>
#endif

using namespace cs354;

#ifdef __MAC__
static mach_timebase_info_data_t sTimebaseInfo;
#else
struct ClockSpec {
    bool valid;
    clockid_t id;
};
static ClockSpec clocks[] = {
#if defined(CLOCK_PROCESS_CPUTIME_ID)
    {true, CLOCK_PROCESS_CPUTIME_ID},
#endif
#if defined(CLOCK_MONOTONIC_RAW)
    {true, CLOCK_MONOTONIC_RAW},
#endif
#if defined(CLOCK_MONOTONIC)
    {true, CLOCK_MONOTONIC},
#endif
#if defined(CLOCK_REALTIME)
    /* Guaranteed to exist, error if it doesn't */
    {true, CLOCK_REALTIME},
#else
# error "Realtime clock not defined"
#endif
    {false, 0}
};

static clockid_t _clock_used;
#endif

static inline bool _init_timer() {
#ifdef __MAC__
    mach_timebase_info(&sTimebaseInfo);
    return true;
#else
    struct timespec ts;
    for(ClockSpec *c = &(clocks[0]); c->valid; ++c) {
        if(clock_gettime(c->id, &ts) == 0) {
            _clock_used = c->id;
            return true;
        }
    }
    return false;
#endif
}

static bool _timer_init = false;

Timer::Timer() {
    if(!_timer_init) {
        if(!_init_timer()) {
            /* If we couldn't initialize the timer, kill the process. */
            std::fprintf(stderr, "Unable to initialize time subsystem\n");
            std::exit(1);
        }
        _timer_init = true;
    }
    
    initial = getTime();
}
Timer::~Timer() { }

uint64_t Timer::getTimeNanos() {
    return getTime() - initial;
}
uint64_t Timer::getTimeMillis() {
    return getTimeNanos() / 1000000;
}

uint64_t Timer::getTime() {
#ifdef __MAC__
    return mach_absolute_time() * sTimebaseInfo.numer / sTimebaseInfo.denom;
#else
    timespec ts;
    clock_gettime(_clock_used, &ts);
    return (ts.tv_sec * 1000000000) + ts.tv_nsec;
#endif
}
