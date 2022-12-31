cmake_minimum_required(VERSION 3.10)
project(Raytracer4D
	VERSION 0.1
	LANGUAGES C
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(FILES ${FILES}
	src/vector.c
	src/image.c

	src/object.c
	src/objects/hypersphere.c
	src/objects/hyperplane.c

	src/main.c
)

add_executable(raytracer4d ${FILES})
target_include_directories(raytracer4d PRIVATE include/ extern/)
