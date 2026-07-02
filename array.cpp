#include "./headers/array.h"
#include "./headers/pixel.h"

// Array::Array(int gridW, int gridH, int pixelSize, bool showLines) 
//     : gridW_(gridW), gridH_(gridH), pixelSize_(pixelSize), showLines_(showLines)
// {
//     glm::vec3 color{0.5, 0.8, 0.0};
//     vector<float> colorVec{color[0], color[1], color[2]};

//     for (float h=0; h < gridH; h++) {
//         vector<Pixel> row;
//         for (float w=0; w < gridW; w++) {
//             row.push_back(Pixel(pixelSize * w, pixelSize * h, (float)pixelSize, (float)pixelSize, colorVec));
//         }
//         pixels.push_back(row);
//     }

    

// }




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