#include "main.h"
#include "stdint.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>
#include <vector>

#include "color.h"
#include "vec3.h"
#include "ray.h"

using namespace std;

bool hit_sphere(const point3& center, double radius, const ray& r) {
	vec3 oc = center - r.origin();
	auto a = dot(r.direction(), r.direction());
	auto b = -2.0 * dot(r.direction(), oc);
	auto c = dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4 * a * c;
	return (discriminant >= 0);
}

color ray_color(const ray& r) {
	if (hit_sphere(point3(0, 0, -1), 0.5, r))
		return color(1, 0, 0);

	vec3 unit_direction = unit_vector(r.direction());
	auto a = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{
	// Image
	auto aspect_ratio = 16.0 / 9.0;
	int image_width = 400;

	int image_height = int(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	// Camera
	auto focal_length = 1.0f;
	auto viewport_height = 2.0f;
	auto viewport_width = viewport_height * (double(image_width) / image_height);
	auto camera_center = point3(0, 0, 0);

	auto viewport_u = vec3(viewport_width, 0, 0);
	auto viewport_v = vec3(0, -viewport_height, 0);

	auto pixel_delta_u = viewport_u / image_width;
	auto pixel_delta_v = viewport_v / image_height;

	auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) 
		- viewport_u / 2.0 - viewport_v / 2.0;
	auto pix_00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

	// Render
	int data_length = image_width * image_height * N_CHANNELS;
	uint8_t* data = new uint8_t[data_length];

	try
	{
		int index = 0;

		for (int j = 0; j < image_height; j++)
		{
			clog << "\rScanlines remaining: " << (image_height - j) << ' ' << flush;
			for (int i = 0; i < image_width; i++)
			{
				auto pixel_center = pix_00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
				auto ray_direction = pixel_center - camera_center;
				ray r(camera_center, ray_direction);

				//auto pixel_color = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0);
				auto pixel_color = ray_color(r);

				write_color(data, data_length, pixel_color, index);
				index += N_CHANNELS;
			}
		}
	}
	catch (const std::exception& e)
	{
		cout << "Exception - " << e.what() << "\n";
	}

	stbi_write_jpg("trace_output.jpg", image_width, image_height, N_CHANNELS, data, 100);
	clog << "\rDone.                 \n";

	delete[] data;
	return 0;
}
