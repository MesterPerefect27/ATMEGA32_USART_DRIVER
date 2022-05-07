/*
 * USART_interface.h
 *
 *  Created on: Apr 8, 2022
 *      Author: INTEL
 */

#ifndef MCAL_USART_USART_INTERFACE_H_
#define MCAL_USART_USART_INTERFACE_H_
#define NULL 0
#define USART_RX_Complete 0
#define USART_Data_Empty  1
#define USART_TX_Complete 2

typedef enum{
	USART_Receiver,USART_Transmitter,USART_Receiver_Transmitter
}USART_Modes;
typedef enum{
	USART_5_bit,USART_6_bit,USART_7_bit,USART_8_bit,USART_9_bit=7
}USART_Chr_Size;
typedef enum{
	USART_Asynchronous_Operation, USART_Synchronous_Operation
}USART_Operation;
typedef enum{
	USART_Disabled_Parity,USART_Even_Parity=2,USART_Odd_Parity
}USART_Parity;
typedef enum{
	USART_1_Bit_stop,USART_2_Bit_stop
}USART_Stop_Bits;
typedef enum{
	USART_2400=207,USART_4800=103,USART_9600=51
}USART_Baud_Rate;
typedef enum{
	USART_Normal_Speed,USART_Double_Speed
}USART_Speed;
typedef struct{
	USART_Modes     Mode;
	USART_Chr_Size  DataSize;
	USART_Operation Operation;
	USART_Parity    Parity;
	USART_Stop_Bits StopFrame;
	USART_Baud_Rate BaudRate;
	USART_Speed     Speed;
}USART_Configration;
void USART_voidInit(void);
void USART_voidSetModes(USART_Configration Copy_structConfig);
void USART_voidTransimt(U8 Copy_u8Value);
U8   USART_u8Receive(void);
void USART_voidSendString(U8 *Copy_Ptr);
U8*  USART_ptrReceiveString(void);
void USART_voidEnableRXInterrupt(void);
void USART_voidEnableTXInterrupt(void);
void USART_voidEnableDataEmptyInterrupt(void);
void USART_voidSetCallBack(void(*Copy_PvoidCallBack(void)),U8 copy_u8IntLine);


#endif /* MCAL_USART_USART_INTERFACE_H_ */
