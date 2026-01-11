# CMakeList.txt : CMake project for RT1Weekend, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (RT1Weekend "main.cpp" "main.h" "vec3.h" "color.h" "ray.h" "hittable.h" "sphere.h" "hittable_list.h" "rtweekend.h")

message(STATUS "asD ${CMAKE_SOURCE_DIR}")

target_include_directories(RT1Weekend PRIVATE ${CMAKE_SOURCE_DIR}/modules/stb)
target_link_directories(RT1Weekend PRIVATE ${CMAKE_SOURCE_DIR}/modules/stb)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RT1Weekend PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
