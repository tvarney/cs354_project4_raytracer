
#ifndef CS354_PROJECT4_ATOMIC_HPP
#define CS354_PROJECT4_ATOMIC_HPP

namespace cs354 {
    // Atomic::Add<uint32_t>();
    // Atomic<uint32_t>::Add();
    namespace Atomic {
        template <typename valtype>
        valtype Add(volatile valtype &value, valtype amt) {
            return __sync_fetch_and_add(&value, amt);
        }
        template <typename valtype>
        valtype Sub(volatile valtype &value, valtype amt) {
            return __sync_fetch_and_sub(&value, amt);
        }
        
        template <typename valtype>
        valtype Inc(volatile valtype &value) {
            return __sync_fetch_and_add(&value, 1);
        }
        template <typename valtype>
        valtype Dec(volatile valtype &value) {
            return __sync_fetch_and_sub(&value, 1);
        }
    }
}

#endif
