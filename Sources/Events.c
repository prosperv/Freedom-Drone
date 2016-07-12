/* ###################################################################
**     Filename    : Events.c
**     Project     : Drone-RTOS
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-06-30, 21:37, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "rtos_main_task.h"
//#include "Xbee\Xbee.hpp"

void xbee_callback(void *xbee);

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

uint8_t uart_rxbuff[1];

/*
** ===================================================================
**     Callback    : uartXbee_RxCallback
**     Description : This callback occurs when data are received.
**     Parameters  :
**       instance - The LPSCI instance number.
**       lpsciState - A pointer to the LPSCI driver state structure
**       memory.
**     Returns : Nothing
** ===================================================================
*/
void uartXbee_RxCallback(uint32_t instance, void * lpsciState)
{
	// Use lpsci_state_t for lpsciState
//	UART0_Type * base = g_lpsciBase[instance];
//	lpsci_state_t * state = (lpsci_state_t *) lpsciState;
    LPSCI_DRV_SendData(uartXbee_IDX,uart_rxbuff,1);
	xbee_callback(uart_rxbuff[0]);
//	while ((UART0_BRD_C2_RIE(base)) && (UART0_BRD_S1_RDRF(base)))
//	{
//        LPSCI_HAL_Getchar(instance, state->rxBuff);
//		xbee_callback(state->rxBuff[0]);
//	}
//	state->rxBuff = uart_rxbuff;
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
