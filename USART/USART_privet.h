/*
 * USART_privet.h
 *
 *  Created on: Apr 8, 2022
 *      Author: INTEL
 */

#ifndef MCAL_USART_USART_PRIVET_H_
#define MCAL_USART_USART_PRIVET_H_

#define UDR   *((volatile U8*)0X2C)
#define UCSRA *((volatile U8*)0X2B)
#define UCSRB *((volatile U8*)0X2A)
#define UCSRC *((volatile U8*)0X40)
#define UBRRL *((volatile U8*)0X29)
#define UBRRH *((volatile U8*)0X40)
/*UCSRA_REG*/
#define RXC   7
#define TXC   6
#define UDRE  5
#define FE    4
#define DOR   3
#define PE    2
#define U2X   1
#define MPCM  0
/*UCSRB_REG*/
#define RXCIE 7
#define TXCIE 6
#define UDRIE 5
#define RXEN  4
#define TXEN  3
#define UCSZ2 2
#define RXB8  1
#define TXB8  0
/*UCSRC_REG*/
#define URSEL  7
#define UMSEL  6
#define UPM1   5
#define UPM0   4
#define USBS   3
#define UCSZ1  2
#define UCSZ0  1
#define UCPOL  0

#endif /* MCAL_USART_USART_PRIVET_H_ */
