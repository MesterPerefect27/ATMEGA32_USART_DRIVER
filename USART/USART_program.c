/*
 * USART_program.c
 *
 *  Created on: Apr 8, 2022
 *      Author: INTEL
 */
#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"
#include"USART_interface.h"
#include"USART_privet.h"
void (*USART_PtrCallBack[3]) (void)={NULL};
void USART_voidInit(void){
	UCSRB=0b10011000;
	UCSRC=0b10000110;
	UBRRH=0;
	UBRRL=51;
}
void USART_voidSetModes(USART_Configration Copy_structConfig){
	if(Copy_structConfig.Mode==USART_Receiver){
		UCSRB|=(1<<RXEN);
	}else if(Copy_structConfig.Mode==USART_Transmitter){
		UCSRB|=(1<<TXEN);
	}else{
		UCSRB|=(1<<RXEN)|(1<<TXEN);
	}
	if(Copy_structConfig.DataSize==USART_5_bit){
		UCSRB&=~(1<<UCSZ2);
		UCSRC=(1<<URSEL);
		UCSRC&=(~(1<<UCSZ0))&(~(1<<UCSZ1));
	}else if(Copy_structConfig.DataSize==USART_6_bit){
		UCSRB&=~(1<<UCSZ2);
		UCSRC=(1<<URSEL);
		SET_BIT(UCSRC,UCSZ0);
		CLR_BIT(UCSRC,UCSZ1);
	}else if(Copy_structConfig.DataSize==USART_7_bit){
		UCSRB&=~(1<<UCSZ2);
		UCSRC=(1<<URSEL);
		CLR_BIT(UCSRC,UCSZ0);
		SET_BIT(UCSRC,UCSZ1);
	}else if(Copy_structConfig.DataSize==USART_8_bit){
		CLR_BIT(UCSRB,2);
		UCSRC=(1<<URSEL);
		UCSRC|=(1<<UCSZ0)|(1<<UCSZ1);
	}else if(Copy_structConfig.DataSize==USART_9_bit){
		UCSRB|=(1<<UCSZ2);
		UCSRC=(1<<URSEL);
		UCSRC|=(1<<UCSZ0)|(1<<UCSZ1);
	}
	if(Copy_structConfig.Operation==USART_Asynchronous_Operation){
		UCSRC=(1<<URSEL);
		CLR_BIT(UCSRC,UMSEL);
		CLR_BIT(UCSRC,UCPOL);
	}else if(Copy_structConfig.Operation==USART_Synchronous_Operation){
		UCSRC=(1<<URSEL);
		UCSRC|=(1<<UMSEL);
	}
	if(Copy_structConfig.Parity==USART_Disabled_Parity){
		UCSRC=(1<<URSEL);
		CLR_BIT(UCSRC,UPM0);
		CLR_BIT(UCSRC,UPM1);
	}else if(Copy_structConfig.Parity==USART_Even_Parity){
		UCSRC=(1<<URSEL);
		CLR_BIT(UCSRC,UPM0);
		SET_BIT(UCSRC,UPM1);
	}else if(Copy_structConfig.Parity==USART_Odd_Parity){
		UCSRC=(1<<URSEL);
		UCSRC|=(1<<UPM0)|(1<<UPM1);
	}
	if(Copy_structConfig.StopFrame==USART_1_Bit_stop){

		UCSRC=(UCSRC|(1<<URSEL))&(~(1<<USBS));
	}else if(Copy_structConfig.StopFrame==USART_2_Bit_stop){
		UCSRC|=(1<<URSEL)|(1<<USBS);
	}
	if(Copy_structConfig.BaudRate==USART_2400){
		UBRRH=0;
		UBRRL=USART_2400;
	}else if(Copy_structConfig.BaudRate==USART_4800){
		UBRRH=0;
		UBRRL=USART_4800;
	}else if(Copy_structConfig.BaudRate==USART_9600){
		UBRRH=0;
		UBRRL=USART_9600;
	}
	if(Copy_structConfig.Speed==USART_Normal_Speed){
		UCSRA&=(~(1<<U2X));
	}else if(Copy_structConfig.Speed==USART_Double_Speed){
		UCSRA|=(1<<U2X);
	}
	//Disable Interrupt
	UCSRB&=((~(1<<RXCIE))&(~(1<<TXCIE))&(~(1<<UDRIE)));
}
void USART_voidTransimt(U8 Copy_u8Value){
	UDR= Copy_u8Value;
	while(GET_BIT(UCSRA,UDRE)==0);
}
U8   USART_u8Receive(void){
	while(GET_BIT(UCSRA,RXC)==0);
	return UDR;
}
void USART_voidSendString(U8 *Copy_Ptr){
	U8 LOC_Iteration=0;
	while(Copy_Ptr[LOC_Iteration]!='\0'){
		USART_voidTransimt(Copy_Ptr[LOC_Iteration]);
		LOC_Iteration++;
	}
}
U8 String[20];
U8*  USART_ptrReceiveString(void){
	U8 Recive_Chr,Iteration=0;
	while((Recive_Chr=USART_u8Receive())!=13){
		String[Iteration++]=Recive_Chr;
	}
	String[Iteration]='\0';
	return String;
}
void USART_voidEnableRXInterrupt(void){
	UCSRB|=(1<<RXCIE);
}
void USART_voidSetCallBack(void (*copy_ptrvoidCallBack(void)),U8 copy_u8IntLine){
	if(copy_ptrvoidCallBack!=NULL){
		if(copy_u8IntLine==USART_RX_Complete){
			USART_PtrCallBack[copy_u8IntLine]=copy_ptrvoidCallBack;
		}else if(copy_u8IntLine==USART_Data_Empty){
			USART_PtrCallBack[copy_u8IntLine]=copy_ptrvoidCallBack;
		}else{
			USART_PtrCallBack[copy_u8IntLine]=copy_ptrvoidCallBack;
		}
	}
}
void __vector_13(void) __attribute__((signal));
void __vector_13(void){
	if(USART_PtrCallBack[0]!=NULL){
		USART_PtrCallBack[0]();

	}
}
void __vector_14(void) __attribute__((signal));
void __vector_14(void){
	if(USART_PtrCallBack[1]!=NULL){
		USART_PtrCallBack[1]();

	}
}
void __vector_15(void) __attribute__((signal));
void __vector_15(void){
	if(USART_PtrCallBack[2]!=NULL){
		USART_PtrCallBack[2]();
		UCSRA|=(1<<TXC);
	}
}

