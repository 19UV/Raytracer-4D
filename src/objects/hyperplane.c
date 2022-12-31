#include "object.h"

#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

#include "ray.h"
#include "hit.h"
#include "vector.h"

/** [THE RAY-HYPERPLANE INTERSECTION ALGORITHM EXPLAINED]
 * A hyperplane can be defined as the set of points that have a restricted axis.
 * For example, a floor plane, is defined by all the points where y = 0.
 * In addition, we could define a 'plane' as a graph, where the y value is an equation based off of x, z, and w.
 * For the sake of simplicity however, we will just find the intersection with a plane at y = 0.
 *
 * For notation purposes, I will define the operation V[y] to get the y-value of the vector V.
 *
 * Because we are limiting the position of the points to y = 0, we will want to find t such that R(t)[y] = 0.
 *
 * R(t)[y] = 0
 *
 * By substituting, we get...
 *
 * (Dt + O)[y] = 0
 *
 * Because vector-scalar multiplication and vector addition deals with axes independantly, we can distribute.
 *
 * D[y] * t + O[y] = 0
 *
 * And solve for t.
 *
 * t = -O[y] / D[y]
*/

bool hyperplane_intersect(struct Object* object, struct Ray ray, struct Hit* hit) {
	assert(object->type == OHyperplane);

	/* Check for divide by zero, which is a valid input (looking parallel to the plane). */
	if(ray.direction.y == 0.0f) {
		return false;
	}

	const float t = -ray.origin.y / ray.direction.y;
	if(t <= 0.0f) {
		return false;
	}

	if(hit != NULL) {
		hit->t = t;
		hit->object = object;
	}

	return true;
}
