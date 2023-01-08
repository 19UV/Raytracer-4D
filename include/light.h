#pragma once

#include "vector.h"
#include "material.h"
#include "hit.h"

enum LightType {
	LAmbient,
	LDirectional,
	LPoint
};

struct Light {
	enum LightType type;

	Color color;

	union {
		struct {
			float intensity;
		} ambient;
		struct {
			Vector4 direction;
		} directional;
		struct {
			Vector4 position;
		} point;
	} data;
};

Color light_color(const struct Light* light, struct Hit hit);