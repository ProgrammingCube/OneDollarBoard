/*
 * ATtiny85_I2C_Eeprom_C.c
 *
 * Created: 7/27/2024 4:36:07 PM
 * Author : Patrick
 */ 

#ifndef F_CPU
#define F_CPU	16500000UL				// 16.5MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "inc/USI_TWI_Master.h"

#define	delay(x)	_delay_ms(x)

#define I2C_READ	TRUE<<TWI_READ_BIT
#define I2C_WRITE	FALSE<<TWI_READ_BIT

#define	MEMORY_ADDR_HEADER	0b1010
#define MEMORY_ADDR_ADDR	0b0000
#define MEMORY_I2C_ADDR		(MEMORY_ADDR_HEADER<<3)|(MEMORY_ADDR_ADDR)

typedef uint8_t byte;

/* main function */
int main( void )
{
	
	byte page_to_write[] = { ( byte ) ( MEMORY_I2C_ADDR << TWI_ADR_BITS ) | I2C_WRITE,
							 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,
							 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF };
	
    /* set up USI block as I2C */
	USI_TWI_Master_Initialise();
	
	/* write page to see if this actually does anything at all */
	( void ) USI_TWI_Start_Read_Write( page_to_write, 17 );
	
	/* clear buffer to see if the read works */
	memset( page_to_write, 0, 17 );
	
	/* set first byte of page to memory IC address as a read address */
	page_to_write[ 0 ] = ( byte ) ( MEMORY_I2C_ADDR << TWI_ADR_BITS ) | I2C_READ;
	
	/* send page to be read */
	( void ) USI_TWI_Start_Read_Write( page_to_write, 17 );
	
    while (1) 
    {
    }
}
