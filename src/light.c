#include "light.h"

#include <stddef.h>
#include <assert.h>

#include "vector.h"
#include "material.h"
#include "hit.h"

static inline float max(float a, float b) {
	return a > b ? a : b;
}

/* TODO: Document this */
Color light_color(const struct Light* light, struct Hit hit) {
	assert(light != NULL);

	float intensity = 0.0f;

	switch(light->type) {
		case LAmbient:
			intensity = light->data.ambient.intensity;
			break;
		case LDirectional:
			intensity = max(vector_dot(hit.normal, light->data.directional.direction), 0.0f);
			break;
		case LPoint:
			const Vector4 direction = vector_normalize((Vector4){
				.x = light->data.point.position.x - hit.position.x,
				.y = light->data.point.position.y - hit.position.y,
				.z = light->data.point.position.z - hit.position.z,
				.w = light->data.point.position.w - hit.position.w
			});

			intensity = max(vector_dot(hit.normal, direction), 0.0f);
			break;
	}

	return (Color){
		.r = light->color.r * intensity,
		.g = light->color.g * intensity,
		.b = light->color.b * intensity
	};
}