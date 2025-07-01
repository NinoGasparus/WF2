


##g++  -O3 -fno-inline -fno-unroll-loops -g -S  main.cpp render.cpp engines/basic/*  engines/unrolled/* -lSDL2 -lGL  main
g++ -O0 -g -mfma  main.cpp render.cpp engines/basic/*.cpp engines/unrolled/*.cpp -lSDL2 -lGL -o  main

