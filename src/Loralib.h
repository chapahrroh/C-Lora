#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"

//mascaras
#define MAS_SPI_ESCRITURA    0x80
#define MAS_SPI_LECTURA      0x7f

//definicion de direcciones de reguistros
#define REG_OP_MODE          0x01
#define REG_FRF_BMAS         0x06
#define REG_FRF_MED          0x07
#define REG_FRF_BMES         0x08
#define REG_FIFO_TX_DIR_BASE 0x0e
#define REG_FIFO_RX_DIR_BASE 0x0f
#define REG_LNA              0x0c
#define REG_MODEM_CONFIG_3   0x26
#define REG_PA_DAC           0x4d
#define REG_OCP              0x0b
#define REG_PA_CONFIG        0x09

//modos
#define MODE_LONG_RANGE_MODE 0x80
#define MODE_SLEEP           0x00
#define MODO_ESPERA          0x01

// declaracion de pines spi
#define PIN_MISO             4
#define PIN_CS               5
#define PIN_SCK              6
#define PIN_MOSI             7
#define LORA_RESET           21
#define SPI_PORT             spi0

class LoRa {

    public:

    //variables de la clase
        long _frecuencia;

    // funciones de la clase
                LoRa();
        uint8_t transSimple(uint8_t direccion, uint8_t valor);
        uint8_t leerRegistro(uint8_t direccion);
        void    escribirRegistro(uint8_t direccion, uint8_t valor);
        void    reset();
        int     iniciarLoRa(long frecuencia);
        void    setFrecuencia(long frecuencia);
        void    setPotenciaTX(int nivel);
        void    setOCP(uint8_t mA);
        void    dormir();
        void    espera();

};



// Constructor de la clase
