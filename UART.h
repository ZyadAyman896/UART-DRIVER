/*
 * UART.h
 *
 * Created: 3/6/2024 9:39:09 PM
 *  Author: Zyad Ayman
 */ 


#ifndef UART_H_
#define UART_H_

#include "std_types.h"





/************************************************************************/
/*                        CONFIGURATIONS                                */
/************************************************************************/




/* These values is calculated for F_CPU = 8 MHZ and U2X = 0 */

#define REG_VAL_BR_9600     ( 51 )

#define REG_VAL_BR_38400    ( 12 )

#define REG_VAL_BR_115200   ( 3  )



/************************************************************************/
/*                        UART REGISTERS                                */
/************************************************************************/

#define UDR   *((volatile u8 *)0x2C)
#define UCSRB *((volatile u8 *)0x2A)
#define UCSRA *((volatile u8 *)0x2B)
#define UBRRL *((volatile u8 *)0x29)
#define UBRRH *((volatile u8 *)0x40)
#define UCSRC *((volatile u8 *)0x40)

/************************************************************************/
/*                        UART REGISTER's bit masks                     */
/************************************************************************/
/* ======================= UCSRA ======================= */

#define RXC     7    // Receive Complete
#define TXC     6    // Transmit Complete
#define UDRE    5    // Data Register Empty
#define FE      4    // Frame Error
#define DOR     3    // Data OverRun
#define PE      2    // Parity Error
#define U2X     1    // Double Speed
#define MPCM    0    // Multi-Processor Communication Mode

/* ======================= UCSRB ======================= */

#define RXCIE   7    // RX Complete Interrupt Enable
#define TXCIE   6    // TX Complete Interrupt Enable
#define UDRIE   5    // Data Register Empty Interrupt Enable
#define RXEN    4    // Receiver Enable
#define TXEN    3    // Transmitter Enable
#define UCSZ2   2    // Character Size bit 2
#define RXB8    1    // Receive Data Bit 8
#define TXB8    0    // Transmit Data Bit 8

/* ======================= UCSRC ======================= */

#define URSEL   7    // Register Select (1 = UCSRC)
#define UMSEL   6    // USART Mode Select (0 = Async)
#define UPM1    5    // Parity Mode bit 1
#define UPM0    4    // Parity Mode bit 0
#define USBS    3    // Stop Bit Select
#define UCSZ1   2    // Character Size bit 1
#define UCSZ0   1    // Character Size bit 0
#define UCPOL   0    // Clock Polarity (sync only)


/* ======================= UBRRH ======================= */
// URSEL must be 0 to write to UBRRH
// UBRRH uses bits 0–3 for UBRR[11:8]

#define UBRRH_MASK  0x0F

/* ======================= UBRRL ======================= */
// UBRR[7:0] in UBRRL

#define UBRRL_MASK  0xFF


/************************************************************************/
/*                        Function Prototypes                           */
/************************************************************************/




void UART_vInit(u32 Baud_Rate);

void UART_vSendData(u8 copy_u8Data);

void UART_vSendString(Pu8 Ptr);

void UART_vDisable_Flow_Control();

void UART_vEnable_Flow_Control();

u8 UART_u8GetData(void);



#endif /* UART_H_ */