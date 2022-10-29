#ifndef COLLISION_H
#define COLLISION_H

#include <vector>
#include <set>
#include "vector3.h"
#include "physics.h"
#include "shape.cpp"

using namespace physics;
namespace collision {

    struct CollisionData {
        float penetration;
        Vector3 normal, point_on_plane;
    };

    void check_collisions (const std::vector<PhysicsObject*>& objects);

    void get_unique_pairs (
        const std::vector<PhysicsObject*>& objects, 
        std::set<std::pair<PhysicsObject*, PhysicsObject*>>& pairs
    ); 

    bool broad_check (std::pair<PhysicsObject*, PhysicsObject*>& pair); 

    bool narrow_check (std::pair<PhysicsObject*, PhysicsObject*>& pair); 

    bool handle_simplex (std::vector<Vector3>& simplex, const Vector3& direction); 

    bool line_case (std::vector<Vector3>& simplex, Vector3& direction); 

    bool triangle_case (std::vector<Vector3>& simplex, Vector3& direction); 

    void handle_collisions (PhysicsState* state); 
}

#endif // COLLISION_H
