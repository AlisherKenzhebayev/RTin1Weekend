#include "main.h"
#include "stdint.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>
#include <vector>

#include "vec3.h"
#include "color.h"

using namespace std;

int main()
{
	const int image_width = 256;
	const int image_height = 256;

	// Render

	cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

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
				auto pixel_color = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0);

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
