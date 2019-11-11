#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef _NRF24L01_H
#define _NRF24L01_H

// SPI Commands

#define R_REGISTER          0x00 // 000A AAAA
#define W_REGISTER          0x20 // 001A AAAA
#define R_RX_PAYLOAD        0x61 // 0110 0001
#define W_TX_PAYLOAD        0xA0 // 1010 0000
#define FLUSH_TX            0xE1 // 1110 0001
#define FLUSH_RX            0xE2 // 1110 0010
#define REUSE_TX_PL         0xE3 // 1110 0011
#define R_RX_PL_WID         0x60 // 0110 0000
#define W_ACK_PAYLOAD       0xA8 // 1010 1PPP
#define W_TX_PAYLOAD_NOACK  0xB0 // 1011 0000
#define NOP                 0xFF // 1111 1111


// Register Map

#define CONFIG      0x00
#define MASK_RX_DR  6
#define MASK_TX_DS  5
#define MASK_MAX_RT 4
#define EN_CRC      3
#define CRCO        2
#define PWR_UP      1
#define PRIM_RX     0

#define EN_AA       0x01
#define ENAA_P5     5
#define ENAA_P4     4
#define ENAA_P3     3
#define ENAA_P2     2
#define ENAA_P1     1
#define ENAA_P0     0

#define EN_RXADDR   0x02
#define ERX_P5      5
#define ERX_P4      4
#define ERX_P3      3
#define ERX_P2      2
#define ERX_P1      1
#define ERX_P0      0

#define SETUP_AW    0x03
#define AW          0

#define SETUP_RETR  0x04
#define ARD         4
#define ARC         0

#define RF_CH       0x05

#define RF_SETUP    0x06
#define CONT_WAVE   7
#define RF_DR_LOW   5
#define PLL_LOCK    4
#define RF_DR_HIGH  3
#define RF_PWR      1

#define STATUS              0x07
#define RX_DR               6
#define TX_DS               5
#define MAX_RT              4
#define RX_P_NO_MASK        0x0E
#define STATUS_TX_FULL      0

#define OBSERVE_TX  0x08
#define PLOS_CNT    4
#define ARC_CNT     0

#define RPD         0x09

#define RX_ADDR_P0  0x0A
#define RX_ADDR_P1  0x0B
#define RX_ADDR_P2  0x0C
#define RX_ADDR_P3  0x0D
#define RX_ADDR_P4  0x0E
#define RX_ADDR_P5  0x0F

#define TX_ADDR     0x10

#define RX_PW_P0    0x11
#define RX_PW_P1    0x12
#define RX_PW_P2    0x13
#define RX_PW_P3    0x14
#define RX_PW_P4    0x15
#define RX_PW_P5    0x16

#define FIFO_STATUS         0x17
#define TX_REUSE            6
#define FIFO_TX_FULL        5
#define TX_EMPTY            4
#define RX_FULL             1
#define RX_EMPTY            0

#define DYNPD       0x1C
#define DPL_P5      5
#define DPL_P4      4
#define DPL_P3      3
#define DPL_P2      2
#define DPL_P1      1
#define DPL_P0      0

#define FEATURE     0x1D
#define EN_DPL      2
#define EN_ACK_PAY  1
#define EN_DYN_ACK  0


typedef struct {
    int pipe_number;
    uint8_t data[32];
    uint8_t length;
} nRF24L01Message;

typedef struct {
    volatile uint8_t *port;
    uint8_t pin;
} gpio_pin;

typedef struct {
    gpio_pin ss; // slave select
    gpio_pin ce; // chip enabled
    gpio_pin sck; // serial clock
    gpio_pin mosi; // master out slave in
    gpio_pin miso; // master in slave out
    uint8_t status;
} nRF24L01;


nRF24L01 *nRF24L01_init(void);
void nRF24L01_begin(nRF24L01 *rf);
uint8_t nRF24L01_send_command(nRF24L01 *rf, uint8_t command, void *data,
    size_t length);
uint8_t nRF24L01_write_register(nRF24L01 *rf, uint8_t reg_address, void *data,
    size_t length);
uint8_t nRF24L01_read_register(nRF24L01 *rf, uint8_t regAddress, void *data,
    size_t length);
uint8_t nRF24L01_no_op(nRF24L01 *rf);
uint8_t nRF24L01_update_status(nRF24L01 *rf);
uint8_t nRF24L01_get_status(nRF24L01 *rf);
void nRF24L01_listen(nRF24L01 *rf, int pipe, uint8_t *address);
bool nRF24L01_data_received(nRF24L01 *rf);
bool nRF24L01_read_received_data(nRF24L01 *rf, nRF24L01Message *message);
int nRF24L01_pipe_number_received(nRF24L01 *rf);
void nRF24L01_transmit(nRF24L01 *rf, void *address, nRF24L01Message *msg);
int nRF24L01_transmit_success(nRF24L01 *rf);
void nRF24L01_flush_transmit_message(nRF24L01 *rf);
void nRF24L01_retry_transmit(nRF24L01 *rf);
void nRF24L01_clear_interrupts(nRF24L01 *rf);
void nRF24L01_clear_transmit_interrupts(nRF24L01 *rf);
void nRF24L01_clear_receive_interrupt(nRF24L01 *rf);

#endif
