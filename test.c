// #include <stdio.h>
// #include <string.h>
#include "pico/stdlib.h"
// #include "pico/binary_info.h"
// #include "hardware/spi.h"

// declaracion de pines spi 
// #define PIN_MISO 6
// #define PIN_CS   7
// #define PIN_SCK  8
// #define PIN_MOSI 9
// #define SPI_PORT spi0



int main() {

    // uint LORA_RESET = 21;
    // gpio_init(LORA_RESET);
    // gpio_set_dir(LORA_RESET,GPIO_OUT);
    
    // stdio_init_all();
    // spi_init(SPI_PORT, 20000000);
    // spi_set_format(SPI_PORT, 8, 0, 0, 0);
    // gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    // gpio_set_function(PIN_CS, GPIO_FUNC_SPI)  ;
    // gpio_set_function(PIN_SCK, GPIO_FUNC_SPI) ;
    // gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    
 
    while (true) {
        // gpio_put(LORA_RESET,1);
        // sleep_ms(250);
        // gpio_put(LORA_RESET,0);

        printf("sigo vivo!\n");
        sleep_ms(1000);
    }
    return 0;
}