#ifndef MAT4_H
#define MAT4_H

#include "memory.h"

namespace sandista {

class mat4 {
private:
    float* mtx;
public:

    inline mat4()
    {
        mtx = new float[16];
    }

    inline ~mat4()
    {
        delete[] mtx;
    }

    inline mat4(const mat4& other) {
        mtx = new float[16];
        memcpy(mtx, other.mtx, sizeof(float) * 16);
    }

    inline mat4(mat4&& other)
    {
        mtx = other.mtx;
    }

    inline float& operator[] (int id)
    {
        return mtx[id];
    }

    inline mat4 operator*(mat4 other)
    {

        mat4 M;
        M[ 0] = mtx[ 0] * other[ 0] + mtx[ 1] * other[ 4] + mtx[ 2] * other[ 8] + mtx[ 3] * other[12];
        M[ 1] = mtx[ 0] * other[ 1] + mtx[ 1] * other[ 5] + mtx[ 2] * other[ 9] + mtx[ 3] * other[13];
        M[ 2] = mtx[ 0] * other[ 2] + mtx[ 1] * other[ 6] + mtx[ 2] * other[10] + mtx[ 3] * other[14];
        M[ 3] = mtx[ 0] * other[ 3] + mtx[ 1] * other[ 7] + mtx[ 2] * other[11] + mtx[ 3] * other[15];
        M[ 4] = mtx[ 4] * other[ 0] + mtx[ 5] * other[ 4] + mtx[ 6] * other[ 8] + mtx[ 7] * other[12];
        M[ 5] = mtx[ 4] * other[ 1] + mtx[ 5] * other[ 5] + mtx[ 6] * other[ 9] + mtx[ 7] * other[13];
        M[ 6] = mtx[ 4] * other[ 2] + mtx[ 5] * other[ 6] + mtx[ 6] * other[10] + mtx[ 7] * other[14];
        M[ 7] = mtx[ 4] * other[ 3] + mtx[ 5] * other[ 7] + mtx[ 6] * other[11] + mtx[ 7] * other[15];
        M[ 8] = mtx[ 8] * other[ 0] + mtx[ 9] * other[ 4] + mtx[10] * other[ 8] + mtx[11] * other[12];
        M[ 9] = mtx[ 8] * other[ 1] + mtx[ 9] * other[ 5] + mtx[10] * other[ 9] + mtx[11] * other[13];
        M[10] = mtx[ 8] * other[ 2] + mtx[ 9] * other[ 6] + mtx[10] * other[10] + mtx[11] * other[14];
        M[11] = mtx[ 8] * other[ 3] + mtx[ 9] * other[ 7] + mtx[10] * other[11] + mtx[11] * other[15];
        M[12] = mtx[12] * other[ 0] + mtx[13] * other[ 4] + mtx[14] * other[ 8] + mtx[15] * other[12];
        M[13] = mtx[12] * other[ 1] + mtx[13] * other[ 5] + mtx[14] * other[ 9] + mtx[15] * other[13];
        M[14] = mtx[12] * other[ 2] + mtx[13] * other[ 6] + mtx[14] * other[10] + mtx[15] * other[14];
        M[15] = mtx[12] * other[ 3] + mtx[13] * other[ 7] + mtx[14] * other[11] + mtx[15] * other[15];

        return M;
    }

    inline void operator*=(mat4 B) {
        float* A = new float[16];
        memcpy(A, mtx, sizeof(float) * 16);

        mtx[ 0] = A[ 0] * B[ 0] + A[ 1] * B[ 4] + A[ 2] * B[ 8] + A[ 3] * B[12];
        mtx[ 1] = A[ 0] * B[ 1] + A[ 1] * B[ 5] + A[ 2] * B[ 9] + A[ 3] * B[13];
        mtx[ 2] = A[ 0] * B[ 2] + A[ 1] * B[ 6] + A[ 2] * B[10] + A[ 3] * B[14];
        mtx[ 3] = A[ 0] * B[ 3] + A[ 1] * B[ 7] + A[ 2] * B[11] + A[ 3] * B[15];
        mtx[ 4] = A[ 4] * B[ 0] + A[ 5] * B[ 4] + A[ 6] * B[ 8] + A[ 7] * B[12];
        mtx[ 5] = A[ 4] * B[ 1] + A[ 5] * B[ 5] + A[ 6] * B[ 9] + A[ 7] * B[13];
        mtx[ 6] = A[ 4] * B[ 2] + A[ 5] * B[ 6] + A[ 6] * B[10] + A[ 7] * B[14];
        mtx[ 7] = A[ 4] * B[ 3] + A[ 5] * B[ 7] + A[ 6] * B[11] + A[ 7] * B[15];
        mtx[ 8] = A[ 8] * B[ 0] + A[ 9] * B[ 4] + A[10] * B[ 8] + A[11] * B[12];
        mtx[ 9] = A[ 8] * B[ 1] + A[ 9] * B[ 5] + A[10] * B[ 9] + A[11] * B[13];
        mtx[10] = A[ 8] * B[ 2] + A[ 9] * B[ 6] + A[10] * B[10] + A[11] * B[14];
        mtx[11] = A[ 8] * B[ 3] + A[ 9] * B[ 7] + A[10] * B[11] + A[11] * B[15];
        mtx[12] = A[12] * B[ 0] + A[13] * B[ 4] + A[14] * B[ 8] + A[15] * B[12];
        mtx[13] = A[12] * B[ 1] + A[13] * B[ 5] + A[14] * B[ 9] + A[15] * B[13];
        mtx[14] = A[12] * B[ 2] + A[13] * B[ 6] + A[14] * B[10] + A[15] * B[14];
        mtx[15] = A[12] * B[ 3] + A[13] * B[ 7] + A[14] * B[11] + A[15] * B[15];

        delete A;
    }
};

}

#endif // MAT4_H
