#ifndef SHAPE_H
#define SHAPE_H

#include "vector3.h"
#include <vector>

namespace shapes {
    struct CollisionShape {
        Vector3 center;
    };

    struct Sphere : CollisionShape {
        float radius;
    };

    Vector3 support (CollisionShape* shape_a, CollisionShape* shape_b, const Vector3& direction); 

    Vector3 furthest_point (CollisionShape* s, const Vector3& direction); 
}

#endif //SHAPE_H

