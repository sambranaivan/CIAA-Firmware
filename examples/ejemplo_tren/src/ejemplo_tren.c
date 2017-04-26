/*==================[inclusions]=============================================*/
#include "os.h"               /* <= operating system header */
#include "ciaaPOSIX_stdio.h"  /* <= device handler header */
#include "ciaaPOSIX_string.h" /* <= string header */
#include "ciaak.h"            /* <= ciaa kernel header */
#include "blinking.h"         /* <= own header */
#include "tren.h"         /* <= own header */
#include "myLedDriver.h"         /* <= own header */
#include "myInputDriver.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/** \brief File descriptor for digital output ports
 *
 * Device path /dev/dio/out/0
 */
static int32_t fd_out, fd_in,blink;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
void LED_ON(uint8 led)
{

ciaaPOSIX_write(fd_out,&led,1);
}

void updateSensor(uint8 in)
{
   if ((in&(BUTTON_1|BUTTON_2|BUTTON_3))== 0)
  {
    SENSOR = 7;
  }
  else if ((in&(BUTTON_1|BUTTON_2))== 0)
  {
    SENSOR = 6;
  }
else if ((in&(BUTTON_1|BUTTON_3))== 0)
  {
    SENSOR = 5;
  }
else if ((in&(BUTTON_2|BUTTON_3))== 0)
  {
   SENSOR = 3; 
  }
else if ((in&(BUTTON_3))== 0)
  {
    SENSOR = 1;
  }
else if ((in&(BUTTON_2))== 0)
  {
    SENSOR = 2;
  }
else if ((in&(BUTTON_1))== 0)//100
  {
    SENSOR = 4;
  }
else 
  // if ((inputs&0x0)== 0)
  {
    SENSOR = 0;
  }

//callback
  update_STATE();
}

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */
int main(void)
{
   /* Starts the operating system in the Application Mode 1 */
   /* This example has only one Application Mode */
   StartOS(AppMode1);

   /* StartOs shall never returns, but to avoid compiler warnings or errors
    * 0 is returned */
   return 0;
}

/** \brief Error Hook function
 *
 * This fucntion is called from the os if an os interface (API) returns an
 * error. Is for debugging proposes. If called this function triggers a
 * ShutdownOs which ends in a while(1).
 *
 * The values:
 *    OSErrorGetServiceId
 *    OSErrorGetParam1
 *    OSErrorGetParam2
 *    OSErrorGetParam3
 *    OSErrorGetRet
 *
 * will provide you the interface, the input parameters and the returned value.
 * For more details see the OSEK specification:
 * http://portal.osek-vdx.org/files/pdf/specs/os223.pdf
 *
 */
void ErrorHook(void)
{
   ciaaPOSIX_printf("ErrorHook was called\n");
   ciaaPOSIX_printf("Service: %d, P1: %d, P2: %d, P3: %d, RET: %d\n", OSErrorGetServiceId(), OSErrorGetParam1(), OSErrorGetParam2(), OSErrorGetParam3(), OSErrorGetRet());
   ShutdownOS(0);
}

/** \brief Initial task
 *
 * This task is started automatically in the application mode 1.
 */
TASK(InitTask)
{
   /* init CIAA kernel and devices */
   ciaak_start();

   /* print message (only on x86) */
   ciaaPOSIX_printf("Init Task...\n");
   
   /* open CIAA digital outputs */
   fd_out = ciaaPOSIX_open("/dev/dio/out/0", ciaaPOSIX_O_RDWR);
   fd_in = ciaaPOSIX_open("/dev/dio/in/0", ciaaPOSIX_O_RDONLY);
   blink = 0;
   /* activate periodic task:
    *  - for the first time after 350 ticks (350 ms)
    *  - and then every 250 ticks (250 ms)
    */
   SetRelAlarm(ActivatePeriodicTask, 350, 50);//blink
   SetRelAlarm(ActivateEscuchaTecla, 1, 10);
   /* terminate task */
   TerminateTask();
}

/** \brief Periodic Task
 *
 * This task is started automatically every time that the alarm
 * ActivatePeriodicTask expires.
 *
 */
TASK(PeriodicTask)
{
   uint8  outputs;
   if ((blink == 1) )
   {

   /* blink output */
   ciaaPOSIX_read(fd_out, &outputs, 1);
   outputs ^= RED_LED;
   ciaaPOSIX_write(fd_out, &outputs, 1);

 }

   TerminateTask();
}


TASK(EscuchaTeclas)
{
  
  uint8 inputs;
  uint8  led;
  ciaaPOSIX_read(fd_in, &inputs,1);
  // inputs = ~inputs;//logical shift
  // ((inputs&0x01) == 0)//apreto 3
  updateSensor(inputs);

  ///LED MANAGER

  switch(STATE)
  {
    case 0:
    LED_ON(GREEN_LED);
    break;
    case 1:
    LED_ON(RED_LED);
    break;
     case 2:
    LED_ON(RED_LED);
    break;
    case 3:
    LED_ON(RED_LED);
    break;
    case 4:
    LED_ON(YELLOW_LED);
    break;
    case 5:
    LED_ON((RGB_RED_LED|RED_LED));//FALLA EN SENSORES
    blink = 1;
    break;
    case 6:
    LED_ON(RED_LED);
    break;
    case 7:
    LED_ON(RED_LED);
    break;
    case 8:
    LED_ON(YELLOW_LED);
    break;
    case 9:
    LED_ON(RED_LED);
    break;
    case 10:
    LED_ON(ALL_LED);//ESTADO DE FALLA TOTAL
    break;

  }
 



  TerminateTask();
}



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

