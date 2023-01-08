#include "vector.h"

#include <math.h>

float vector_dot(Vector4 a, Vector4 b) {
	return (
		a.x * b.x +
		a.y * b.y +
		a.z * b.z +
		a.w * b.w
	);
}

float vector_length(Vector4 vector) {
	return sqrtf(
		vector.x * vector.x +
		vector.y * vector.y +
		vector.z * vector.z +
		vector.w * vector.w
	);
}

Vector4 vector_normalize(Vector4 vector) {
	const float length = vector_length(vector);

	return (Vector4){
		.x = vector.x / length,
		.y = vector.y / length,
		.z = vector.z / length,
		.w = vector.w / length
	};
}