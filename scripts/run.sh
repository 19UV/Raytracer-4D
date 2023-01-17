#!/bin/sh

if [ ! -d "build/" ]; then
	cmake -B build
fi

cmake --build build && ./build/raytracer4d