
#include <cstdint>

double map(float x, float in_min, float in_max, float out_min, float out_max) {
    return out_min + (x - in_min) * (out_max - out_min) / (in_max - in_min);
}


void computeBasic(int x, int y, int mit, uint8_t* mem){
  for(int iy = 0; iy < y; iy++){
    for(int jx = 0; jx < x; jx++){

      double x0 = map(jx, 0, x, -2, 1);
      double y0 = map(iy, 0, y, -1.75, 1.75);

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
          mem[iy * x + jx] =  (uint8_t)map(c, 0,mit, 0, 255);
          break;
        }
      }
      if(c == mit){
        mem[iy * x+ jx] = 0;
      }
    }
  }
 
}



