#include <cstdint>
#include <iostream>

void printMem(uint8_t* mem, int amt){
  for(int i =0; i < amt; i++){
    std::cout << (int)mem[i]; 
  }
  std::cout << '\n';
}
