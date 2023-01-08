#pragma once

#include "vector.h"

struct Object;

struct Hit {
	float t;

	Vector4 position;
	Vector4 normal;

	struct Object* object;
};
