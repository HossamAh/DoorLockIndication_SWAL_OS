#include "MCAL/DIO.h"
#include "Rte_DoorIndication_ECU_Abstraction_SWC.h"
/*file to implement DoorIndication_ECU_Abstraction_SWC Runnables*/

#define LEDON 0
#define LEDOFF 1
void Read_Door_State(void)
{
//	uint8 DoorState = MGPIO_GPIO_PinLevelGetPinValue(Port_Used, Door_Lock);
	uint8 DoorState = DIO_ReadChannel(Door_Lock);
	Rte_IWrite_DoorIndication_ECU_Abstraction_SWC_Read_Door_State_Runnable_DoorState_PPort_Door_State(DoorState);
}

Std_ReturnType LED_Switch(uint8 LED_State)
{
	if(LED_State==LEDON)
	{
		DIO_Write(LED_pin,LEDON);
		return RTE_E_CSIF_LEDSwitch_E_OK;
	}
	else if(LED_State==LEDOFF)
	{
		DIO_Write(LED_pin,LEDOFF);
		return RTE_E_CSIF_LEDSwitch_E_NOT_OK;
	}
	else
		return RTE_E_CSIF_LEDSwitch_E_NOT_OK;
}
