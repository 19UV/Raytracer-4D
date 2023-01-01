#pragma once

#include <stddef.h>

typedef struct Color {
	float r, g, b;
} Color;

struct Material {
	Color albedo;
	float roughness;
};

typedef size_t MaterialIndex;
