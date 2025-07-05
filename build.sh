


##g++  -O3 -fno-inline -fno-unroll-loops -g -S  main.cpp render.cpp engines/basic/*  engines/unrolled/* -lSDL2 -lGL  main
g++ -O0 -g main.cpp render.cpp  utils.cpp engines/basic/*.cpp engines/simple/* -lSDL2 -lGL -lGLEW -o  main

