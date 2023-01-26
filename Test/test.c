#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void reloj(char caracter){
    int i;
    int relojVal;
    short tamanoCar = ((sizeof(caracter)*8)-1);
    short periodo = tamanoCar*2;

    for (i = periodo ; i>=0; i--) {
    
        if(relojVal==1){
            printf("1\n");
            relojVal = 0;
        }
        else{
            printf("0\n");
            relojVal = 1;
        }
     }
}

void recBin(long binario){
    int n,c,k;
    int tamano;
    n = binario;
    
    tamano = ((sizeof(binario)*8)-1);

    printf("%d en binario es: ",n);
    
    for (c=tamano; c>=0; c--) {
        k = n>>c;
        if (k&1) {
            printf("1");
        }
        else {
            printf("0");
        }
    }
    printf("\n");
}

int unBit(int dato, int pos){
    int out;

    out = dato>>pos;
    if(out&1){
        return 1;
    }
    else {
        return 0;
    }
}

int main(){
   
    long numTest = 500E6;

    recBin(numTest);

    printf("%d",unBit(numTest, 0));

    int bits = ((sizeof(long)*8)-1);
    int byts = sizeof(long);
    printf("tipo de dato long tiene %d bits\n",bits);
    printf("tipo de dato long tiene %d byts\n",byts);

    numTest = (numTest << 19)/32000000 ;

    char MSB = numTest >> 16;
    char MID = numTest >> 8;
    char LSB = numTest >> 0;

    recBin(numTest);
    printf("MSB =");
    recBin(MSB);
    
    return 0;

}


