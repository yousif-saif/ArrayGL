#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include "./pixel.h"

// class Array {
//     private:
//         int gridW_, gridH_;
//         int pixelSize_;
//         bool showLines_;

//     public:
//         vector<vector<Pixel>> pixels;
//         Array(int gridW, int gridH, int pixelSize, bool showLines);

//         int& operator[](int index) {
//             if (index > )
//         }
// };





class Array {
    public:
        int rows;
        int cols;
        int pixelSize;
        bool showLines;
        int z_index;
        glm::vec3 color;
        vector<Pixel> data;
        // glm::vec3 color{0.5, 0.8, 0.0};

        Array(int rows, int cols, int pixelSize, glm::vec3 color, bool showLines, int z_index=0);
        
        class RowProxy {
            private:
                Array& parent;
                int row_index;
            
            public:
                RowProxy(Array& p, int r) : parent(p), row_index(r) {}

                Pixel& operator[](int col_index) {
                    if (col_index >= parent.cols) {
                        throw out_of_range("Column index out of bounds!");
                    }

                    return parent.data[row_index * parent.cols + col_index];
                }
        };
    
        RowProxy operator[](int row_index) {
            if (row_index >= rows) {
                throw out_of_range("Row index out of bounds");
            }

            return RowProxy(*this, row_index);
        }

        

};