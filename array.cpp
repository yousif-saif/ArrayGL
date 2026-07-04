#include "./headers/array.h"
#include "./headers/pixel.h"
#include "./headers/render.h"


Array::Array(int rows, int cols, int pixelSize, glm::vec3 color, Renderer *renderer, bool show_lines, int z_index) 
: rows(rows), cols(cols), pixelSize(pixelSize), color(color), show_lines(show_lines), z_index(z_index) {

    width = cols * pixelSize;
    height = rows * pixelSize;


    vector<float> color_vector = {color[0], color[1], color[2]};
    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {
            Pixel new_pixel = Pixel(
                j*pixelSize,
                i*pixelSize,
                (int)pixelSize, 
                (int)pixelSize, 
                color_vector,
                z_index
            );
            data.push_back(new_pixel);

            if (show_lines) {
                Pixel vertical = Pixel(
                    j*pixelSize,
                    0.0,
                    line_width,
                    rows*pixelSize,
                    vector<float>{0.0f, 0.0f, 0.0f},
                    z_index
                );

                Pixel horizontal = Pixel(
                    0.0,
                    i*pixelSize,
                    cols*pixelSize,
                    line_width,
                    vector<float>{0.0f, 0.0f, 0.0f},
                    z_index
                );


                data.push_back(vertical);
                data.push_back(horizontal);

            }


        }
    }

    if (show_lines) {
        // add one more vertical and horizontal line to complete the lines
        Pixel vertical = Pixel(
            rows*pixelSize,
            0.0,
            line_width,
            rows*pixelSize,
            vector<float>{0.0f, 0.0f, 0.0f},
            z_index
        );

        Pixel horizontal = Pixel(
            0.0,
            cols*pixelSize,
            cols*pixelSize, // to fix the dead pixel at the bottom-right
            line_width,
            vector<float>{0.0f, 0.0f, 0.0f},
            z_index
        );


        data.push_back(vertical);
        data.push_back(horizontal);
    }

    renderer->arrays_buffer.push_back(this);

}