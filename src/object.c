#include "object.h"

#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

#include "ray.h"
#include "hit.h"

bool hypersphere_intersect(struct Object*, struct Ray, struct Hit*);

/* NOTE: object MUST NOT be NULL, but hit MAY be NULL */
bool intersect(struct Object* object, struct Ray ray, struct Hit* hit) {
	assert(object != NULL);

	switch(object->type) {
		case OHypersphere:
			return hypersphere_intersect(object, ray, hit);
	}

	return false;
}
