/*
 * ATtiny85_Blink_C.c
 *
 * Created: 7/26/2024 7:04:51 PM
 * Author : Patrick
 */ 

#ifndef F_CPU
#define F_CPU			16500000UL			// 16.5MHz clock speed
#endif

#undef	LED_BUILTIN
#define LED_BUILTIN		0x01				// LED pin on PORTB

#include <avr/io.h>
#include <util/delay.h>

#define	delay(x)	_delay_ms(x)

int main(void)
{
	DDRB = LED_BUILTIN;						// Makes PORTB -> Pin 1 Output
	PORTB = 0x00;							// Sets all outputs to LOW
    while (1) 
    {
		PORTB ^= LED_BUILTIN;				// Toggles PB0
		delay(1000);
    }
}

