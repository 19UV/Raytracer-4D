#include <stdio.h>
#include <assert.h>

#include "random.h"

#include "image.h"
#include "vector.h"
#include "ray.h"

#include "object.h"
#include "material.h"
#include "light.h"

#define ARR_LEN( arr) (sizeof( arr) / sizeof( arr[0]))

struct Scene {
	struct Object root;
	struct Material* materials;

	unsigned int light_count;
	struct Light* lights;
};

/* Oh no! Global Variables! They will make code more concise, so I will use them. :) */
static const unsigned int image_width = 960;
static const unsigned int image_height = 540;

static const unsigned int sample_count = 10;
static const unsigned int ray_depth = 10;

static inline Color hit_color(struct Hit hit, struct Scene* scene) {
	Color color = { 0.0f, 0.0f, 0.0f };
	
	struct Object* object = hit.object;
	struct Material* material = &scene->materials[object->material];

	for(unsigned int light = 0; light < scene->light_count; light++) {
		Color _light_color = light_color(&scene->lights[light], hit);

		color.r += _light_color.r;
		color.g += _light_color.g;
		color.b += _light_color.b;
	}

	color.r *= material->albedo.r;
	color.g *= material->albedo.g;
	color.b *= material->albedo.b;

	return color;
}

static inline Color ray_color(struct Ray ray, struct Scene* scene) {
	struct Hit hit;

	Color color = { 0.0f, 0.0f, 0.0f };
	float weight = 1.0f;

	for(unsigned int i = 0; i < ray_depth; i++) {
		if(!intersect(&scene->root, ray, &hit)) {
			break;
		}

		Color _hit_color = hit_color(hit, scene);
		color.r += _hit_color.r * weight;
		color.g += _hit_color.g * weight;
		color.b += _hit_color.b * weight;
		weight *= 0.5f;

#define SMALL_VALUE 0.0001f
		ray.origin.x = hit.position.x + hit.normal.x * SMALL_VALUE;
		ray.origin.y = hit.position.y + hit.normal.y * SMALL_VALUE;
		ray.origin.z = hit.position.z + hit.normal.z * SMALL_VALUE;
		ray.origin.w = hit.position.w + hit.normal.w * SMALL_VALUE;
#undef SMALL_VALUE

		float roughness = scene->materials[hit.object->material].roughness;
		ray.direction = vector_reflect(ray.direction, (Vector4){
			.x = hit.normal.x + roughness * random_float_range(-1.0f, 1.0f),
			.y = hit.normal.y + roughness * random_float_range(-1.0f, 1.0f),
			.z = hit.normal.z + roughness * random_float_range(-1.0f, 1.0f),
			.w = hit.normal.w + roughness * random_float_range(-1.0f, 1.0f)
		});
	}
	
	return color;
}

int main(int argc, const char* argv[]) {
	random_seed();
	
	Image image = image_create(image_width, image_height);

	struct Material materials[] = {
		{
			.albedo = { 0.25f, 1.0f, 0.25f },
			.roughness = 0.5f
		},
		{
			.albedo = { 0.25f, 0.25f, 1.0f },
			.roughness = 0.1f
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
		},
		{
			.type = OHyperplane,
			.position = { 0.0f, -1.0f, 0.0f, 0.0f },
			.material = 1
		}
	};

	struct Scene scene = {
		.root = {
			.type = OGroup,
			.position = { 0.0f, 0.0f, 0.0f, 0.0f },
			.data.group = {
				.children = objects,
				.children_count = ARR_LEN(objects)
			}
		},
	
		.materials = materials,

		.light_count = ARR_LEN(lights),
		.lights = lights
	};

	Vector4 ray_origin = { 0.0f, 0.0f, -2.5f, 0.0f };

	const float aspect_ratio = (float)image_width / (float)image_height;
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
			ray.direction.x *= aspect_ratio;

			Color pixel_color = { 0.0f, 0.0f, 0.0f };
			for(unsigned int i = 0; i < sample_count; i++) {
				Color _pixel_color = ray_color(ray, &scene);

				pixel_color.r += _pixel_color.r;
				pixel_color.g += _pixel_color.g;
				pixel_color.b += _pixel_color.b;
			}

			pixel_color.r /= (float)sample_count;
			pixel_color.g /= (float)sample_count;
			pixel_color.b /= (float)sample_count;
			
			*image_at(&image, x, y) = from_color(pixel_color);
		}
	}

	image_write_png(&image, "./output.png");

	return 0;
}
