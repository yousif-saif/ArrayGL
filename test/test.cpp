#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int*> pointers;
    
    pointers.push_back(&arr[1]);
    pointers.push_back(&arr[1]);

    bool r = &arr[1] == pointers[1];
    cout << r << endl;

    return 0;

}