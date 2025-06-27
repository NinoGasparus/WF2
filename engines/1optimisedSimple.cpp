
#include <cstdint>




/*
*
* (r + i ) ( r + i ) + (r0 + i0 )
* simplifies down to 
*
* real part  : r * r - i * i + r0 
* imag :       2 * r * i + i0
* 
* 7 flops instead of 8
* 
*
* also remove all variable declarations out of the loop
*
*
* */
static double map(float x, float in_min, float in_max, float out_min, float out_max) {
    return out_min + (x - in_min) * (out_max - out_min) / (in_max - in_min);
}


void computeSimpleOptimised(int x, int y, int mit, uint8_t* mem){
  double x0, y0, r, i, a;
  int c = 0;
  for(int iy = 0; iy < y; iy++){
    for(int jx = 0; jx < x; jx++){
      c = 0;
      x0 = map(jx, 0, x, -2, 1);
      y0 = map(iy, 0, y, -1.75, 1.75);

      r = x0;
      i  = y0;

      c  = 0; 
      while(c++ <mit){
        a = r * r - i * i + x0;
        i = 2 * r * i + y0;
        r = a;
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



