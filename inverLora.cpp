#include "inverLora.h"

int main() {
    int status = 0;

    stdio_init_all();
    LoRa lora;
    
    status = lora.iniciarLoRa(915E6);
    
    if(status){
        printf("LoRa iniciado Correctamente \n");
    }
    else{
        printf("Falla en inicialisacion LoRa \n");
    }

    while (true) {
        printf("sigo vivo!\n");
        sleep_ms(1000);
    }
    
    return 0;
}
