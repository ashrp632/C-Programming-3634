#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int countLines(FILE *fp){

  char buf[BUFSIZ];
  int numberLines = 0;

  // get a label for the current position in the file
  long int start = ftell(fp);
  
  while(fgets(buf, BUFSIZ, fp)){
    ++numberLines;
  }

  // rewind back to the original start
  fseek(fp, start, SEEK_SET);

  return numberLines;
}


int main(int argc, char **argv){
  FILE *fp = fopen(argv[1], "r");
  char buf[BUFSIZ];
  int numberLines = countLines(fp);
  float *v = (float*) malloc(numberLines*sizeof(float));
  float *k = (float*) malloc(numberLines*sizeof(float));
  float sumOne, sumTwo, meanOne, meanTwo, sdOne, sdTwo;
  int n;
  for(n=0;n<numberLines;n++){
    fgets(buf, BUFSIZ, fp);
    int res = sscanf(buf, "%f %f", v+n, k+n);
    if(res == -1) {
      break;
    }
  }
  fclose(fp);
  for(int i=0; i<numberLines;++i){
    sumOne+=v[i];
    sumTwo+=k[i];
  }
  meanOne = sumOne/numberLines;
  meanTwo = sumTwo/numberLines;
  for(int t=0;t<numberLines;++t){
    sdOne += pow(v[t] - meanOne, 2);
    sdTwo += pow(k[t] - meanTwo, 2);
  }
 sdOne = sqrt(sdOne/numberLines);
 sdTwo = sqrt(sdTwo/numberLines);
 printf("%f, %f\n", sdOne, sdTwo);
}
