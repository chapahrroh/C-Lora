#include "src/Loralib.h"

int main() {
    int status = 0;
    int compensacionTemp = -197;

    stdio_init_all();
    // LoRa lora;

    status = lora.iniciarLoRa(915E6);

    if(status){
        printf("LoRa iniciado Correctamente \n");
    }
    else{
        printf("Falla en inicialisacion LoRa \n");
    }

    while (true) {
        int temp = lora.tempSX1276() + compensacionTemp;
        printf("Temperatura leida por SX276: %d \n", temp);
        sleep_ms(1000);
    }

    return 0;
}
