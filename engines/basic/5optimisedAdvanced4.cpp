
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>




/*
* both writes can be branchlessly joined into one
* 
* if check can be converted into a conditional jump (allegaldy faster slight improvement 1-3ms)
* */


void computeAdvancedOptimised4(int x, int y, int mit, uint8_t* mem){
  double x0, y0, r, i, a;
  double minX = -2.0;
  double maxX = 1.0;

  double minY = -1.75;
  double maxY = 1.75;

  x0 = minX;
  y0 = minY;
  
  double r1 = 255.0 /mit;
  int r2;
  double dx0 = std::fabs(minX-maxX) /x;
  double dy0 = std::fabs(minY-maxY) /y;

  
  int c = 0;
  
   
  int jx = 0;  
  int iy = 0;
  void* loop1Labels[] = {&&exit, &&redo};
  void* loop2Labels[] = {&&exit2, &&redo2};
  redo:
  //iy < y
  while(true){
      r2 = iy * x;
      redo2:
      while(true){
            r = x0;
            i  = y0;
            c  = 0; 
              
              while(true){
                a = r* r - i * i + x0;
                i = 2.0 * r * i + y0;
                r = a;

                if(r *r + i * i > 4.0 || c++>mit){
                  break;
                }
              }
              mem[r2+ jx] =(uint8_t) ((int)!(c == mit))  * (c*r1) ; 
              x0 += dx0;
//                x0 = minX + jx * dx0;
              jx ++;
              goto *loop2Labels[jx < x];
          }
      exit2:
      y0 += dy0;
//        y0 = minY + iy * dy0;
      x0 = -2.0;
      jx = 0; 
      iy ++;
      goto *loop1Labels[iy < y];
    
  }
  exit:
  return;
}



