#ifndef LORALIB_H
#define LORALIB_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"

namespace InverLoRa
{
    namespace nodo
    {

        //mascaras
        #define MAS_SPI_ESCRITURA    0x80
        #define MAS_SPI_LECTURA      0x7f
        #define MAS_IRQ_TX_DONE      0x08

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
        #define REG_MAPEO_DIO_1      0x40
        #define REG_VANDERA_IRQ      0x12
        #define REG_MODEM_CONFIG_1   0x1d
        #define REG_IMAGE_CAL        0x3b //registro de control de temperatura
        #define REG_TEMP             0x3c //registro de temperatura

        //modos LoRa
        #define MODE_LONG_RANGE_MODE 0x80 //modo LoRa
        #define MODE_SLEEP           0x00
        #define MODO_ESPERA          0x01
        #define MODO_TX              0x03
        //modos FSK/OOK
        #define MODO_FSK             0x00 //modo FSK
        #define MODO_FS_RX           0x04

        // declaracion de pines spi
        #define PIN_MISO             4
        #define PIN_CS               5
        #define PIN_SCK              6
        #define PIN_MOSI             7
        #define LORA_RESET           21
        #define LORA_DIO0            26
        #define SPI_PORT             spi0

        class LoRa {

            public:

            //variables de la clase

            // funciones de la clase
                LoRa(); // constructor

                bool     iniciarLoRa(long frecuencia);
                void    terminarLoRa();

                uint8_t transSimple(uint8_t direccion, uint8_t valor);
                uint8_t leerRegistro(uint8_t direccion);
                void    escribirRegistro(uint8_t direccion, uint8_t valor);
                void    reset();
                void    resetFIFO();
                void    setFrecuencia(long frecuencia);
                void    setPotenciaTX(int nivel);
                void    setOCP(uint8_t mA);
                bool    crearPaquete(int cabeseraImplicita);
                bool    finalizarPaquete(bool async);
                bool    transmitiendo();
                int   tempSX1276();

                // modos LoRa
                void    dormir(uint8_t modo);
                void    espera(uint8_t modo);
                void    modoCabeseraExplicita();
                void    modoCabeseraImplicita();

                // modos FSK/OOK
                void   modoFsRx();

            private:
                spi_inst_t *_spi;
                long _frecuencia;
                uint8_t  _reset;
                uint8_t  _cs;
                uint8_t  _dio0;

                bool _cabeseraImplicita;

                void (*_onTxDone)();

        };

        // extern LoRa lora;
    }
}
// extern LoRa lora;
#endif