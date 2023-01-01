#include <stdio.h>

#include "image.h"
#include "vector.h"
#include "ray.h"

#include "object.h"
#include "material.h"

/* Oh no! Global Variables! They will make code more concise, so I will use them. :) */
static const unsigned int image_width = 512;
static const unsigned int image_height = 512;

int main(int argc, const char* argv[]) {
	Image image = image_create(image_width, image_height);

	struct Material materials[] = {
		{
			.albedo = { 0.0f, 1.0f, 0.0f },
			.roughness = 0.5f
		}
	};

	struct Object hypersphere = {
		.type = OHypersphere,
		.position = { 0.0f, 1.0f, 0.0f, 0.0f },
		.material = 0
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
				intersect(&hypersphere, ray, &hit)
					? from_color(materials[hit.object->material].albedo)
					: (Pixel){ 0, 0, 0 };
		}
	}

	image_write_png(&image, "./output.png");

	return 0;
}
