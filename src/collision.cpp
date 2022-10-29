#include <vector>
#include <set>
#include "vector3.h"
#include "physics.h"
#include "shape.h"
#include "collision.h"

using namespace physics;
namespace collision {

    void check_collisions (const std::vector<PhysicsObject*>& objects) {

        std::set<std::pair<PhysicsObject*, PhysicsObject*>> pairs;
        get_unique_pairs(objects, pairs);

        for (auto pair : pairs) {
            if (broad_check(pair) && narrow_check(pair)) {
                CollisionData cdata;
                //get_collision_data(pair, cdata)
                //collisions.push_back(cdata);
            }
        }
    }

    void get_unique_pairs (
        const std::vector<PhysicsObject*>& objects, 
        std::set<std::pair<PhysicsObject*, PhysicsObject*>>& pairs
    ) {
        for (auto obj_a : objects) {
            for (auto obj_b : objects) {
                std::pair<PhysicsObject*, PhysicsObject*> pair;
                pairs.insert(pair);
            }
        }
    }

    bool broad_check (std::pair<PhysicsObject*, PhysicsObject*>& pair) {
        return true;
    }

    /*
     * Implemented using the GJK algorithm
     */
    bool narrow_check (std::pair<PhysicsObject*, PhysicsObject*>& pair) {

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
