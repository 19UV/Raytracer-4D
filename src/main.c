#include <stdio.h>
#include <assert.h>

#include "image.h"
#include "vector.h"
#include "ray.h"

#include "object.h"
#include "material.h"
#include "light.h"

#define ARR_LEN( arr) (sizeof( arr) / sizeof( arr[0]))

/* Oh no! Global Variables! They will make code more concise, so I will use them. :) */
static const unsigned int image_width = 512;
static const unsigned int image_height = 512;

int main(int argc, const char* argv[]) {
	Image image = image_create(image_width, image_height);

	struct Material materials[] = {
		{
			.albedo = { 0.25, 1.0f, 0.25 },
			.roughness = 0.5f
		}
	};

	struct Light lights[] = {
		{
			.type = LAmbient,
			.color = { 1.0f, 0.5f, 0.5f },
			.data.ambient.intensity = 0.2f
		},
		{
			.type = LDirectional,
			.color = { 0.5f, 1.0f, 0.5f },
			.data.directional.direction = vector_normalize((Vector4){ 1.0f, 1.0f, -1.0f, 0.0f })
		},
		{
			.type = LPoint,
			.color = { 0.5f, 0.5f, 1.0f },
			.data.point.position = { -5.0f, 5.0f, -5.0f, 2.5f }
		}
	};

	struct Object objects[] = {
		{
			.type = OHypersphere,
			.position = { 0.0f, 0.0f, 0.0f, 0.0f },
			.material = 0
		}
	};

	struct Object scene = {
		.type = OGroup,
		.position = { 0.0f, 0.0f, 0.0f, 0.0f },
		.data.group = {
			.children = objects,
			.children_count = ARR_LEN(objects)
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

			Color color = { 0.0f, 0.0f, 0.0f };

			struct Hit hit;
			if(intersect(&scene, ray, &hit)) {
				struct Object* object = hit.object;
				struct Material* material = &materials[object->material];

				for(unsigned int light = 0; light < ARR_LEN(lights); light++) {
					Color _color = light_color(&lights[light], hit);

					color.r += _color.r;
					color.g += _color.g;
					color.b += _color.b;
				}
				color.r *= material->albedo.r;
				color.g *= material->albedo.g;
				color.b *= material->albedo.b;
			}

			*image_at(&image, x, y) = from_color(color);
		}
	}

	image_write_png(&image, "./output.png");

	return 0;
}
