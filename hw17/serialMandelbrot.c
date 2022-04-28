/*

To compile:
make serialMandelbrot

To run:
./serialMandelbrot

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "png_util.h"

void mandelbrot(const int Nx, 
		const int Ny, 
		const float xmin,
		const float ymin,
		const float dx, 
		const float dy,
		float * count){

  int n,m;
  
  for(m=0;m<Ny;++m){
    for(n=0;n<Nx;++n){
      
      float cx = xmin + n*dx;
      float cy = ymin + m*dy;

      float x = 0;
      float y = 0;
      
      int Nit = 200;
      int t, cnt=0;
      for(t=0;t<Nit;++t){

	float xnew = cos(x) - cos(y) + cx;
	float ynew = cos(x)*cos(y) + cy;

	x = xnew;
	y = ynew;

	float r= x*x+y*y;
	if(r<4.f)
	  ++cnt;
      }

      count[n + m*Nx] = cnt;
    }
  }
  

}


int main(int argc, char **argv){

  int Nx = 4096;
  int Ny = 4096;

  /* box containing sample points */
  float xcent = -.759856;
  float ycent= .125547;
  float diam  = 0.151579;
  float xmin = xcent -0.5*diam;
  float xmax = xcent +0.5*diam;
  float ymin = ycent -0.5*diam;
  float ymax = ycent +0.5*diam;

  float dx = (xmax-xmin)/(Nx-1.f);
  float dy = (ymax-ymin)/(Ny-1.f);
  
  float *h_count = (float*) calloc(Nx*Ny, sizeof(float));

  double tic = clock();

  // call mandelbrot from here
  mandelbrot(Nx, Ny, xmin, ymin, dx, dy, h_count);

  double toc = clock();

  double elapsed = (toc-tic)/CLOCKS_PER_SEC;
  
  printf("elapsed time %g\n", elapsed);

  FILE *png = fopen("serialMandelbrot.png", "w");
  write_hot_png(png, Nx, Ny, h_count, 0, 80);
  fclose(png);

}
