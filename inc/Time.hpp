
#ifndef CS354_PROJECT4_TIME_HPP
#define CS354_PROJECT4_TIME_HPP

#include <stdint.h>

namespace cs354 {
    class Timer {
    public:
        Timer();
        ~Timer();
        
        uint64_t getTimeNanos();
        uint64_t getTimeMillis();
    protected:
        uint64_t getTime();
        
        /* A uint64_t can store over 35096.5 years in nanoseconds */
        uint64_t initial;
    };
    
    static Timer Time;
}

#endif
