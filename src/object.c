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

	bool hits = false;
	switch(object->type) {
		case OGroup:
			hits = group_intersect(object, ray, hit);
			break;
		case OHypersphere:
			hits = hypersphere_intersect(object, ray, hit);
			break;
		case OHyperplane:
			hits = hyperplane_intersect(object, ray, hit);
			break;
	}

	if(hit != NULL) {
		hit->position.x += object->position.x;
		hit->position.y += object->position.y;
		hit->position.z += object->position.z;
		hit->position.w += object->position.w;
	}

	return hits;
}
