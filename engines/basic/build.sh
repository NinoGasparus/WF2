#!/bin/bash



FILE="5optimisedAdvanced4.cpp"
g++ -O0 -masm=intel -S  "$FILE" -o 5optimisedAdvanced4.asm

echo "compiled, edit, press key to continue"

read 

gcc -c 5optimisedAdvanced4.asm -o file.o

g++ -o0 -c  ../../main.cpp -o main.o
g++ -o0 -c ../../render.cpp -o render.o
g++ main.o render.o file.o -lSDL2 -lGL -o main

echo "done"
