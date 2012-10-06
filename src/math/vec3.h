#ifndef SANDISTA_VEC3_H
#define SANDISTA_VEC3_H

namespace sandista {

class vec3
{
public:
    inline vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    float x, y, z;

    inline vec3 operator+(const vec3& other) {
        return vec3(x + other.x, y + other.y, z + other.z);
    }

    inline vec3 operator-(const vec3& other) {
        return vec3(x - other.x, y - other.y, z - other.z);
    }

    inline vec3 operator*(float other) {
        return vec3(x * other, y * other, z * other);
    }

    inline vec3 operator/(float other) {
        return vec3(x / other, y / other, z / other);
    }

    inline void operator+=(vec3 other) {
        x += other.x;
        y += other.y;
        z += other.z;
    }

    inline void operator-=(vec3 other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

    inline void operator*=(float other) {
        x *= other;
        y *= other;
        z *= other;
    }

    inline void operator/=(float other) {
        x /= other;
        y /= other;
        z /= other;
    }

    inline float operator*(vec3 other) {
        return x * other.x + y * other.y + z * other.z;
    }

    inline vec3 cross(vec3 b) {
        return vec3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
};

} // namespace sandista

#endif // SANDISTA_VEC2_H
