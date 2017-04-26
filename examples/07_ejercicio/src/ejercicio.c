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
#include "ejercicio.h"
#define OK "\n\rMensaje RECIBIDO"
#define KO "\n\rMensaje NO RECIBIDO"
#define ESPERA 1000000
#define INTERPLAP 100000
#define MICROACTUAL 10000
#define ESPERA_APLAUSO 25000


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

uint8_t soyElQueSoy = 0;
uint8_t loQueEscuche = 0;
uint8_t loQueRecibiDelMaestro= 0;
uint64_t loQueRecibiDelEsclavo = 0;

int main(void)
{
   /* inicializaciones */


	InitLed();
	Init_Switches();
	init_UART_RS232_EDUCIAA();
	init_UART_FTDI_EDUCIAA();
	InitMic();

	uint8_t tecla = 0;


    while(1)
    {

    	/*Iniciar MAESTRO o ESCLAVO*/
    	while ((tecla == 0)&&!soyElQueSoy)
    	{
  		    tecla = Read_Switches();

    	}

    	soyElQueSoy=tecla;//elijo una vez el modo y después lo recuerdo.

    	switch(tecla){
		   case TEC1:
		   case TEC2:
			      EncenderLed(LED_ROJO);
			      Maestro();
			      break;
		   case TEC3:
		   case TEC4:
				  EncenderLed(LED_VERDE);
				  Esclavo();
				  break;
		   default:break;
    	}

    }
    

}

void Maestro()
{
	while(loQueEscuche==0)//Espero del Microfono
	{
		EscucharMicrofono();

	}

	HablarAlEsclavo(loQueEscuche);//Microfono
	EscucharAlEsclavo();

	loQueEscuche=0;//Reinicio para escuchar el Microfono
	//TODO ERROR
}

void Esclavo()
{
	while(loQueRecibiDelMaestro==0)
	{
		EscucharAlMaestro();
	}

	HablarAlMaestro(loQueRecibiDelMaestro);
	loQueRecibiDelMaestro=0;


}

void EscucharMicrofono()
{

	while(!ReadMic())
	{

	}
	//Delay para esperar el fin del aplauso
	 int i=0;
	 while(i<=ESPERA_APLAUSO)
	 	{
	 		i++;
	 	}
	 //Un aplauso
	 int aplausos = ReadMic();
	 i=0;
	 while(i<=ESPERA_APLAUSO)
	 	{
	 		i++;
	 	}
	 //Dos aplausos
	  aplausos = aplausos+ReadMic();
	 i=0;

	 while(i<=ESPERA_APLAUSO)
	 	{
	 		i++;
	 	}
	 //Tres aplausos
	  aplausos = aplausos+ReadMic();

	  switch(aplausos)
	  	{
	  		case 0:loQueEscuche = 0;sendString_UART_USB_EDUCIAA("\n\rNO RECIBIDO",20);break;
	  		case 1:loQueEscuche = 65;sendString_UART_USB_EDUCIAA("\n\rLED 1 ACTIVADO. UN APLAUSO",30);break;
	  		case 2:loQueEscuche = 66;sendString_UART_USB_EDUCIAA("\n\rLED 2 ACTIVADO. DOS APLAUSOS",30);break;
	  		case 3:loQueEscuche = 67;sendString_UART_USB_EDUCIAA("\n\rLED 3 ACTIVADO. TRES APLAUSOS",30);break;
	  		default: loQueEscuche =  67;sendString_UART_USB_EDUCIAA("\n\rLED 3 ACTIVADO. TRES APLAUSOS",30);break;
	  		}


}



void EscucharAlEsclavo()
{
	//escuchar desde el RS232
	int i=0;
	do
	{
		loQueRecibiDelEsclavo = readByte_UART_RS232_EDUCIAA();
		i++;
	}while((loQueRecibiDelEsclavo==0)&&(i<ESPERA));

	if(i>=ESPERA)
	{
		sendString_UART_USB_EDUCIAA("\n\rESCLAVO NO RESPONDE",20);
	}
	else
	{
		if(loQueRecibiDelEsclavo == loQueEscuche)
			{sendString_UART_USB_EDUCIAA(OK,20);EncenderLed(LED_VERDE);}
		else
		{
			EncenderLed(LED_ROJO);
			sendString_UART_USB_EDUCIAA(KO,20);
			sendString_UART_USB_EDUCIAA("\n\r",2);
			sendString_UART_USB_EDUCIAA("Enviado: ",9);
			sendString_UART_USB_EDUCIAA(Itoa(loQueEscuche,10),2);
			sendString_UART_USB_EDUCIAA("\n\r",2);
			sendString_UART_USB_EDUCIAA("Recibido: ",10);
			sendString_UART_USB_EDUCIAA(Itoa(loQueRecibiDelEsclavo,10),2);
			sendString_UART_USB_EDUCIAA("\n\r============",15);
		}

	}
	loQueRecibiDelEsclavo =0;
	ApagarLed(LED1);ApagarLed(LED2);ApagarLed(LED3);
}

void EscucharAlMaestro()
{
	//escuchar desde el RS232
	loQueRecibiDelMaestro = readByte_UART_RS232_EDUCIAA();
	sendString_UART_USB_EDUCIAA("\n\r",10);
	sendString_UART_USB_EDUCIAA(Itoa(loQueRecibiDelMaestro,10),10);
	//Encender Led enviado
		switch(loQueRecibiDelMaestro){

				   case 65:
					  ApagarLed(LED2);
					  ApagarLed(LED3);
				      EncenderLed(LED1);
				      break;
				   case 66:
					  ApagarLed(LED1);
					  ApagarLed(LED3);
					  EncenderLed(LED2);
					  break;
				   case 67:
					  ApagarLed(LED1);
					  ApagarLed(LED2);
				      EncenderLed(LED3);
				      break;
				   default : break;
				}

}

void HablarAlMaestro(uint8_t dato)
{

		// Enviar dato
		writeByte_UART_RS232_EDUCIAA(dato);
}
//El maestro habla con el esclavo, enciende el LED enviado
void HablarAlEsclavo(uint8_t dato)
{


	//Encender Led enviado
	switch(dato){

			   case 65:
				  ApagarLed(LED2);
				  ApagarLed(LED3);
			      EncenderLed(LED1);
			      break;
			   case 66:
				  ApagarLed(LED1);
				  ApagarLed(LED3);
				  EncenderLed(LED2);
				  break;
			   case 67:
				  ApagarLed(LED1);
				  ApagarLed(LED2);
			      EncenderLed(LED3);
			      break;
			   default : break;
			}
	// Enviar dato
	writeByte_UART_RS232_EDUCIAA(dato);


}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

