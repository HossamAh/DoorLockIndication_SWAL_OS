/*
 * AUTOSAR IN Depth Materials
 * www.learn-in-depth.com
 * Eng.Keroles Shenouda
 * eng.keroles.karam@gmail.com
 *
 */


//    PA15   (*(unsigned int*)(0x40020014)) >> 15
//    PB15   (*(unsigned int*)(0x40020414)) >> 15
//    PC15   (*(unsigned int*)(0x40020814)) >> 15
//    PD15:  (*(unsigned int*)(0x40020C14)) >> 15


#define PA15_red (*(volatile unsigned int*)(0x40020014)) ^= (1U << (15))
#define PB15_blue (*(volatile unsigned int*)(0x40020414)) ^= (1U << (15))
#define PC15_orange (*(volatile unsigned int*)(0x40020814)) ^= (1U << (15))

#define GPIOA_MODER (*(volatile uint32_t*)(0x40020000)) // GPIOA Mode Register address
#define RCC_AHB1ENR (*(volatile uint32_t*)(0x40023830)) // RCC AHB1 peripheral clock enable register address
#define RCC_AHB1ENR_GPIOAEN (1 << 0) // GPIOA clock enable bit

void Rte_Call_Door_Lock_Indication_SWC_LEDSwitchClient_RPort_LED_Switch_SETOIE(unsigned char LED_State);


#include "tp.h"
#include "tpl_os.h"
//simple mydelay function
void mydelay(unsigned int ms)
{
    unsigned int i;
    for(i=0;i<ms;i++)
    {
    }
}
void init_GPIOA_PIN0_as_input(void) {
	// Enable GPIOA clock
	RCC_AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// Configure GPIOA PIN 0 as input (00 in MODER register for pin 0)
	GPIOA_MODER &= ~(3UL << (0 * 2)); // Clear the 2 bits corresponding to pin 0
}

FUNC(int, OS_APPL_CODE) main(void)
{
	initBoard();
	init_GPIOA_PIN0_as_input();
	StartOS(OSDEFAULTAPPMODE);
	return 0;
}

unsigned char LEDState;
//-------------------------------------------
#define APP_Task_ReadDoorT_START_SEC_CODE
#include "tpl_memmap.h"
TASK(ReadDoorT)
{
	while(1)//Extended Task
	{
	//wait on timing event of 10 ms
	WaitEvent(Time_10ms_Event);
	//clear Event
	ClearEvent(Time_10ms_Event);
	//run the ECU Abstract SWC Read Door State Runnable
	Read_Door_State();//state is written in the shared buffer between the two ports
	SetEvent(DoorLockIndicationTask,DoorStateReceivedEvent);
	}
	TerminateTask();
}
#define APP_Task_ReadDoorT_STOP_SEC_CODE
#include "tpl_memmap.h"
//-------------------------------------------

//-------------------------------------------
#define APP_Task_LEDSwitchTask_START_SEC_CODE
#include "tpl_memmap.h"
TASK(LEDSwitchTask)
{
	while(1)//Extended Task
	{
	//wait on OperationInvokedEvent
	WaitEvent(LedSwitchInvokeEvent);
	//clear Event
	ClearEvent(LedSwitchInvokeEvent);
	//run the ECU Abstract SWC LED Switch Runnable with global LED State that APP SWC client call.
	LED_Switch(LEDState);
	}
	TerminateTask();
}
#define APP_Task_LEDSwitchTask_STOP_SEC_CODE
#include "tpl_memmap.h"
//-------------------------------------------

//-------------------------------------------
#define APP_Task_DoorLockIndicationTask_START_SEC_CODE
#include "tpl_memmap.h"
TASK(DoorLockIndicationTask)
{
	while(1)//Extended Task
	{
	//wait on DoorStateReceived Event
	WaitEvent(DoorStateReceivedEvent);
	//clear Event
	ClearEvent(DoorStateReceivedEvent);
	//run the App SWC DoorLockIndication Runnable to read the Door Lock State and take call the server port according.
	Door_Lock_indication();
	}
	TerminateTask();
}
#define APP_Task_DoorLockIndicationTask_STOP_SEC_CODE
#include "tpl_memmap.h"
//-------------------------------------------
void Rte_Call_Door_Lock_Indication_SWC_LEDSwitchClient_RPort_LED_Switch_SETOIE(unsigned char LED_State)
{
	LEDState = LED_State;
	SetEvent(LEDSwitchTask,LedSwitchInvokeEvent);
}



/*
 *  * This is necessary for ST libraries
 *   */
FUNC(void, OS_CODE) assert_failed(uint8_t* file, uint32_t line)
{
}

