#include "Loralib.h"

LoRa::LoRa(){
        
    gpio_init(LORA_RESET);
    gpio_set_dir(LORA_RESET,GPIO_OUT);
        
    spi_init(SPI_PORT, 12500);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI) ;
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);

}

// funcion de inicio del trasnductor
int LoRa::iniciarLoRa(long frecuencia){
    reset();
        
    uint8_t version = leerRegistro(0x42);
        if(version != 0x12){
            printf("falla conexion LORA\n");
        }
    
    // pone el transductor en estado "sleep"
    dormir();

    // establece la frecuencia de funcionamiento del transductor(solo se puede utilizar con el transductor en modo sleep o standby)
    setFrecuencia(frecuencia);

    // establese FIFOS TX y RX a 0
    escribirRegistro(REG_FIFO_TX_DIR_BASE, 0);
    escribirRegistro(REG_FIFO_RX_DIR_BASE, 0);

    // establece boost LNA (amplificacion de senal)
    escribirRegistro(REG_LNA,leerRegistro(REG_LNA) | 0x03);
    
    // se establece Ganancia LNA en automativo (auto AGC)
    escribirRegistro(REG_MODEM_CONFIG_3, 0x04);
    
    // se fija potencia de salida en 17 DBm
    setPotenciaTX(17);  

    // se pone el equipo en standby 
    espera();

    return 1;
}

// reset del transductor LoRa
void LoRa::reset(){
    gpio_put(LORA_RESET,0); 
    sleep_ms(10);
    gpio_put(LORA_RESET,1);
    sleep_ms(10);
}

// modos del trasnductor
// modo dormir
void LoRa::dormir(){
    escribirRegistro(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_SLEEP);
}

// modo espera
void LoRa::espera(){
    escribirRegistro(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODO_ESPERA);
}


// seteo de frecuencia
void LoRa::setFrecuencia(long frecuencia){
    _frecuencia = frecuencia;

    uint64_t frf =((uint64_t)frecuencia << 19) /32000000;

    escribirRegistro(REG_FRF_BMAS, (uint8_t)(frf >> 16));
    escribirRegistro(REG_FRF_MED , (uint8_t)(frf >>  8));
    escribirRegistro(REG_FRF_BMES, (uint8_t)(frf >>  0));

}

//transmicion simple SPI
uint8_t LoRa::transSimple(uint8_t direccion, uint8_t valor){
    uint8_t respuesta;

    gpio_put(PIN_CS, 0);
    spi_write_blocking(SPI_PORT, &direccion, 1);
    spi_write_read_blocking(SPI_PORT, &valor, &respuesta, 1);
    gpio_put(PIN_CS, 1);

    return respuesta;
}

// lectura de un reguistro
uint8_t LoRa::leerRegistro(uint8_t direccion){
    return transSimple(direccion & MAS_SPI_LECTURA, 0x00);
}

// escritura de un reguistro
void LoRa::escribirRegistro(uint8_t direccion, uint8_t valor){
    transSimple(direccion | MAS_SPI_ESCRITURA, valor);
}

// placa utilisada no utilisa salida RFO, utilisa la salida PA BOOSTER
void LoRa::setPotenciaTX(int nivel){

    if(nivel > 17){
        if(nivel > 20 ){
            nivel = 20;
        }

        nivel -= 3;   // se restan 3 para mantener el rango maximo de 17
        escribirRegistro(REG_PA_DAC,0x87); // abilita salida de 20 DBm 
        setOCP(140);   // setea corriente maxima en 140 mA

    }
    else{
        if(nivel < 2){
            nivel = 2;
        }
        escribirRegistro(REG_PA_DAC, 0x84);  // valores por defecto sin boost para salida
        setOCP(100);
    }

    escribirRegistro(REG_PA_CONFIG, 0x80 | (nivel - 2)); // 0x80 es para abilitar salida BOOST
}

// seteo de corrientes maximas
void LoRa::setOCP(uint8_t mA){

    int8_t ocpTrim = 27;

    if (mA <= 120) {
        ocpTrim = (mA - 45) / 5;
    } 
    else if (mA <=240) {
        ocpTrim = (mA + 30) / 10;
    }

    escribirRegistro(REG_OCP, 0x20 | (0x1f & ocpTrim));  //0x20 abilita la proteccion de sobrecorriente y el 0x1f limita el OCP a 23 , limitando la corriente maxima a 200 mA (por catalogo soporta 240 mA)
}