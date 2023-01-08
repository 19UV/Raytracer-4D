#include "object.h"

#include <float.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

#include "ray.h"
#include "hit.h"
#include "vector.h"

bool group_intersect(struct Object* object, struct Ray ray, struct Hit* hit) {
	assert(object->type == OGroup);

	if(hit != NULL) {
		hit->t = FLT_MAX;
	}

	bool hits = false;
	for(unsigned int i = 0; i < object->data.group.children_count; i++) {
		struct Hit child_hit;

		if(intersect(&object->data.group.children[i], ray, &child_hit)) {
			hits = true;

			if(hit == NULL) {
				break;
			}

			if(child_hit.t < hit->t) {
				*hit = child_hit;
			}
		}
	}

	return hits;
}