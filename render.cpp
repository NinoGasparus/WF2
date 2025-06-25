#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>



//convert 8bit ints to chars for viewing
void preRender(uint8_t* data, int len){
  char range[] = {',', ':', 'o', 'O', '@', '#'};

  for(int i =0; i < len; i++){
    if(data[i] == 0){
      data[i] = '.';
    }else{
      //map value to somethign between 0 and 5 
      data[i] = range[(int)data[i]/43];
    }
  }

}


uint8_t getMAX(int x, int y, int blockX, int blockY, int bsx, int bsy, uint8_t * data){
  int max = 0;  
/* 

  for(int i = 0; i < bsy; i ++){
    for(int j = 0; j < bsx; j++){
      int val = data[(blockY + i) * x+ (blockX+ j)];
      if(val > max)
        max = val;
    }
  }

*/
  for(int i = blockY; i < blockY + bsy; i++){
    for(int j = blockX; j < blockX + bsx; j++){
      if(data[i * x + j] > max){
        max = data[i*x+j];
      }
    }
  }
  return max;
}



uint8_t* downscale(uint8_t* data, int x, int y, int scale){
  int newX = (int) x / scale;
  int newY = (int) y / scale;
  int bsx = x / newX;
  int bsy = y / newY;

  int newSize = newX * newY;

  uint8_t* newData = new uint8_t[newSize];

  for(int i  = 0; i < newY ; i+= 1 ){
    for(int j = 0; j < newX; j+=1){
      newData[i * newX + j] = getMAX(x, y ,j*bsx, i * bsy, bsx, bsy, data); 
    }
  }
  return newData;
}

void render(int x, int y, uint8_t* data){
  int df = 32;
  int newlen =  (int)(x/df) * (int)(y/df);
  uint8_t* newData = downscale(data, x , y, df);

  preRender(newData, newlen);

  char* buff = new char[x/df];

  for(int i = 0; i < y/df; i++){
    memcpy(buff,newData+i*(x/df), x/df);
    std::cout << buff <<  std::endl;
  }

  delete[] newData;
  

}
