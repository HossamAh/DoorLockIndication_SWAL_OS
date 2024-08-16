#include "DIO.h"

#define LED_SET (*(volatile unsigned int*)(0x40020414)) |= (1U << (15))
#define LED_CLEAR (*(volatile unsigned int*)(0x40020414)) &= ~(1U << (15))

#define GPIOA_IDR (*(volatile unsigned int*)(0x40020010)) // GPIOA Input Data Register address
#define READ_DOOR_LOCK ((GPIOA_IDR>>0)&0x01)



#define LEDON	1
#define LEDOFF	0


unsigned char DIO_ReadChannel(unsigned char ID)
{
	return READ_DOOR_LOCK;
//	return MGPIO_GPIO_PinLevelGetPinValue(Port_Used, ID);
}
void DIO_Write(unsigned char ID,unsigned char Level)
{
	if(Level==LEDON)
		LED_SET;
	else
		LED_CLEAR;

//	MGPIO_VoidSetPinValue(Port_Used, ID, Level);
}
