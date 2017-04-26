#ifndef DHT22_H_
#define DHT22_H_

/** @file dht.h
 *  @brief DHT22 header file
 *
 */

#define dht22_pin	12
#define dht22_port	6
#define dht22_gpioPin	8
#define dht22_gpioPort	2
typedef uint8_t byte;

void dht22_delay_ms (unsigned char time);
void dht22_delay_us (unsigned char time);
byte leer_datos_dht(void);
void leer_dht22_pin (void);
void leer_dht22(float *,float *);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* DHT22_H_ */
