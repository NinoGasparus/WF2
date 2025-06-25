#include <cstdint>
#include <cstdio>






int x = 30;
int y = 10;
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
  while(c++ < 120){
    double a = r * r;
    double b = 2 * r * i;
    double d = i * i * -1;

    double e = r + d + x0;
    double f = b + y0;
    r = e; 
    i = f;

    if(r * r + i * i < 4){
      return (uint8_t)map(c, 0, 120, 0, 255);
    }
  }

  return 0;

}







int main(){

  for(int i = 0; i < y; i++){
    for(int j = 0; j < x; j++){
      printf("%d", compute(j, i)  );
    }

    printf("%c", '\n');
  }
  
  printf("complete\n");


  return 0;
}
