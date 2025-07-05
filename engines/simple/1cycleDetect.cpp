
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>




/*
* */





void comCycleDetect(int x, int y, int mit, uint8_t* mem){
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

  // write into buff  
  double buff[mit+1][2];
  memset(buff, 0,2*(mit+1));
  //store first storeLim iterations into actuall buffer
  int storeLim = 20;
  storeLim =std::min(storeLim, mit);

  int prec = 10;

  bool* escBuff = new bool[x * y* prec * prec ];
  memset(escBuff, 0, (x * y * prec * prec));

  bool conv = false;

  redo:
  while(true){
      r2 = iy * x;
      redo2:
                c = mit -1;
      while(true){
            r = x0;
            i  = y0;
            c  = 0; 
 


            while(true){
              a = r* r - i * i + x0;
              i = 2.0 * r * i + y0;
              r = a;
       
              buff[c][0] = r;
              buff[c][1] = i;
              int ix = (int)((r - minX) / (maxX - minX) * x * prec);
              int iy = (int)((i - minY) / (maxY - minY) * y * prec);

              if(ix >= 0 && ix < x * prec && iy >= 0 && iy < y * prec){
                  if(escBuff[iy * x * prec + ix]){
                      conv = true;
                      c = 1;
                      break;
                  }
              }

              if(r *r + i * i > 4.0){
                 break;
              }
              if( c == mit){
                conv = true;
                c = 2;
                break;
              }
              c++;
            }




            mem[r2+ jx] =(uint8_t) (!(/* c == mit*/ false))  * (c*r1) ; 
            if(conv){
            //converged 
              for(int i =0; i < storeLim;i++){
                int rT =(int)(buff[i][0]  -minX) / (maxX - minX) * x * prec;
                int iT =(int)(buff[i][1]  -minY) / (maxY - minY) * y * prec;
                escBuff[(int)iT * x * prec +(int) rT] = true;
              }
              
            }
            x0 += dx0;
            jx ++;
            conv  = false;
            goto *loop2Labels[jx < x];
          }
      exit2:
      y0 += dy0;
      x0 = -2.0;
      jx = 0; 
      iy ++;
      goto *loop1Labels[iy < y];
    
  }
  exit:
  delete[] escBuff;
  return;
}

   

