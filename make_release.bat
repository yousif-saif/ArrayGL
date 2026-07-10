g++ -c ./src/*.cpp -I./include -L./lib ./glad.c -O3 -std=c++17
ar rcs libArrayGL.a *.o
rm *o