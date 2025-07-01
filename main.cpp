#include <chrono>
#include <cstdint>
#include <cstdio>
#include <exception>
#include <iostream>
#include <string>


extern void render(int  x, int y, uint8_t* mem);
extern void render2(int  x, int y, uint8_t* mem);

extern void printMem(uint8_t* mem, int amt);
extern void compareAlg(void (*alg1) (int, int, int, uint8_t *), void (*alg2) (int, int, int, uint8_t*));
extern void scramble(int x, int y, int mit, uint8_t* mem);

extern void computeSimpleOptimised(int x, int y, int mit, uint8_t* mem);
extern void computeAdvancedOptimised(int x, int y, int mit, uint8_t* mem);
extern void computeAdvancedOptimised2(int x, int y, int mit, uint8_t* mem);
extern void computeAdvancedOptimised3(int x, int y, int mit, uint8_t* mem);
extern void computeAdvancedOptimised4(int x, int y, int mit, uint8_t* mem);
extern void computeUnrolled(int x, int y, int mit, uint8_t* mem);
int mit =100;
int x = 1920;
int y = 1080;


int renderCount = 1;
uint8_t* mem = new uint8_t[x* y];

bool benchmark = false;



int main(int argc, char* argv[]){
  if(argc >=2){
    try{
      if(argv[1][0] == 'B'){
        benchmark = true;
        mit = 10000;
      }
    
    }catch(std::exception x){

    }
  }
  if(argc >=2){
    try {
      if(argv[1][0] != 'r' && !benchmark){
        mit = std::stoi(argv[1]);
 
      }else{
        mit = 1000;
      }
    } catch (std::exception e) {
      mit = 1000;
    }
  }


  if(argc >=3){
    try{
      if(argv[2][0] == 'a' && !benchmark){
       renderCount = std::stoi(argv[3]);
      }
    }catch(std::exception x){

    }
  }
  for(int i =0 ; i < renderCount; i++){
    auto start = std::chrono::high_resolution_clock::now();
    
      //computeBasic(x,y, mit, mem);
     // computeSimpleOptimised(x,y, mit, mem);
  //  computeAdvancedOptimised(x, y, mit, mem);
   // computeAdvancedOptimised2(x, y, mit, mem);
 //       computeAdvancedOptimised3(x, y, mit,  mem);
   computeAdvancedOptimised4(x, y, mit,  mem);
 //       computeUnrolled(x, y, mit, mem);

    auto end  = std::chrono::high_resolution_clock::now();
    



    unsigned long  time =  std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
if(!benchmark){    std::cout <<  time << std::endl;}
  }

  if(benchmark){
    compareAlg(computeAdvancedOptimised4,scramble);
  }


  if(argc >=3 && !benchmark){
    try{
      if(argc >= 2 && (argv[4][0] == 'r' ||argv[2][0] == 'r' && argv[4][1] != 'v' && argv[2][1] != 'v')){
       render(x, y,mem);
      }else if(argv[4][1] == 'v' || argv[2][1] == 'v'){
        render2(x,y,mem);
      }
    }catch(std::exception e){

    }
  }
  delete[] mem;
  return 0;
}
