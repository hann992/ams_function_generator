#include <avr/io.h>
#include <stdlib.h>
// Constants
#define XTAL 16000000

/*************************************************************************
USART initialization.
    Asynchronous mode.
	RX and TX enabled.
	Number of Stop Bits = 1.
	Baud rate = Parameter.
	Data bits = Parameter.
Parameters:
	BaudRate: Wanted Baud Rate (110-115200).
	Databits: Wanted number of Data Bits (5-8).
	Parity: 'E' (Even parity), 'O' (Odd parity), otherwise No Parity.
	Rx_Int: If non-zero, receiver interrupt will be enabled.
*************************************************************************/
void InitUART()
{

   // ENABLE READ WRITE
   UCSR0B = (1<<RXEN0);
   UCSR0B |= (1<<TXEN0);
   
   // Stop bit: 1
   UCSR0C = (0<<3);
   
   // Asynkron
   UCSR0C |= (0<<6)|(0<<7);
   
   // Parity: none
   UCSR0C |= (0<<4)|(0<<5);
   
   // Antal bits: 8
   UCSR0C |= (1<<1)|(1<<2);
   UCSR0B |= (0<<2);
   
   UBRR0 = 103;
  
}

/*************************************************************************
  Returns 0 (FALSE), if the UART has NOT received a new character.
  Returns value <> 0 (TRUE), if the UART HAS received a new character.
*************************************************************************/
unsigned char CharReady()
{
   return UCSR0A & (1<<7);
}

/*************************************************************************
Awaits new character received.
Then this character is returned.
*************************************************************************/
char ReadChar()
{
  // Wait for new character received
  while ( (UCSR0A & (1<<7)) == 0 )
  {}                        
  // Then return it
  return UDR0;
}

/*************************************************************************
Awaits transmitter register ready.
Then send the character.
Parameter :
	Tegn : Character for sending. 
*************************************************************************/
void SendChar(char Tegn)
{
  // Wait for transmitter register empty (ready for new character)
  while ( (UCSR0A & (1<<5)) == 0 )
  {}
  // Then send the character
  UDR0 = Tegn;
}

/*************************************************************************
Sends 0 terminated string.
Parameter:
   Streng: Pointer to the string. 
*************************************************************************/
void SendString(char* Streng)
{
  // Repeat until zero-termination
  while (*Streng != 0)
  {
    // Send the character pointed to by "Streng"
    SendChar(*Streng);
    // Advance the pointer one step
    Streng++;
  }
}

/*************************************************************************
Converts the integer "Tal" to an ASCII string - and then sends this string
using the USART.
Makes use of the C standard library <stdlib.h>.
Parameter:
    Tal: The integer to be converted and sent. 
*************************************************************************/
void SendInteger(int Tal)
{
char array[7];
  // Convert the integer to an ASCII string (array), radix = 10 
  itoa(Tal, array, 10);
  // - then send the string
  SendString(array);
}

/************************************************************************/