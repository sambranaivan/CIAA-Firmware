/*
 * FatFS Test program
 *
 * This file contains the support functions for ChaN's FatFS
 * on the lpc1769 module
 *
 * (c) Rob Jansen
 *
 * This software is free software, you may use it, enhance it
 * and share it as long as you like as long as this copyright
 * message stays in place.
 */

#include "../SDLib/diskio.h"
#include "../SDLib/ff.h"
#include "LPC17xx.h"

/*
 * This is a user changeable value for the disk_timerproc() function.
 * It is used by the SysTick_Handler to determine if the SD guard timers
 * need to be incremented.
 * By default this is set to 10 which results in a 10 ms resolution
 * of the Timer1 and Timer2 guard timers in sd.c
 * But I have found that there are sometimes timeouts while writing
 * data towards the SD card. By relaxing the timerproc_interval
 * it is possible to look for an acceptable value.
 *
 * I found that in my case the error exists in SD_SendDataBlock()
 * where a timeout occurs while waiting for write completion.
 */
uint32_t timerproc_interval = 10;

/*
 * User provided RTC function for FatFs.
 *
 * This is a real time clock service to be called from FatFs.
 *
 * This function reads the RTC from the lpc17xx in order
 * to generate a valid time.
 */
DWORD get_fattime ()
{
	/* Pack date and time into a DWORD variable */
	return	  ((DWORD)(LPC_RTC->YEAR - 1980) << 25)
			| ((DWORD)LPC_RTC->MONTH << 21)
			| ((DWORD)LPC_RTC->DOM << 16)
			| ((DWORD)LPC_RTC->HOUR << 11)
			| ((DWORD)LPC_RTC->MIN << 5)
			| ((DWORD)LPC_RTC->SEC >> 1);

}

/*
 * SysTick_Handler
 *
 * This is the Sysick handler that is being called every 1 ms
 * Here it only calls the disk_timerproc() for the SD guard timers
 *
 * This function is being called every SysTick interrupt
 * at a 1 ms interval but the disk_timerproc() function in FatFS
 * should be called only every 10 ms.
 */

/*
void SysTick_Handler(void)
{
	static uint32_t div10 = 0;

	if(++div10 >= timerproc_interval)
	{
		div10 = 0;
		disk_timerproc();
	}
}
*/
