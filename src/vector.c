#include "vector.h"

float vector_dot(Vector4 a, Vector4 b) {
	return (
		a.x * b.x +
		a.y * b.y +
		a.z * b.z +
		a.w * b.w
	);
}
