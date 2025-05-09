/*
 * UART.c
 *
 * Created: 3/6/2024 9:38:53 PM
 *  Author: Zyad Ayman
 */ 

#include "UART.h"
#include "DIO.h"
#include "Utils.h"


void UART_vInit(u32 Baud_Rate)
{
	/*	Enable Tx & Rx	*/
	
	UCSRB = (1 << RXEN) | (1 << TXEN) ;
	
	/* No Parity, 8 Bit, Async, 1 Stop Bit, CLK Polarity = Rising at TX & Falling at RX */
	
	SET_PIN(UCSRC, URSEL);
	CLR_PIN(UCSRC, UMSEL);  // Asynchronous mode
	CLR_PIN(UCSRC, UPM0);   // No parity
	CLR_PIN(UCSRC, UPM1);
	CLR_PIN(UCSRC, USBS);   // 1 Stop bit
	SET_PIN(UCSRC, UCSZ0);  // 8 Data bits
	SET_PIN(UCSRC, UCSZ1);
	CLR_PIN(UCSRC, UCPOL);  // Rising edge at TX, falling edge at RX

	/* Baud Rate = CONFIGURABLE, F_CPU = 8 MHz */
	if (Baud_Rate == 9600)
	{
		UBRRH = (REG_VAL_BR_9600 >> 8);
		UBRRL = (REG_VAL_BR_9600 & 0xFF);
	}
	else if (Baud_Rate == 38400)
	{
		UBRRH = (REG_VAL_BR_38400 >> 8);
		UBRRL = (REG_VAL_BR_38400 & 0xFF);
	}
	else if (Baud_Rate == 115200)
	{
		UBRRH = (REG_VAL_BR_115200 >> 8);
		UBRRL = (REG_VAL_BR_115200 & 0xFF);
	}

}


void UART_vSendData( u8 copy_u8Data )
{
	while( READ_PIN( UCSRA , PIN_NO_5 ) == 0 );

	UDR = copy_u8Data ;
	
}


u8 UART_u8GetData(void)
{

	while(READ_PIN(UCSRA,PIN_NO_7) == 0);

	return READ_WHOLE_REG(UDR);
}


void UART_vSendString( Pu8 Pointer )
{
	while( *Pointer != '\0' )
	{
		UART_vSendData( *Pointer ) ;
		
		Pointer++ ;
	}

}

/*	Those Functions to make handshaking algorithm */

/*	Function to enable UART flow control	*/ 

void UART_vEnable_Flow_Control() {

	/*	Configure RTS and CTS pins as outputs/inputs	*/ 
	/*	CTS pin as input	*/

	DIO_vSet_Pin_Direction('d',PIN_NO_2,INPUT);
	
	/*	RTS pin as output	*/ 
	DIO_vSet_Pin_Direction('d',PIN_NO_3,OUTPUT);

}

/*	Function to disable UART flow control 	*/ 
void UART_vDisable_Flow_Control() {
	// Restore RTS pin as input (disable flow control)
	DIO_vSet_Pin_Direction('d',PIN_NO_3,INPUT);
}