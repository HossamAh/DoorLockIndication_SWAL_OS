#include "Rte_Door_Lock_Indication_SWC.h"

/*file to implement Door_Lock_Indication_SWC Runnables*/
#define LEDON 1
#define LEDOFF 0

void Door_Lock_indication(void)
{
	/*read the Door Sensor*/
	uint8 DoorSensorState  = Rte_IRead_Door_Lock_Indication_SWC_Door_Lock_indication_Runnable_InputState_RPort_Door_State();
	Std_ReturnType result=RTE_E_CSIF_LEDSwitch_E_OK;
	if(DoorSensorState)
	{
		result=Rte_Call_Door_Lock_Indication_SWC_LEDSwitchClient_RPort_LED_Switch (LEDON);
	}
	else
	{
		result=Rte_Call_Door_Lock_Indication_SWC_LEDSwitchClient_RPort_LED_Switch (LEDOFF);
	}
}
