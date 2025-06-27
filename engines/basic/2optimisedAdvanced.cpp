
#include <cstdint>




/*
*
 inline the map, manually, cant trust compiler
* manually simplify the map calls further as they do much of not needed calculations such as x -0 and 1 --2 etc
*
*
* some constant ratios can be precalculated 
* */


void computeAdvancedOptimised(int x, int y, int mit, uint8_t* mem){
  double x0, y0, r, i, a;

  double r1 = 255.0 /mit;
  double r2 = 3.0 /x;
  double r3 = 3.5 /y;
  int c = 0;

  for(int iy = 0; iy < y; iy++){
    for(int jx = 0; jx < x; jx++){
      c = 0;
      
      x0 = -2 + jx * r2;
      y0 = -1.75 + iy * r3; 

      r = x0;
      i  = y0;

      c  = 0; 
      while(c++ <mit){
        a = r * r - i * i + x0;
        i = 2 * r * i + y0;
        r = a;

        if(r * r + i * i > 4){
          mem[iy * x + jx] =  (uint8_t)(c* r1);
          break;
        }
      }
      if(c == mit){
        mem[iy * x+ jx] = 0;
      }
    }
  }
 
}



