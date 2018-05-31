#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PC 32

int registrador[33];//registradores
unsigned int memoria[0x10000];

void func_R(int d, int s, int t, int shift, int funct);
void func_I(int opcode, int s, int t, int I);
void func_J(int opcode, int I);
void decode(unsigned int inst);
int simula();
