#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulador.c"
#include "header.h"


unsigned char buf;
unsigned int inst = 0;

int main(int argc, char const *argv[]) {
  FILE *fp = fopen(argv[1],"rb");

  memset(memoria,0,sizeof(memoria));

  int cbyte = 0;
  int it = 0;
  while(fread(&buf,1,1,fp)>0){
      inst = inst | (buf << (24 - (8*cbyte)));

      if(cbyte==3){
          memoria[it]=inst;
          it++;
          inst = 0;
          cbyte = 0;
          continue;
      }
      cbyte++;
  }

  registrador[PC] = 0;

  simula();

  return 0;
}
