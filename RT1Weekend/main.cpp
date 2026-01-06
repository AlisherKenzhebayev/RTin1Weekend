#include "main.h"
#include "stdint.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>

#define N_CHANNELS 3

using namespace std;

int main()
{
	const int image_width = 256;
	const int image_height = 256;

	// Render

	cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	uint8_t data[image_width * image_height * N_CHANNELS];

	int index = 0;
	for (int j = 0; j < image_height; j++)
	{
		clog << "\rScanlines remaining: " << (image_height - j) << ' ' << flush;
		for (int i = 0; i < image_width; i++)
		{
			auto r = double(i) / (image_width - 1);
			auto g = double(j) / (image_height - 1);
			auto b = 0.0;

			int ir = int(255.999 * r);
			int ig = int(255.999 * g);
			int ib = int(255.999 * b);

			data[index]		= ir;
			data[index + 1]	= ig;
			data[index + 2]	= ib;
			index += N_CHANNELS;
		}
	}

	stbi_write_jpg("output/image_out.jpg", image_width, image_height, N_CHANNELS, data, 100);
	std::clog << "\rDone.                 \n";
	return 0;
}
