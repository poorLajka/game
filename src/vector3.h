#ifndef VECTOR3_H 
#define VECTOR3_H 

/*
 * A simple 3-dimensional vector with basic vector math implemented 
 * using operator overloading.
 */

struct Vector3 {
    float x, y, z;

    Vector3& operator += (const Vector3& right); 

    Vector3& operator -= (const Vector3& right); 
};

const Vector3 ORIGIN { .x = 0,.y = 0,.z = 0 };

Vector3 operator + (const Vector3& a, const Vector3& b); 

Vector3 operator - (const Vector3& a, const Vector3& b); 

Vector3 operator * (const Vector3& vec, float scalar); 

Vector3 operator * (float scalar, const Vector3& vec); 

float dot (const Vector3& a, const Vector3& b); 

Vector3 cross (const Vector3& a, const Vector3& b); 

Vector3 cross_tripple (const Vector3& a, const Vector3& b, const Vector3& c); 

float quake_rsqrt(float number ); 

Vector3 normalize (const Vector3& vec); 

Vector3 perp (const Vector3& a, const Vector3& b); 

bool past_orig (const Vector3& point, const Vector3& direction); 

#endif


