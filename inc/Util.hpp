
#ifndef CS354_PROJECT4_UTIL_HPP
#define CS354_PROJECT4_UTIL_HPP

#include "Color.hpp"
#include "Vector.hpp"

namespace cs354 {
    template <typename T>
    inline Color NormalToColor(const Vector<T> normal) {
        return Color((normal.x + 1.0) * 0.5, (normal.y + 1.0) * 0.5,
                     (normal.z + 1.0) * 0.5);
    }
}

#endif
