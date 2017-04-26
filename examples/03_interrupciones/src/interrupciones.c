/* Copyright 2016, XXXX
 *
 *  * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Blinking Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "interrupciones.h"
/* <= own header */



/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

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
   /* inicializaciones */


	InitLed();
	Init_Switches();

	uint8_t tecla = 1;
	uint8_t ledActual = 1;

	uint64_t velocidad = 2000000;
	uint64_t velocidadMaxima = 2000000;
	uint64_t paso = 200000;
	EncenderLed(ledActual);
   
   /*acá va mi programa principal */
   

    while(1){

    	do
    	{
    	tecla = Read_Switches();
    	Delay(velocidad);
    	CambiarLed(ledActual);
    	}
    	while (tecla == 0);

    	switch(tecla){

		   case TEC1:
		      ApagarLed(ledActual);
		      if(ledActual == 6)
		    	  ledActual = 1;
		      else
		    	  ledActual++;
		      EncenderLed(ledActual);
		      break; /* optional */
		   case TEC2:
			      ApagarLed(ledActual);
			      if(ledActual == 1)
			    	  ledActual = 6;
			      else
			    	  ledActual--;
			      EncenderLed(ledActual);
		      break; /* optional */
		   case TEC3:

		      if(velocidad  <=  paso)
		    	  velocidad == velocidadMaxima;
		      else
		    	  velocidad = velocidad - paso;
		      break; /* optional */
		   case TEC4:
			      if(velocidad + paso > velocidadMaxima)
			    	  velocidad == paso;
			      else
			    	  velocidad = velocidad + paso;
			      break; /* optional */
		   default : break;
		}
    };
    


}


	void Delay(uint64_t sec)
	{
		uint64_t i;
		for(i=0 ; i <= sec ; i++ )
		{}

	}



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

