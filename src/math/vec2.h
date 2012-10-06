#ifndef SANDISTA_VEC2_H
#define SANDISTA_VEC2_H

namespace sandista {

class vec2
{
public:
    inline vec2(float x = 0, float y = 0) : x(x), y(y) {}
    float x, y;

    inline vec2 operator+(const vec2& other) {
        return vec2(x + other.x, y + other.y);
    }

    inline vec2 operator-(const vec2& other) {
        return vec2(x - other.x, y - other.y);
    }

    inline vec2 operator*(float other) {
        return vec2(x * other, y * other);
    }

    inline vec2 operator/(float other) {
        return vec2(x / other, y / other);
    }

    inline void operator+=(vec2 other) {
        x += other.x;
        y += other.y;
    }

    inline void operator-=(vec2 other) {
        x -= other.x;
        y -= other.y;
    }

    inline void operator*=(float other) {
        x *= other;
        y *= other;
    }

    inline void operator/=(float other) {
        x /= other;
        y /= other;
    }

    inline float operator*(vec2 other) {
        return x * other.x + y * other.y;
    }
};

} // namespace sandista

#endif // SANDISTA_VEC2_H
