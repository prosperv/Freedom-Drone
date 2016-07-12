/* ###################################################################
**     Filename    : rtos_main_task.c
**     Project     : Drone-RTOS
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-07-04, 14:21, # CodeGen: 16
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         main_task - void main_task(os_task_param_t task_init_data);
**
** ###################################################################*/
/*!
** @file rtos_main_task.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup rtos_main_task_module rtos_main_task module documentation
**  @{
*/         
/* MODULE rtos_main_task */

#include "Cpu.h"
#include "Events.h"
#include "rtos_main_task.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

extern void * g_lpsciStatePtr[UART0_INSTANCE_COUNT];

/* Initialization of Processor Expert components function prototype */
#ifdef MainTask_PEX_RTOS_COMPONENTS_INIT
extern void PEX_components_init(void);
#endif 

/*
** ===================================================================
**     Callback    : main_task
**     Description : Task function entry.
**     Parameters  :
**       task_init_data - OS task parameter
**     Returns : Nothing
** ===================================================================
*/
void main_task(os_task_param_t task_init_data)
{
  /* Write your local variable definition here */
  /* Initialization of Processor Expert components (when some RTOS is active). DON'T REMOVE THIS CODE!!! */
#ifdef MainTask_PEX_RTOS_COMPONENTS_INIT
	PEX_components_init();
#endif 
  /* End of Processor Expert components initialization.  */

	void * xbee = xbee_init();
	bool lastStatus = false;
	lpsci_state_t * lpsciState = (lpsci_state_t *)g_lpsciStatePtr[uartXbee_IDX];
	char rxData = 0;
	char txData = 0;

	print("Starting Main Task\n\r");
#ifdef PEX_USE_RTOS
  while (1) {
#endif
    /* Write your code here ... */
//	  lpsci_status_t result = LPSCI_DRV_ReceiveDataBlocking(uartXbee_IDX, &rxData, 1u, 5000u);
//      if (kStatus_LPSCI_Success == result)
//      {
//          // Echo received character
//    	  txData = rxData;
//          LPSCI_DRV_SendDataBlocking(uartXbee_IDX, &txData, 1u, 1000u);
//      }
//      else
//      {
////    	  print("Error: ");
//    	  printInt(result);
////    	  print("\r\n");
//      }
    OSA_TimeDelay(100);                 /* Example code (for task release) */
	if (xbee_isData() && lastStatus)
	{
//		print("Command Received\n\r");
		short * cmd = xbee_getCMD();
		xbee_deleteCMD(cmd);
		lastStatus = false;
	}
	else if (!lastStatus)
	{
		lastStatus = true;
//		print("No commands\n\r");
	}




   
    
    
    
#ifdef PEX_USE_RTOS   
  }
#endif    
}

/* END rtos_main_task */

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
