
#include <cstdint>

double map(double x, double in_min, double in_max, double out_min, double out_max) {
    return out_min + (x - in_min) * (out_max - out_min) / (in_max - in_min);
}


void computeBasic(int x, int y, int mit, uint8_t* mem){
  for(int iy = 0; iy < y; iy++){
    for(int jx = 0; jx < x; jx++){

      double x0 = map(jx, 0.0, x, -2.0, 1.0);
      double y0 = map(iy, 0.0, y, -1.75, 1.75);

      double r = x0;
      double i  = y0;

      int c  = 0; 
      while(c++ <mit){
        double a = r * r;
        double b = 2.0 * r * i;
        double d = i * i * -1.0;

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



