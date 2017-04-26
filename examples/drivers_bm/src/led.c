/* Copyright 2016, XXXXXXXXX  
 * All rights reserved.
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

/** \brief Blinking Bare Metal driver led
 **
 **
 **
 **/
/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal LED Driver
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

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif

#include "led.h"

/*==================[macros and definitions]=================================*/

// P2_10 GPIO0[14]
#define LED1_MUX_PORT 2
#define LED1_MUX_PIN 10
#define LED1_PUERTO_GPIO 0
#define LED1_BIT_GPIO 14

#define LED2_MUX_PORT 2
#define LED2_MUX_PIN 11
#define LED2_PUERTO_GPIO 1
#define LED2_BIT_GPIO 11

#define LED3_MUX_PORT 2
#define LED3_MUX_PIN 12
#define LED3_PUERTO_GPIO 1
#define LED3_BIT_GPIO 12

// LED DE LA PROTO 
// P6_1 GPIO3[0]
#define PROTO_MUX_PORT 6
#define PROTO_MUX_PIN 1
#define PROTO_PUERTO_GPIO 3
#define PROTO_BIT_GPIO 0
// P6 12 GPIO2[8]

#define LED_GPIO8_MUX_PORT 6
#define LED_GPIO8_MUX_PIN 12
#define LED_GPIO8_PUERTO_GPIO 2
#define LED_GPIO8_BIT_GPIO 8

#define LEDR_MUX_PORT 2
#define LEDR_MUX_PIN 0
#define LEDR_PUERTO_GPIO 5
#define LEDR_BIT_GPIO 0

#define LEDG_MUX_PORT 2
#define LEDG_MUX_PIN 1
#define LEDG_PUERTO_GPIO 5
#define LEDG_BIT_GPIO 1

#define LEDB_MUX_PORT 2
#define LEDB_MUX_PIN 2
#define LEDB_PUERTO_GPIO 5
#define LEDB_BIT_GPIO 2

#define OUTPUT_DIRECTION 1
#define INPUT_DIRECTION 0



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
void InitLed(void)
{
	 Chip_GPIO_Init(LPC_GPIO_PORT); //LPC_GPIO_PORT ya definido en chip.h


	Chip_SCU_PinMux(LED1_MUX_PORT,LED1_MUX_PIN,MD_PUP,FUNC0);
	Chip_SCU_PinMux(LED2_MUX_PORT,LED2_MUX_PIN,MD_PUP,FUNC0);
	Chip_SCU_PinMux(LED3_MUX_PORT,LED3_MUX_PIN,MD_PUP,FUNC0);
	Chip_SCU_PinMux(LEDR_MUX_PORT,LEDR_MUX_PIN,MD_PUP,FUNC4);
	Chip_SCU_PinMux(LEDG_MUX_PORT,LEDG_MUX_PIN,MD_PUP,FUNC4);
	Chip_SCU_PinMux(LEDB_MUX_PORT,LEDB_MUX_PIN,MD_PUP,FUNC4);

	Chip_GPIO_SetDir(LPC_GPIO_PORT, LED1_PUERTO_GPIO,1<<LED1_BIT_GPIO,OUTPUT_DIRECTION);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LED2_PUERTO_GPIO,1<<LED2_BIT_GPIO,OUTPUT_DIRECTION);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LED3_PUERTO_GPIO,1<<LED3_BIT_GPIO,OUTPUT_DIRECTION);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LEDR_PUERTO_GPIO,1<<LEDR_BIT_GPIO,OUTPUT_DIRECTION);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LEDG_PUERTO_GPIO,1<<LEDG_BIT_GPIO,OUTPUT_DIRECTION);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LEDB_PUERTO_GPIO,1<<LEDB_BIT_GPIO,OUTPUT_DIRECTION);

	Chip_GPIO_ClearValue(LPC_GPIO_PORT, LEDR_PUERTO_GPIO,1<<LEDR_BIT_GPIO);
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, LEDG_PUERTO_GPIO,1<<LEDG_BIT_GPIO);
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, LEDB_PUERTO_GPIO,1<<LEDB_BIT_GPIO);
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, LED1_PUERTO_GPIO,1<<LED1_BIT_GPIO);
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, LED2_PUERTO_GPIO,1<<LED2_BIT_GPIO);
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, LED3_PUERTO_GPIO,1<<LED3_BIT_GPIO);

	// DE LA PROTO
	Chip_SCU_PinMux(PROTO_MUX_PORT,PROTO_MUX_PIN,MD_PUP,FUNC0);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, PROTO_PUERTO_GPIO,1<<PROTO_BIT_GPIO,OUTPUT_DIRECTION);
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, PROTO_PUERTO_GPIO,1<<PROTO_BIT_GPIO);
Chip_SCU_PinMux(LED_GPIO8_MUX_PORT,LED_GPIO8_MUX_PIN,MD_PUP,FUNC0);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, LED_GPIO8_PUERTO_GPIO,1<<LED_GPIO8_BIT_GPIO,OUTPUT_DIRECTION);
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, LED_GPIO8_PUERTO_GPIO,1<<LED_GPIO8_BIT_GPIO);


}

