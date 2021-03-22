#define F_CPU 1000000UL

/*
 * This file contains methods that can be used to control the ATTiny841 board
 */

void USART0_Init( unsigned int baud ) {
  /* Set baud rate */
  UBRR0H = (unsigned char) (baud>>8);
  UBRR0L = (unsigned char) baud;
  
  // enable USART Receive Complete interrupts
  //RXCIE0 = 1;
  
  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART1_Init( unsigned int baud ) {
  /* Set baud rate */
  UBRR1H = (unsigned char) (baud>>8);
  UBRR1L = (unsigned char) baud;

  // enable USART Receive Complete interrupts
  //RXCIE1 = 1;
  
  /* Enable receiver and transmitter */
  UCSR1B = (1<<RXEN1)|(1<<TXEN1);
  /* Set frame format: 8data, 2stop bit */
  UCSR1C = (1<<USBS1)|(3<<UCSZ10);
}

void USART0_Transmit( unsigned char data ) {
  /* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) );
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

void USART1_Transmit( unsigned char data ) {
  /* Wait for empty transmit buffer */
  while ( !( UCSR1A & (1<<UDRE1)) );
  /* Put data into buffer, sends the data */
  UDR1 = data;
}

unsigned char USART0_Receive( void ) {
  /* Wait for data to be received */
  while ( !(UCSR0A & (1<<RXC0)) );
  /* Get and return received data from buffer */
  return UDR0;
}

unsigned char USART1_Receive( void ) {
  /* Wait for data to be received */
  while ( !(UCSR1A & (1<<RXC1)) );
  /* Get and return received data from buffer */
  return UDR1;
}
