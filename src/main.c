#include <stdio.h>
#include <assert.h>

#include "image.h"
#include "vector.h"
#include "ray.h"

#include "object.h"
#include "material.h"

/* Oh no! Global Variables! They will make code more concise, so I will use them. :) */
static const unsigned int image_width = 512;
static const unsigned int image_height = 512;

static inline Color normal_to_color(Vector4 normal) {
	assert(normal.x >= -1.0f);
	assert(normal.x <=  1.0f);

	assert(normal.y >= -1.0f);
	assert(normal.y <=  1.0f);

	assert(normal.z >= -1.0f);
	assert(normal.z <=  1.0f);

	assert(normal.w >= -1.0f);
	assert(normal.w <=  1.0f);

	return (Color){
		.r = normal.x * 0.5f + 0.5f,
		.g = normal.y * 0.5f + 0.5f,
		.b = normal.z * 0.5f + 0.5f
	};
}

int main(int argc, const char* argv[]) {
	Image image = image_create(image_width, image_height);

	struct Material materials[] = {
		{
			.albedo = { 0.0f, 0.0f, 1.0f },
			.roughness = 0.5f
		},
		{
			.albedo = { 1.0f, 0.0f, 0.0f },
			.roughness = 0.5f
		},
		{
			.albedo = { 0.0f, 1.0f, 0.0f },
			.roughness = 0.1f
		}
	};

	struct Object objects[] = {
		{
			.type = OHypersphere,
			.position = { 1.0f, 0.0f, 0.0f, 0.0f },
			.material = 0
		},
		{
			.type = OHypersphere,
			.position = { -1.0f, 0.0f, 0.0f, 0.0f },
			.material = 1
		},
		{
			.type = OHyperplane,
			.position = { 0.0f, -1.0f, 0.0f, 0.0f },
			.material = 2
		}
	};

	struct Object scene = {
		.type = OGroup,
		.position = { 0.0f, 0.0f, 0.0f, 0.0f },
		.data.group = {
			.children = objects,
			.children_count = sizeof(objects) / sizeof(struct Object)
		}
	};

	Vector4 ray_origin = { 0.0f, 0.0f, -2.5f, 0.0f };

	for(unsigned int y = 0; y < image_height; y++) {
		const float v = (float)y / (float)image_height;

		for(unsigned int x = 0; x < image_width; x++) {
			const float u = (float)x / (float)image_width;

			struct Ray ray = {
				.origin = ray_origin,
				/* We don't care if direciton is normalized (length 1), we just can't make assumptions */
				.direction = (Vector4){
					/* We need the range of u and v to be [-1, 1], so we see all of the scene */
					u * 2.0f - 1.0f,
					v * 2.0f - 1.0f,
					1.0f, 0.0f
				}
			};

			struct Hit hit;
			*image_at(&image, x, y) =
				intersect(&scene, ray, &hit)
					? from_color(normal_to_color(hit.normal))
					: (Pixel){ 0, 0, 0 };
		}
	}

	image_write_png(&image, "./output.png");

	return 0;
}
