#pragma once

struct Object;

struct Hit {
	float t;

	struct Object* object;
};
