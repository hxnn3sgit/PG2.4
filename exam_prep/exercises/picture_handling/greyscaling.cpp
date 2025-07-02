#include <png++/png.hpp>

int main() {
	png::image< png::rgb_pixel > image("pic.png");
	for (png::uint_32 y = 0; y < image.get_height(); ++y) {
		for (png::uint_32 x = 0;  x < image.get_width(); ++x) {
			float rgb_sum = 0.0;
			png::rgb_pixel pixel = image.get_pixel(x, y);
			rgb_sum = pixel.blue + pixel.green + pixel.red;
			float greyscale_value = rgb_sum / 3;
			image.set_pixel(x, y, png::rgb_pixel(greyscale_value, greyscale_value, greyscale_value));	
		}
	}

	image.write("greyscaled_pic.png");

	return 0;
}
