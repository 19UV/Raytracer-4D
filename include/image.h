#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "material.h"

typedef struct Pixel {
	uint8_t r, g, b;
} Pixel;

typedef struct Image {
	unsigned int width, height;

	Pixel* data;
} Image;

Image image_create(unsigned int width, unsigned int height);
void image_destroy(Image* image);

Pixel* image_at(Image* image, unsigned int x, unsigned int y);

Pixel from_color(Color color);

bool image_write_png(Image* image, const char* path);
