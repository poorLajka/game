#include <vector>
#include <set>
#include "vector3.h"
#include "physics.h"
#include "shape.h"
#include "collision.h"

using namespace physics;

namespace collision {

    struct Cdata {

    };

    //Look through each unique pair of objects for object vector, returns a list of collisions
    void check_collisions (const std::vector<PhysicsObject*>& obj_vec, std::vector<PhysObject*>& coll_vec) {
        std::set<std::pair<PhysObj*, PhysObj*>> pairs;
        get_unique_pairs(obj_vec, pairs);
        for (auto pair : pairs) {
            Cdata cdata;
            if (check_collision(pair, cdata))
                coll_vec.push_back(cdata);
        }
    }

    void get_unique_pairs (const std::vector<PhysObj*>& obj_vec, std::set<std::pair<PhysObj*,PhysObj*>>& pairs) {
        for (auto obj_a : obj) {
            for (auto obj_b : obj) {
                std::pair<PhysObj*, PhysObj*> pair;
                pairs.insert(pair);
            }
        }
    }

    bool check_collision (const std::pair<PhysObj*,PhysObj*>& pair, Cdata& cdata) {
        if (broad_check(pair, cdata))
                return narrow_check(pair, cdata);
        return false;
    }

    bool broad_check (std::pair<PhysObj*, PhysObj*>& pair) {
        return true;
    }

    /*
     * Implemented using the GJK algorithm
     */
    bool narrow_check (std::pair<PhysObj*, PhysObj*>& pair) {

        shapes::CollisionShape* shape_a = pair.first->shape;
        shapes::CollisionShape* shape_b = pair.second->shape;

        Vector3 direction = normalize(shape_a->center - shape_b->center);
        std::vector<Vector3> simplex;
        simplex.push_back(shapes::support(shape_a, shape_b, direction));
        direction = normalize(ORIGIN - simplex.p1);

        while (true) {
            Vector3 p2_candidate = shapes::support(shape_a, shape_b, direction);
            if (past_orig(p2_candidate, direction)) {
                return false;
            }
            simplex.push_back(p2_candidate);
            if (handle_simplex(simplex, direction)) {
                return true;
            }
        }
    }

    bool handle_simplex (std::vector<Vector3>& simplex, Vector3& direction) {
        if (simplex.size() == 2) {
            return line_case(simplex, direction);
        }
        return triangle_case(simplex, direction);
    }

    bool line_case (std::vector<Vector3>& simplex, Vector3& direction) {
        Vector3 a, b;
        direction = normalize(perp(a, b));
        return false;
    }

    bool triangle_case (std::vector<Vector3>& simplex, Vector3& direction) {
        Vector3 a, b, c;
        Vector3 ab_perp = perp(a, b);
        Vector3 ac_perp = perp(a, c);

        if (past_orig(ab_perp, ORIGIN - a)) { //Region AB
            //simplex.erase(c);
            direction = normalize(ab_perp);
            return false;
        }
        if (past_orig(ac_perp, ORIGIN - a)) { //Region AC
            //simplex.erase(b);
            direction = normalize(ac_perp);
            return false;
        }
        return true;
    }

    void handle_collisions (PhysicsState* state) {
        return;
    }
}
