/*
 * ATtiny85_L293D_C.c
 *
 * Created: 8/20/2024 11:55:12 PM
 * Author : Patrick
 */ 

//Motor A
// motorPin1  = 0  // Pin 14 of L293
// motorPin2  = 1  // Pin 10 of L293
//Motor B
// motorPin3  = 2 // Pin  7 of L293
// motorPin4  = 3  // Pin  2 of L293

#ifndef F_CPU
#define F_CPU			16500000UL			// 16.5MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>

#define	delay(x)	_delay_ms(x)

int main(void)
{
	DDRB = 0x0F;							// Set lower 4 pins to OUTPUT
	PORTB = 0x00;							// Set all pins LOW
	while (1)
	{
		PORTB = 0x01;						// Turn motor A clockwise for 2 seconds
		delay( 2000 );

		PORTB = 0x02;						// Turn motor A counter-clockwise for 2 seconds
		delay( 2000 );

		PORTB = 0x04;						// Turn motor B clockwise for 2 seconds
		delay( 2000 );

		PORTB = 0x08;						// Turn motor B counter-clockwise for 2 seconds
		delay( 2000 );
    }
}

