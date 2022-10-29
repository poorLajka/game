#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
#include "vector3.h"
#include "shape.h"

namespace physics {

    struct Transform {
        float blank;
    };

    struct PhysicsObject {
        Vector3 force, vel, pos;
        Transform* transform;
        shapes::CollisionShape* shape;
        float inverse_mass;
    };

    struct PhysicsState {
        Vector3 grav;
        std::vector<PhysicsObject*> objects;
    };

    void update_state (PhysicsState* state, float dt);

    void add_object (PhysicsState* state, PhysicsObject* object);

    namespace {
        void update_object (PhysicsObject* obj, float dt, Vector3 grav);
    }
}

#endif // PHYSICS_H
