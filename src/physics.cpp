#include <iostream>
#include <vector>
#include "vector3.h"
#include "shape.h"

namespace physics {

/*
 * A PhysicsObject is an abstract entity used to track position over time.
 * To use, simply let whatever you want to apply physics to store a PhysicsObject*.
 * Set it's mass, volume, and add it to a PhysicsState. 
 * You can then apply forces to it while having it interract with all 
 * other objects in that state.
 */
    struct PhysObj {
        Vector3 force, vel, pos;
        CollisionShape* shape;
        float inverse_mass;
    };

    void set_mass (PhysObj* obj, float mass) {
        obj->inverse_mass = 1/mass;
    }

    void apply_force (PhysObj* obj, const Vector3& force) {
        obj->force+= force;
    }

    void clear_forces(PhysObj* obj) {
        Vector3 null_vec{ .x = 0, .y = 0, .z = 0 };
        object->force = null_vec;
    }

/*
 * A PhysicsState is a collection of PhysicsObjects along with some additional 
 * information about the state.
 * You can set gravity and damping by calling respective functions.
 * To use, simply call update_state with a timeframe dt to move the system forwards.
 */

    struct PhysState {
        Vector3 grav;
        std::vector<PhysObj*> obj_vec;
        float damping;
    };

    void linear_damp (PhysState* state, PhysObj* obj) {
        obj->vel = object->vel * state->damping;
    }

    void set_grav (PhysState* state) {
        state->grav = Vector3 { .x = 0, .y = -9.82, .z = 0 };
    }

    void add_obj (PhysState* state, PhysObj* obj) {
        state->obj_vec.push_back(obj);
    }

    void update_state (PhysState* state, float dt) {
        std::vector<collision::Cdata> coll_vec;
        collision::check_collisions(state->obj_vec, coll_vec);
        for (auto coll : coll_vec) {
            resolve_coll(coll);
        }

        for (auto obj : state->obj) {
            update_obj(state, obj, dt);
        }
    }

    void resolve_coll (collision::Cdata&) {

    }

    void update_obj (PhysState* state, PhysObj* obj, float dt) {
        //Simple numerical integration using Eulers method
        Vector3 acc = obj->force * obj->inverse_mass;
        acc += state->grav;
        obj->vel += acc * dt;
        obj->pos += obj->vel * dt;

        linear_damp(state, obj);
        clear_object_forces(obj);
    }

}

