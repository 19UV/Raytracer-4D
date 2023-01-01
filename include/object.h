#pragma once

#include <stdbool.h>

#include "vector.h"
#include "ray.h"
#include "hit.h"

#include "material.h"

enum ObjectType {
	OHypersphere,
	OHyperplane
};

struct Object {
	enum ObjectType type;

	Vector4 position;

	MaterialIndex material;
};

bool intersect(struct Object* object, struct Ray ray, struct Hit* hit);
