#pragma once

#include "pixel.h"
#include "array.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

#include <GLFW/glfw3.h>

class Renderer;

class Array {
    public:
        float x = 0;
        float y = 0;

        int rows;
        int cols;
        float width;
        float height;
        // Rect dims;
        int z_index;
        int pixelSize;
        int line_width = 5;
        bool show_lines;
        function<void (void)> left_click_callback = NULL;
        string input_mode;
        int speed;

        vector<int> color;
        vector<Pixel> data;

        Array(int rows, int cols, int pixelSize, vector<int> color, Renderer *renderer, bool show_lines, int z_index=0);
        bool collision(Array array2);
        void WASD_input(float speed);
        void arrows_input(float speed);
        void on_left_click(function<void (void)> callback);

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