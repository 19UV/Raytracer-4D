#include "object.h"

#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

#include "ray.h"
#include "hit.h"

bool group_intersect(struct Object*, struct Ray, struct Hit*);
bool hypersphere_intersect(struct Object*, struct Ray, struct Hit*);
bool hyperplane_intersect(struct Object*, struct Ray, struct Hit*);

/* NOTE: object MUST NOT be NULL, but hit MAY be NULL */
bool intersect(struct Object* object, struct Ray ray, struct Hit* hit) {
	assert(object != NULL);

	/* We can make it seem like we're transforming the object by transforming the ray */
	ray.origin.x -= object->position.x;
	ray.origin.y -= object->position.y;
	ray.origin.z -= object->position.z;
	ray.origin.w -= object->position.w;

	switch(object->type) {
		case OGroup:
			return group_intersect(object, ray, hit);
		case OHypersphere:
			return hypersphere_intersect(object, ray, hit);
		case OHyperplane:
			return hyperplane_intersect(object, ray, hit);
	}

	return false;
}
