#ifndef COLOR_H
#define COLOR_H

#define N_CHANNELS 3

#include "vec3.h"
#include <stdint.h>

using color = vec3;
using namespace std;

void write_color(uint8_t* data, int data_length, const color& pixel_color, int start_index) {
	if (start_index + 2 >= data_length) {
		throw new exception("Something wrong Color Write");
	}
	
	int ir = int(255.999 * pixel_color.x());
	int ig = int(255.999 * pixel_color.y());
	int ib = int(255.999 * pixel_color.z());

	data[start_index] = ir;
	data[start_index + 1] = ig;
	data[start_index + 2] = ib;
	return;
}


#endif // !COLOR_H
