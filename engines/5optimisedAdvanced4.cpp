
#include <cstdint>
#include <cstdio>
#include <cstdlib>




/*
 * r2, can be precomputed, 
 *
 *
 * precomputing rr or ii negativeley impacts performance.- 
 */


void computeAdvancedOptimised4(int x, int y, int mit, uint8_t* mem){
  double x0, y0, r, i, a;
  double minX = -2;
  double maxX = 1;

  double minY = -1.75;
  double maxY = 1.75;

  x0 = minX;
  y0 = minY;
  //double rr, ii;
  double r1 = 255.0 /mit;
  int r2;

  double dx0 = std::abs(minX-maxX) /x;
  double dy0 = std::abs(minY-maxY) /y;

  int c = 0;
   
  int jx = 0;  
  void* labels[] = {&&noAction, &&stop};

  for(int iy = 0; iy < y; iy++){
    r2 = iy * x;
    while(jx < x){
      
      r = x0;
      i  = y0;
      c  = 0; 
      
      while(c <mit){
        //rr = r* r;
        //ii = i * i;
        a = r * r - i * i + x0;
        i = 2 * r * i + y0;
        r = a;

        goto *labels[r*r+ i * i >= 4];
        stop:
          break;
        noAction:
          c++;
      }
        mem[r2 + jx] =(uint8_t) !(c == mit)  * (c*r1) ; 
        jx++;
        x0 += dx0;
    }
    y0 += dy0;
    x0 = -2;
    jx = 0; 
  }
 
}



