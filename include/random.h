#pragma once

void random_seed(void);

/* Returns a random float in [0, 1] */
float random_float_unit(void);

/* Returns a random float in [min, max] */
float random_float_range(float min, float max);