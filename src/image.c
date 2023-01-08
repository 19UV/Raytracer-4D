#include "image.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

Image image_create(unsigned int width, unsigned int height) {
	Pixel* data = malloc(width * height * sizeof(Pixel));
	if(data == NULL) {
		fputs("[ERROR] Out of Memory.\n", stderr);
		exit(1); /* If we can't allocate the image, what is the meaning of anything */
	}

	return (Image){
		.width = width,
		.height = height,
		.data = data
	};
}

void image_destroy(Image* image) {
	assert(image != NULL);
	assert(image->data != NULL);

	free(image->data);
#ifndef NDEBUG
	image->data = NULL; /* In case we (I'm) an idiot. */
#endif
}

Pixel* image_at(Image* image, unsigned int x, unsigned int y) {
	assert(image != NULL);
	assert(image->data != NULL);
	assert(x < image->width);
	assert(y < image->height);

	const unsigned int offset = y * image->width + x;

	return &image->data[offset];
}

static inline uint8_t to_uint8(float value) {
	if(value < 0.0f) {
		return 0x00;
	} else if(value > 1.0f) {
		return 0xff;
	} else {
		return (uint8_t)(value * 255.0f);
	}
}

Pixel from_color(Color color) {
	return (Pixel){
		.r = to_uint8(color.r),
		.g = to_uint8(color.g),
		.b = to_uint8(color.b)
	};
}

bool image_write_png(Image* image, const char* path) {
	assert(image != NULL);
	assert(image->data != NULL);

	stbi_flip_vertically_on_write(1);

	return stbi_write_png(
		path,
		image->width, image->height,
		3,
		image->data,
		sizeof(Pixel) * image->width
	) != 0;
}
