#include "random.h"

#include <stdlib.h>
#include <time.h>

void random_seed(void) {
	srand(time(NULL));
}

/* Returns a random float in [0, 1] */
float random_float_unit(void) {
	return (float)rand() / (float)RAND_MAX;
}

/* Returns a random float in [min, max] */
float random_float_range(float min, float max) {
	return random_float_unit() * (max - min) + min;
}