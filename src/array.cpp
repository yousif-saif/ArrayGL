#include "../include/ArrayGL/array.h"
#include "../include/ArrayGL/pixel.h"
#include "../include/ArrayGL/render.h"
// #include "../include/ArrayGL/ArrayGL.h"


// vector<float> scale_down_color(vector<int> RGB) {
//     vector<float> result;
//     for (int channel : RGB) {
//         result.push_back(channel/255.0);
//     }
//     return result;
// }


Array::Array(int rows, int cols, int pixelSize, vector<int> color, Renderer *renderer, bool show_lines, int z_index) 
: rows(rows), cols(cols), pixelSize(pixelSize), color(color), show_lines(show_lines), z_index(z_index) {

    width = cols * pixelSize;
    height = rows * pixelSize;
    vector<Pixel> linesPixels;

    for (int i=0; i <= rows; i++) {
        for (int j=0; j <= cols; j++) {
            if (i < rows && j < cols) {
                Pixel new_pixel = Pixel(
                    j*pixelSize,
                    i*pixelSize,
                    (int)pixelSize, 
                    (int)pixelSize, 
                    color,
                    z_index
                );
                data.push_back(new_pixel);
            }

            if (show_lines) {
                Pixel vertical = Pixel(
                    j*pixelSize,
                    0.0,
                    line_width,
                    height,
                    vector<int>{0, 0, 0},
                    z_index
                );

                Pixel horizontal = Pixel(
                    0.0,
                    i*pixelSize,
                    width+line_width, // to fix the dead pixel at the bottom right
                    line_width,
                    vector<int>{0, 0, 0},
                    z_index
                );
                

                linesPixels.push_back(vertical);
                linesPixels.push_back(horizontal);
            }


        }
    }

    // append all line pixels at the end of the data so it can't be altered 
    // the indexing system will check if the wanted index is in the range of rows and cols
    // wich will never touch these pixels
    data.insert(data.end(), linesPixels.begin(), linesPixels.end());
    renderer->arrays_buffer.push_back(this);

}



bool Array::collision(Array array2) {
    bool horizontalOverlap = (this->x + this->width >= array2.x) && (this->x <= array2.x + array2.width);    
    bool verticalOverlap =   (this->y + this->height >= array2.y) && (this->y <= array2.y + array2.height);
    return horizontalOverlap && verticalOverlap;
    
}

void Array::WASD_input(float speed) {
    Array::input_mode = "WASD";
    Array::speed = speed;
}

void Array::arrows_input(float speed) {
    Array::input_mode = "ARROWS";
    Array::speed = speed;
}