#include "vector3.h"

/*
 * A simple 3-dimensional vector with basic vector math implemented 
 * using operator overloading.
 */
Vector3& Vector3::operator += (const Vector3& right) {
    this->x += right.x;
    this->y += right.y;
    this->z += right.z;
    return *this;
}

Vector3& Vector3::operator -= (const Vector3& right) {
    this->x -= right.x;
    this->y -= right.y;
    this->z -= right.z;
    return *this;
}


Vector3 operator + (const Vector3& a, const Vector3& b) {
    return Vector3 {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    };
}

Vector3 operator - (const Vector3& a, const Vector3& b) {
    return Vector3 {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    };
}

Vector3 operator * (const Vector3& vec, float scalar) {
    return Vector3 {
        vec.x * scalar,
        vec.y * scalar,
        vec.z * scalar
    };
}

Vector3 operator * (float scalar, const Vector3& vec) {
    return Vector3 {
        vec.x * scalar,
        vec.y * scalar,
        vec.z * scalar
    };
}

float dot (const Vector3& a, const Vector3& b) {
    return 
        a.x * b.x
        + a.y * b.y
        + a.z * b.z;
}

Vector3 cross (const Vector3& a, const Vector3& b) {
    return Vector3 { 
        .x = a.y * b.z - a.z * b.y,
        .y =  a.z * b.x - a.x * b.z,
        .z = a.x * b.y - a.y * b.x 
    };
}

Vector3 cross_tripple (const Vector3& a, const Vector3& b, const Vector3& c) {
    return cross(cross(a, b), c);
}

float quake_rsqrt(float number ) {
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck? 
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

Vector3 normalize (const Vector3& vec) {
    return vec * quake_rsqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}

Vector3 perp (const Vector3& a, const Vector3& b) {
    return cross_tripple(b-a, ORIGIN-a, b-a);
}

bool past_orig (const Vector3& point, const Vector3& direction) {
    return dot(point, direction) < 0;
}

