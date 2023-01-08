#include "ray.h"

Vector4 ray_at(struct Ray ray, float t) {
	return (Vector4){
		.x = ray.direction.x * t + ray.origin.x,
		.y = ray.direction.y * t + ray.origin.y,
		.z = ray.direction.z * t + ray.origin.z,
		.w = ray.direction.w * t + ray.origin.w
	};
}