void EncenderLed(uint8_t led)
{
	if (led == LED_ROJO)
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,LEDR_PUERTO_GPIO,LEDR_BIT_GPIO);
	if (led == LED_VERDE)
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,LEDG_PUERTO_GPIO,LEDG_BIT_GPIO);
	if (led == LED_AZUL)
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,LEDB_PUERTO_GPIO,LEDB_BIT_GPIO);
	if (led == LED1)
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,LED1_PUERTO_GPIO,LED1_BIT_GPIO);
	if (led == LED2)
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,LED2_PUERTO_GPIO,LED2_BIT_GPIO);
	if (led == LED3)
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,LED3_PUERTO_GPIO,LED3_BIT_GPIO);
	if (led == LED_PROTO)
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PROTO_PUERTO_GPIO,PROTO_BIT_GPIO);
if (led == LED_GPIO8)
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,LED_GPIO8_PUERTO_GPIO,LED_GPIO8_BIT_GPIO);

}
void ApagarLed(uint8_t led)
{

	if (led == LED_ROJO)
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LEDR_PUERTO_GPIO,LEDR_BIT_GPIO);
	if (led == LED_VERDE)
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LEDG_PUERTO_GPIO,LEDG_BIT_GPIO);
	if (led == LED_AZUL)
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LEDB_PUERTO_GPIO,LEDB_BIT_GPIO);
	if (led == LED1)
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED1_PUERTO_GPIO,LED1_BIT_GPIO);
	if (led == LED2)
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED2_PUERTO_GPIO,LED2_BIT_GPIO);
	if (led == LED3)
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED3_PUERTO_GPIO,LED3_BIT_GPIO);
	if (led == LED_PROTO)
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PROTO_PUERTO_GPIO,PROTO_BIT_GPIO);
	if (led == LED_GPIO8)
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED_GPIO8_PUERTO_GPIO,LED_GPIO8_BIT_GPIO);
}

void ApagarLeds()
{

		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LEDR_PUERTO_GPIO,LEDR_BIT_GPIO);
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LEDG_PUERTO_GPIO,LEDG_BIT_GPIO);
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LEDB_PUERTO_GPIO,LEDB_BIT_GPIO);
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED1_PUERTO_GPIO,LED1_BIT_GPIO);
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED2_PUERTO_GPIO,LED2_BIT_GPIO);
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED3_PUERTO_GPIO,LED3_BIT_GPIO);
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PROTO_PUERTO_GPIO,PROTO_BIT_GPIO);
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,LED_GPIO8_PUERTO_GPIO,LED_GPIO8_BIT_GPIO);
}

void CambiarLed(uint8_t led)
{
if (led == LED_ROJO)
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,LEDR_PUERTO_GPIO,LEDR_BIT_GPIO);
if (led == LED_VERDE)
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,LEDG_PUERTO_GPIO,LEDG_BIT_GPIO);
if (led == LED_AZUL)
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,LEDB_PUERTO_GPIO,LEDB_BIT_GPIO);
if (led == LED1)
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,LED1_PUERTO_GPIO,LED1_BIT_GPIO);
if (led == LED2)
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,LED2_PUERTO_GPIO,LED2_BIT_GPIO);
if (led == LED3)
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,LED3_PUERTO_GPIO,LED3_BIT_GPIO);
if (led == LED_PROTO)
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,PROTO_PUERTO_GPIO,PROTO_BIT_GPIO);
if (led == LED_GPIO8)
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,LED_GPIO8_PUERTO_GPIO,LED_GPIO8_BIT_GPIO);

}


/*==================[end of file]============================================*/

