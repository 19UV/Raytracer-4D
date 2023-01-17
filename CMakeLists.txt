cmake_minimum_required(VERSION 3.10)
project(Raytracer4D
	VERSION 0.1
	LANGUAGES C
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(FILES ${FILES}
	src/image.c

	src/vector.c
	src/ray.c

	src/object.c
	src/objects/group.c
	src/objects/hypersphere.c
	src/objects/hyperplane.c

	src/light.c

	src/main.c
)

add_executable(raytracer4d ${FILES})
target_include_directories(raytracer4d PRIVATE include/ extern/)

if(NOT MSVC)
	target_link_libraries(raytracer4d PRIVATE m)
endif()