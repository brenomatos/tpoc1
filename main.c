#include <stdio.h>
#include <stdlib.h>

int registrador[32];//registradores
int memoria[10000000];

void func_R(int d, int s, int t, int shift, int funct){//se o opcode eh 0, decide aqui dentro
    if (funct == 64) {//ADD
      registrador[d] = registrador[s] + registrador[t];
    }
    else if (funct == 68) {//AND
      registrador[d] = registrador[s] & registrador[t];
    }
    else if (funct == 74) {//DIV
      registrador[d] = registrador[s]/registrador[t];
    }
    else if (funct == 8) {//JR
      registrador[d] = registrador[s]/registrador[t];
    }
    else if (funct == 40) {//MULT
      registrador[d] = registrador[s] * registrador[t];
    }
    else if (funct == 69) {//OR
      registrador[d] = registrador[s] | registrador[t];
    }
    else if (funct == 0) {//SLL
      registrador[d] = registrador[t] << shift;
    }
    else if (funct == 2) {//SRL
      registrador[d] = registrador[t] >> shift;
    }
    else if (funct == 66) {//SUB
      registrador[d] = registrador[s] - registrador[t] ;
    }
    else if (funct == 72) {//XOR
      registrador[d] = registrador[s] ^ registrador[t];
    }
}

void simula(int opcode, int d, int s, int t, int shift, int funct, int I){
  if (opcode == 0) {//opcode 0 = funcoes tipo R
    func_R(d, s, t, shift, funct)
  }
  //instrucoes tipo I
  else if (opcode == 8) {//ADDI
    registrador[t] = registrador[s] + I;
  }
  else if (opcode == 6) {//ANDI
    registrador[t] = registrador[s] & I;
  }
  else if (opcode == 4) {//BEQ
    if (registrador[t] == registrador[s]) {
      JUMP I;
    }
  }
  else if (opcode == 7) {//BGTZ
    if(registrador[s] > 0){
      JUMP I;
    }
  }
  else if (opcode == 1) {//BLTZ
    if(registrador[s] < 0){
      JUMP I;
    }
  }
  else if (opcode == 5) {//BNE
    if (registrador[s] != registrador[t]) {
      JUMP I;
    }
  }
  else if (opcode == 67) {//LW
    registrador[t] = memoria[registrador[s] + I];
  }
  else if (opcode == 13) {//ORI
    registrador[t] == registrador[s] | I;
  }
  else if (opcode == 75) {//SW
    memoria[registrador[s] + I] = registrador[t];
  }
  //instrucoes tipo J
  else if (opcode == 2) {///J
    JUMP I;
  }
  else if (opcode == 3) {//JAL
    JUMP I;
    registrador[31] = program_counter;//SAVE PC;

  }
  //instrucoes extras
  else if (opcode == 127) {//HALT
    exit(); //finaliza o programa
    FINALIZA O PROGRAMA;
  }
  else if (opcode == 126) {//IN
    int entrada;
    scanf("%d", &entrada);
    registrador[s] = entrada;
  }
  else if (opcode == 125) {//OUT
    printf("%d\n",registrador[s] );
  }

}

unsigned char buffer;

unsigned int instrucao = 0;
int main(int argc, char const *argv[]) {
  FILE *fp = fopen(argv[1],"rb");
  int i = 0;
  while (fread(&buffer,1,1,fp)>0) {
  	printf("%x\n", instrucao);
  	instrucao = instrucao | buffer;
  	instrucao = instrucao << 8;
  	i++;
  	if (i==3)
  	{
  		printf("%x\n", instrucao);
  		instrucao = 0;
  		i=0;
  	}

  }


  return 0;
}
