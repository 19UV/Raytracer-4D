#pragma once

#include <stdbool.h>

#include "vector.h"
#include "ray.h"
#include "hit.h"

#include "material.h"

enum ObjectType {
	OGroup,
	OHypersphere,
	OHyperplane
};

struct Object {
	enum ObjectType type;

	Vector4 position;

	MaterialIndex material;

	union {
		struct {
			struct Object* children;
			unsigned int children_count;
		} group;
	} data;
};

bool intersect(struct Object* object, struct Ray ray, struct Hit* hit);
