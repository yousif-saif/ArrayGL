#include "./headers/array.h"
#include "./headers/pixel.h"


Array::Array(int rows, int cols, int pixelSize, glm::vec3 color, bool showLines, int z_index) 
: rows(rows), cols(cols), pixelSize(pixelSize), color(color), showLines(showLines), z_index(z_index) {
    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {
            data.push_back(Pixel(
                    j*pixelSize,
                    i*pixelSize,
                    (int)pixelSize, 
                    (int)pixelSize, 
                    vector<float>{color[0], color[1], color[2]},
                    z_index
                )
            );

        }
    }

}