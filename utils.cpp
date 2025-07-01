#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <ostream>

void printMem(uint8_t* mem, int amt){
  for(int i =0; i < amt; i++){
    std::cout << (int)mem[i]; 
  }
  std::cout << '\n';
}



void compareAlg(void (*base) (int, int, int, uint8_t *), void (*compare) (int, int, int, uint8_t*)){
  int x = 1920;
  int y = 1080;
  int mit = 100;
  uint8_t* mem_f1 = new uint8_t[x*y];
  uint8_t* mem_f2 = new uint8_t[x*y];

 base(x,y,mit, mem_f1);
  compare(x,y,mit, mem_f2);

  int totalPixels = x * y;
  int diffPixels =0;
  for(int i = 0; i < totalPixels; i++){
    if(mem_f1[i] != mem_f2[i]){
      diffPixels ++;
    }
  }

  std::cout << diffPixels << "/" << totalPixels << " pixels diff: " << (double)(diffPixels*100.0/totalPixels)  << " % "<<  std::endl;
  


  int diffSum = 0;
  int maxOverestimate = 0;
  int maxOverestimateActuallValue = 0;
  int maxUnderestimate = 0;
  int maxUnderestimateActuallValue = 0;
  int curDiff = 0;

  if(diffPixels != 0){
      for(int i = 0; i < totalPixels; i++){
          if(mem_f1[i] != mem_f2[i]){
              curDiff = (int)mem_f2[i] - (int)mem_f1[i];
              diffSum += std::abs(curDiff);

              if(curDiff > maxOverestimate){
                  maxOverestimate = curDiff;
                  maxOverestimateActuallValue = (int)mem_f1[i];
              }else if(-curDiff > maxUnderestimate){
                  maxUnderestimate = -curDiff;
                  maxUnderestimateActuallValue = (int)mem_f2[i];
              }
          }
      }
      
      std::cout << "total offset : " << diffSum << "\n";
      std::cout << "max overestimate: " << maxOverestimate << " actuall value: " << maxOverestimateActuallValue << "\n";
      std::cout << "max underestimate: " << maxUnderestimate << "actuall Value: " << maxUnderestimateActuallValue <<  "\n";
      std::cout << "avg. offset  : " << (double)diffSum / diffPixels << "\n";
  }

}

void scramble(int x, int y, int mit, uint8_t* mem){
  std::srand(std::time(nullptr));
  for(int i= 0; i < y; i++){
    for(int j =0; j < x; j++){
      mem[i*x+ j]= (uint8_t) random() * 255;
    }
  }
}
