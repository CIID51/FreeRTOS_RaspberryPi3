/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

#define portTIMER_PRESCALE 						( ( unsigned long ) 0xF9 )


/* Constants required to setup the VIC for the tick ISR. */
#define portTIMER_BASE                    		( (unsigned long ) 0x3F00B400 )
typedef struct _BCM2835_TIMER_REGS {
	unsigned long LOD;
	unsigned long VAL;
	unsigned long CTL;
	unsigned long CLI;
	unsigned long RIS;
	unsigned long MIS;
	unsigned long RLD;
	unsigned long DIV;
	unsigned long CNT;
} BCM2835_TIMER_REGS;

static volatile BCM2835_TIMER_REGS * const pRegs = (BCM2835_TIMER_REGS *) (portTIMER_BASE);

void vTickISR (unsigned int nIRQ, void *pParam);

vSetupTickInterrupt(){
	// TODO: Configure the timer
	unsigned long ulCompareMatch;
	

	/* Calculate the match value required for our wanted tick rate. */
	ulCompareMatch = 1000000 / configTICK_RATE_HZ;

	/* Protect against divide by zero.  Using an if() statement still results
	in a warning - hence the #if. */
	#if portPRESCALE_VALUE != 0
	{
		ulCompareMatch /= ( portPRESCALE_VALUE + 1 );
	}
	#endif

	irqBlock();

	pRegs->CTL = 0x003E0000;
	pRegs->LOD = 1000 - 1;
	pRegs->RLD = 1000 - 1;
	pRegs->DIV = portTIMER_PRESCALE;
	pRegs->CLI = 0;
	pRegs->CTL = 0x003E00A2;

	irqRegister(64, vTickISR, NULL);

	irqEnable(64);

	irqUnblock();
}
vApplicationIRQHandler( uint32_t ulICCIAR ){	
	// TODO: Configure the IRQHandler
	irqHandler();
}
char _freertos_vector_table;	//TODO





void vTickISR (unsigned int nIRQ, void *pParam)
{
	xTaskIncrementTick();

	#if configUSE_PREEMPTION == 1
	vTaskSwitchContext();
	#endif

	pRegs->CLI = 0;			// Acknowledge the timer interrupt.
}

