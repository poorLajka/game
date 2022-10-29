#include <iostream>
#include <vector>
#include "vector3.h"
#include "shape.h"

//Implementation somewhat more oldschool aka not super OOP

namespace physics {


/*
 * A PhysicsObject is an abstract entity used to track position over time.
 * To use, simply let whatever you want to apply physics to store a PhysicsObject*.
 * Set it's mass, volume, and add it to a PhysicsState. 
 * You can then apply forces to it while having it interract with all 
 * other objects in that state.
 */
    struct PhysicsObject {
        Vector3 force, vel, pos;
        Transform* transform;
        CollisionShape* shape;
        float inverse_mass;
    };

    void set_object_mass (PhysicsObject* object, float mass) {
        object->inverse_mass = 1/mass;
    }

    void apply_object_force (PhysicsObject* object, const Vector3& applied_force) {
        object->force += applied_force;
    }

    void clear_object_forces (PhysicsObject* object) {
        Vector3 null_vec{ .x = 0, .y = 0, .z = 0 };
        object->force = null_vec;
    }

/*
 * A PhysicsState is a collection of PhysicsObjects along with some additional 
 * information about the system.
 * You can set gravity and damping by calling respective functions.
 * To use, simply call update_state with a timeframe dt to move the system forwards.
 */

    struct PhysicsState {
        Vector3 grav;
        std::vector<PhysicsObject*> objects;
        float damping_amount;
    };

    void linear_damp (PhysicsState* state, PhysicsObject* object) {
        object->vel = object->vel * state->damping_amount;
    }

    void set_state_grav (PhysicsState* state) {
        state->grav = Vector3 { .x = 0, .y = -9.82, .z = 0 };
    }

    void add_state_object (PhysicsState* state, PhysicsObject* object) {
        state->objects.push_back(object);
    }

    void update_state (PhysicsState* state, float dt) {
        collision::check_collisions(state);

        for (auto object : state->objects) {
            update_object(state, object, dt);
        }
    }

    void update_object (PhysicsState* state, PhysicsObject* obj, float dt) {
        //Simple numerical integration using Eulers method
        Vector3 accel = obj->force * obj->inverse_mass;
        accel += state->grav;
        obj->vel += accel * dt;
        obj->pos += obj->vel * dt;

        linear_damp(state, obj);
        clear_object_forces(obj);
    }

}

