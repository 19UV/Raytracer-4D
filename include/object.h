#pragma once

#include <stdbool.h>

#include "ray.h"
#include "hit.h"

enum ObjectType {
	OHypersphere
};

struct Object {
	enum ObjectType type;
};

bool intersect(struct Object* object, struct Ray ray, struct Hit* hit);
