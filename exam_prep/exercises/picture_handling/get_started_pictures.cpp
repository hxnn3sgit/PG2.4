#include <png++/png.hpp>

int main() {
	png::image< png::rgb_pixel > image("rgb.png");

	for (png::uint_32 y = 0; y < image.get_height(); ++y) {
		for (png::uint_32 x = 0; x < image.get_width(); ++x) {
			png::rgb_pixel pixel = image.get_pixel(x, y);
			pixel.blue = 0;
			image.set_pixel(
				x, y, pixel
			);
		}
	}

	image.write("new_rgb.png");

	return 0;
}
