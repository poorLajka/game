
#include <iostream>
#include "physics.h"
#include "vector2.h"

int main () {

    physics::PhysicsState* p_state = new physics::PhysicsState();
    physics::set_state_grav(p_state);

    physics::PhysicsObject* p_object = new physics::PhysicsObject();
    p_object->mass = 10;

    physics::add_object(p_state, p_object);

    physics::update_state(p_state, 1);
    std::cout << object->pos.y << std::endl;


    delete object;
    delete world;

    return 0;

}
