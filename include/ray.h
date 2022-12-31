#pragma once

#include "vector.h"

/* R(t) = Dt + O */
struct Ray {
	Vector4 origin, direction;
};
