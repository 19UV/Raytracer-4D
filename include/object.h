#pragma once

#include <stdbool.h>

#include "vector.h"
#include "ray.h"
#include "hit.h"

enum ObjectType {
	OHypersphere,
	OHyperplane
};

struct Object {
	enum ObjectType type;

	Vector4 position;
};

bool intersect(struct Object* object, struct Ray ray, struct Hit* hit);
