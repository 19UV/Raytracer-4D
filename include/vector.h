#pragma once

/* For now we'll just use floats, in the future we may want to use doubles (based on the machine) */
typedef struct Vector4 {
	float x, y, z, w;
} Vector4;

/* TODO: Run a benchmark to see if its faster to pass by pointers, or by value */

float vector_dot(Vector4 a, Vector4 b);

float vector_length(Vector4 vector);
Vector4 vector_normalize(Vector4 vector);