#pragma once

#include "vector.h"

/* R(t) = Dt + O */
struct Ray {
	Vector4 origin, direction;
};

Vector4 ray_at(struct Ray ray, float t);