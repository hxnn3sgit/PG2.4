#include <png++/png.hpp>
#include <string>
#include <filesystem>
#include <charconv>
#include <exception>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <iostream>

// #include "../../../my_own_librarys/dyn_arr/dyn_arr.h"

namespace fs = std::filesystem;

class convert_error : public std::exception {
public:
    virtual const char *what() const noexcept {
        return "int could not be converted, are you sure it is an odd int value?";
    }
};

struct ThreadData {
    int NumberOfThreads;
    // what else? never seen this concept

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

void process_image_section(const png::image<png::rgb_pixel> &input_image, png::image<png::rgb_pixel> &output_image, const int kernel_size, png::uint_32 y_start, png::uint_32 y_end) {
    png::uint_32 i_height = input_image.get_height();
    png::uint_32 i_width = input_image.get_width();

    float blur_value = 0.0;

    for (png::uint_32 y = y_start; y < y_end; ++y) {
        for (png::uint_32 x = kernel_size / 2; x < i_width - (kernel_size / 2 + 1); ++x) {
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
}

png::image<png::rgb_pixel> blur_picture_parallel(const fs::path &filename, const int kernel_size = 3, const int number_of_threads = 2) {
    png::image<png::rgb_pixel> input_image(filename);
    png::uint_32 i_height = input_image.get_height();
    png::uint_32 i_width = input_image.get_width();
    
    std::vector<std::thread> threads;
    png::image<png::rgb_pixel> output_image(i_width, i_height);

    /*
        - create a copy of the input picture: this is the picture where blur pixels are written
        - pass it in process_image_section to safe the blur pixels
    */

    png::uint_32 valid_start = kernel_size / 2;
    png::uint_32 valid_end = i_height - ((kernel_size / 2) + 1);
    png::uint_32 middle = (valid_start + valid_end) / 2;

    threads.push_back(std::thread(process_image_section, std::ref(input_image), std::ref(output_image), kernel_size, valid_start, middle));
    threads.push_back(std::thread(process_image_section, std::ref(input_image), std::ref(output_image), kernel_size, middle, valid_end));

    for (auto &thread : threads) 
        thread.join(); // waits, until every thread is done doing their work

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


void measure_performance (/* some chrono time parameters */);


int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "[ERROR]: i need args, 1st: filename; 2nd: kernel size\n"; // later 3rd, thread number
		return EXIT_FAILURE;
    } else {
        fs::path filename = argv[1];
        if (fs::exists(filename)) {
            try {
                int kernel_size = parse_int(argv[2]);
                if (kernel_size % 2 == 0) {
                    std::cerr << "[ERROR]: Kernel size has to be odd!\n";
                    return EXIT_FAILURE;
                }
                png::image< png::rgb_pixel > blurred_image = blur_picture_parallel(filename, kernel_size);
                std::cout << "[LOGGER]: Picture is getting Blurred with 2 threads\n";
                blurred_image.write("blurred_" + filename.string());
                std::cout  << "[LOGGER]: Picture was saved\n";
            } catch (convert_error &e) {
                std::cerr << "[ERROR]: exception occured: " << e.what() << std::endl;
                return EXIT_FAILURE;
            }
        } else {
            std::cerr << "[ERROR]: no picture with name " << filename << " exists\n";
			return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
