#include <chrono>
#include <cstdint>
#include <cstdio>
#include <exception>
#include <iostream>
#include <string>


extern void render(int  x, int y, uint8_t* data);
int mit =100;
int x = 1920;
int y = 1080;

uint8_t* mem = new uint8_t[x* y];

double map(float x, float in_min, float in_max, float out_min, float out_max) {
    return out_min + (x - in_min) * (out_max - out_min) / (in_max - in_min);
}


uint8_t compute(int X, int Y){
  double x0 = map(X, 0, x, -2, 1);
  double y0 = map(Y, 0, y, -1.75, 1.75);

  double r = x0;
  double i  = y0;

  int c  = 0; 
  while(c++ <mit){
    double a = r * r;
    double b = 2 * r * i;
    double d = i * i * -1;

    double e = a + d + x0;
    double f = b + y0;
    r = e; 
    i = f;

    if(r * r + i * i > 4){
      return (uint8_t)map(c, 0,mit, 0, 255);
    }
  }

  return 0;

}







int main(int argc, char* argv[]){
  if(argc >=2){
    try {
      if(argv[1][0] != 'r'){
        mit = std::stoi(argv[1]);
      }else{
        mit = 1000;
      }
    } catch (std::exception e) {
      mit = 1000;
    }
  }
  auto start = std::chrono::high_resolution_clock::now();
  for(int i = 0; i < y; i++){
    for(int j = 0; j < x; j++){
      mem[i * x + j] =   compute(j, i);
    }
  }
  auto end  = std::chrono::high_resolution_clock::now();
  unsigned long  time =  std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
  std::cout << "complete " << time << std::endl;
  if(argc >= 3 ){
    try{
      if(argv[2][0] == 'r'){
       render(x, y,mem);
      }
    }catch(std::exception e){

    }
  }
  delete[] mem;
  return 0;
}
