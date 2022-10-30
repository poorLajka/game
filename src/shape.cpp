#include "vector3.h"
#include "shape.h"
#include <vector>


class Shape {

};

Vector3 support (CollisionShape* shape_a, CollisionShape* shape_b, const Vector3& direction) {
    return furthest_point(shape_a, direction) - furthest_point(shape_b, direction);
}

Vector3 furthest_point (CollisionShape* s, const Vector3& direction) {
    return Vector3 {0,0,0};
}

