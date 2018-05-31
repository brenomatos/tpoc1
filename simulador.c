#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

// #define PC 32
//
// int registrador[33];//registradores
// unsigned int memoria[0x10000];


void func_R(int d, int s, int t, int shift, int funct){//Executa instruções de tipo R
    //printf("Func R -> rd=%d rs=%x rt=%x shift=%x funct=%d\n",d,s,t,shift,funct );

    if (funct == 0x20) {//ADD
      registrador[d] = registrador[s] + registrador[t];
    }
    else if (funct == 0x24) {//AND
      registrador[d] = registrador[s] & registrador[t];
    }
    else if (funct == 0x2A) {//DIV
      registrador[d] = registrador[s] / registrador[t];
    }
    else if (funct == 0X08) {//JR
      registrador[PC] = registrador[s];
    }
    else if (funct == 0x18) {//MULT
      registrador[d] = registrador[s] * registrador[t];
    }
    else if (funct == 0x25) {//OR
      registrador[d] = registrador[s] | registrador[t];
    }
    else if (funct == 0x00) {//SLL
      registrador[d] = registrador[t] << shift;
    }
    else if (funct == 0x02) {//SRL
      registrador[d] = registrador[t] >> shift;
    }
    else if (funct == 0x22) {//SUB
      registrador[d] = registrador[s] - registrador[t] ;
    }
    else if (funct == 0x26) {//XOR
      registrador[d] = registrador[s] ^ registrador[t];
    }
}

void func_I(int opcode, int s, int t, int I){//Executa instruções de tipo I
    //printf("Func I -> op=%x rs=%x rt=%x im=%x\n",opcode,s,t,I );

    if (opcode == 0x08) {//ADDI
      registrador[t] = registrador[s] + I;
    }
    else if (opcode == 0x0C) {//ANDI
      registrador[t] = registrador[s] & I;
    }
    else if (opcode == 0x04) {//BEQ
      if (registrador[t] == registrador[s]) {
        registrador[PC] = I-1;
        // JUMP I;
      }
    }
    else if (opcode == 0x07) {//BGTZ
      if(registrador[s] > 0){
        registrador[PC] = I-1;
        // JUMP I;
      }
    }
    else if (opcode == 0x01) {//BLTZ
      if(registrador[s] < 0){
        registrador[PC] = I-1;
        // JUMP I;
      }
    }
    else if (opcode == 0x05) {//BNE
      if (registrador[s] != registrador[t]) {
        registrador[PC] = I-1;
        // JUMP I;
      }
    }
    else if (opcode == 0x23) {//LW
      registrador[t] = memoria[registrador[s] + I];
    }
    else if (opcode == 0x0D) {//ORI
      registrador[t] == registrador[s] | I;
    }
    else if (opcode == 0x2B) {//SW
      memoria[registrador[s] + I] = registrador[t];
    }
    else if (opcode == 0x3E) {//IN
      int retorno = scanf("%d", &registrador[s]);

    }
    else if (opcode == 0x3D) {//OUT
      printf("%d\n",registrador[s]);
    }
}


void func_J(int opcode, int I){ //Executa instruções de tipo J
  //printf("Func R -> op=%x im=%x\n",opcode,I );

  if (opcode == 0x02) {///J
    registrador[PC] = I-1;
    // JUMP I;
  }
  else if (opcode == 0x03) {//JAL
    // SAVE PC;
    registrador[31] = registrador[PC];
    // JUMP I;
    registrador[PC] = I-1;
  }
  //instrucoes extras
  else if (opcode == 0x3F) {//HALT
    exit(0);
    // FINALIZA O PROGRAMA;
  }
}

void decode(unsigned int inst){
  //Decodifica e executa a instrução
  int opcode = inst >> 26;

  if(opcode == 0){
    //Decode tipo R
    int t = (inst >> 16) & 0x1F;
    int d = (inst >> 11) & 0x1F;
    int s = (inst >> 21) & 0x1F;
    int shift = (inst >> 6) & 0x1F;
    int funct = inst & 0x3F;
    func_R(d,s,t,shift,funct);
  }else if(opcode == 2 || opcode == 3 || opcode == 0x3F ){
    //Decode tipo J
    int I;
    if((inst>>25) & 1){
      I = inst & 0x03FFFFFF;
      I = I | 0xFC000000;
    }else{
      I = inst & 0x03FFFFFF;
    }
    func_J(opcode,I);
  }else{
    //Decode tipo I
    int t = (inst >> 16) & 0x1F;
    int s = (inst >> 21) & 0x1F;
    int I;
    if((inst>>15) & 1){
      I = inst & 0x0000FFFF;
      I = I | 0xFFFF0000;
    }else{
      I = inst & 0x0000FFFF;
    }
    func_I(opcode,s,t,I);
  }

}

int simula(){

  //Enquanto tiver instrução pra executar
  while(memoria[registrador[PC]]!=0 || registrador[PC]>0xFFF){

    //Executa a instrução
    decode(memoria[registrador[PC]]);
    //Incrementa o PC para a próxima instrução
    registrador[PC]++;
  }

}
