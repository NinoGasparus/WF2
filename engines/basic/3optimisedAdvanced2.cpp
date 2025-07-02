
#include <cmath>
#include <cstdint>
#include <cstdlib>




/*
*
* x0 increments by a constant step with each iteration,
* said step can be precalculated skipping the need for its calculation alltogether,
* said step is same  to the precomputed  constants r2 and r3
* */


void computeAdvancedOptimised2(int x, int y, int mit, uint8_t* mem){
  double x0, y0, r, i, a;
  double minX = -2.0;
  double maxX = 1.0;

  double minY = -1.75;
  double maxY = 1.75;

  x0 = minX;
  y0 = minY;
  
  double r1 = 255.0 /mit;

  double dx0 = std::fabs(minX-maxX) /x;
  double dy0 = std::fabs(minY-maxY) /y;
  
  int c = 0;
  
   

  for(int iy = 0; iy < y; iy++){
    for(int jx = 0; jx < x; jx++){
      c = 0;
      

      r = x0;
      i  = y0;

      c  = 0; 
      while(c++ <mit){
        a = r * r - i * i + x0;
        i = 2.0 * r * i + y0;
        r = a;

        if(r * r + i * i > 4.0){
          mem[iy * x + jx] =  (uint8_t)(c* r1);
          break;
        }
      }
      if(c == mit){
        mem[iy * x+ jx] = 0;
      }
      x0 = std::fma(jx, dx0, minX);
    }
    y0 +=  dy0;
    x0 = -2;
  }
 
}



