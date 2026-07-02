#include <iostream>
#include <vector>

using namespace std;


// class Matrix2D {
//     public:
//         size_t rows;
//         size_t cols;
//         vector<int> data;

//         Matrix2D(size_t r, size_t c) : rows(r), cols(c), data(r * c, 0) {}

//         class RowProxy {
//             private:
//                 Matrix2D& parent;
//                 size_t row_index;
            
//             public:
//                 RowProxy(Matrix2D& p, size_t r) : parent(p), row_index(r) {}

//                 int& operator[](size_t col_index) {
//                     if (col_index >= parent.cols) {
//                         throw out_of_range("Column index out of bounds!");
//                     }

//                     return parent.data[row_index * parent.cols + col_index];
//                 }
//         };
    
//         RowProxy operator[](size_t row_index) {
//             if (row_index >= rows) {
//                 throw out_of_range("Row index out of bounds");
//             }

//             return RowProxy(*this, row_index);
//         }

// };


// void print_matrix(Matrix2D matrix) {
//     for (int i=0; i < matrix.rows; i++) {
//         for (int j=0; j < matrix.cols; j++) {
//             cout << matrix[i][j] << " ";
//         }
//         cout << endl;
//     }
// }



void print(vector<int> nums) {
    for (int i : nums) {
        cout << i << " ";
    }
}

void change(vector<int> &nums) {
    for (int i = 0; i < nums.size(); i++) {
        nums[i] += 1;
    }
}

int main() {
    vector<int> nums = {1, 2, 3};
    cout << "BEFORE: " << " ";
    print(nums);
    change(nums);
    cout << "AFTER: " << " ";
    print(nums);


    return 0;
}