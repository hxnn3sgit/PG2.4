#include <png++/png.hpp>
#include <string>
#include <filesystem>
#include <charconv>
#include <exception>
#include <thread>

namespace fs = std::filesystem;

class convert_error : public std::exception {
public:
    virtual const char *what() const noexcept {
        return "int could not be converted, are you sure it is an odd int value?";
    }
};


std::vector<float> calc_blur_values(const png::image<png::rgb_pixel> &my_image, png::uint_32 x, png::uint_32 y, int kernel_size) {
    float sum_blur_value_r = 0.0, sum_blur_value_g = 0.0, sum_blur_value_b = 0.0;
    for (png::uint_32 current_x = x - (kernel_size/2); current_x < x + (kernel_size / 2 + 1); ++current_x) {
        for (png::uint_32 current_y = y - (kernel_size/2); current_y < y + (kernel_size / 2 + 1); ++current_y) {
            png::rgb_pixel my_pixel = my_image.get_pixel(current_x, current_y);
            sum_blur_value_r += my_pixel.red;
            sum_blur_value_g += my_pixel.green;
            sum_blur_value_b += my_pixel.blue;
        }
    }

    sum_blur_value_r /= (kernel_size * kernel_size);
    sum_blur_value_g /= (kernel_size * kernel_size);
    sum_blur_value_b /= (kernel_size * kernel_size);

    std::vector<float> sum_blur_values{ sum_blur_value_r, sum_blur_value_g, sum_blur_value_b };

    return sum_blur_values;
}

/*bool at_border_or_corner(png::uint_32 x, png::uint_32 y, png::uint_32 height, png::uint_32 width) {
    // if x or y or both are zero or max widht/height, return true -> that means youre at a border or corner
    return ( (x == 0 || y == 0) || (x == 0 && y == 0) || (x == height - 1 || y == width - 1) || (x == height - 1 && y == width - 1) );
}*/

png::image< png::rgb_pixel > blur_picture(const std::string &filename, int kernel_size = 3) {
    png::image<png::rgb_pixel> input_image(filename);
    png::image<png::rgb_pixel> output_image(input_image.get_width(), input_image.get_height());

    float blur_value = 0.0;
    for (png::uint_32 y = kernel_size/2; y < input_image.get_height() - (kernel_size/2+1); ++y) {
        for (png::uint_32 x = kernel_size/2;  x < input_image.get_width() - (kernel_size/2 + 1); ++x) {
                std::vector<float> blur_values = calc_blur_values(input_image, x, y, kernel_size);
                int r = blur_values.at(0);
                int g = blur_values.at(1);
                int b = blur_values.at(2);

                r = (r > 255) ? 255 : r;
                g = (g > 255) ? 255 : g;  
                b = (b > 255) ? 255 : b;

                output_image.set_pixel(x, y, png::rgb_pixel(r, g, b));
        }
    }

    return output_image;
}

int parse_int(char* argv_2) {
    int parsed_int;

    auto [ptr, ec] = std::from_chars(argv_2, argv_2 + std::strlen(argv_2), parsed_int);
    if (ec != std::errc()) {
        throw convert_error();
    }

    return parsed_int;
} 

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "[ERROR]: i need args, 1st: filename; 2nd: kernel size\n";
    } else {
        fs::path filename = argv[1];
        if (fs::exists(filename)) {
            try {
                int kernel_size = parse_int(argv[2]);
                if (kernel_size % 2 == 0) {
                    std::cerr << "[ERROR]: Kernel size has to be odd!\n";
                    return EXIT_FAILURE;
                }
                png::image< png::rgb_pixel > blurred_image = blur_picture(filename, kernel_size);
                std::cout << "[LOGGER]: Picture is getting Blurred\n";
                blurred_image.write("blurred_" + filename.string());
                std::cout  << "[LOGGER]: Picture was saved\n";
            } catch (convert_error &e) {
                std::cerr << "[ERROR]: exception occured: " << e.what() << std::endl;
            }
        } else {
            std::cerr << "[ERROR]: no picture with name " << filename << " exists\n";
        }
    }

    return 0;
}