#ifndef QUAT_H
#define QUAT_H

#include "math/vec3.h"

namespace sandista {

class quat {
public:
    vec3 v;
    float w;
    float& x;
    float& y;
    float& z;

    inline quat(float x = 0, float y = 0, float z = 0, float w = 1)
        : v(x, y, z), w(w), x(v.x), y(v.y), z(v.z) {}

    inline quat(const vec3& cv, float w = 1) : v(cv), w(w), x(v.x), y(v.y), z(v.z) {}

    inline quat operator*(quat other)
    {
        return quat(v.cross(other.v) + v * other.w + other.v * w, w * other.w - v * other.v);
    }

    inline void operator*= (quat other)
    {
        vec3 vx(v);
        v = vx.cross(other.v) + vx * other.w + other.v * w;
        w = w * other.w - vx * other.v;

    }


};

}

#endif // QUAT_H
