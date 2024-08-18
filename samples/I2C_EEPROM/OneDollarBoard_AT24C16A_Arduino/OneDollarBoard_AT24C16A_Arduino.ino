/* ATtiny85 AT24C16A example
 * TinyWireM.h is used instead of Wire.h
 * ATtiny85 PB0 - SDA
 * ATtiny85 PB2 - SCL
 */

#include <TinyWireM.h>

#define EEPROM_ADDR 0x50

char data_array[16];

void setup()
{
  memset( data, 0x42, sizeof( data ) );

  write_byte( 0x00, 'a' );
  write_page( 0x10, data_array );

}

void loop() {}

void write_page( int addr, char* data )
{
  unsigned char i;
  unsigned char i2c_addr = EEPROM_ADDR | ( ( addr >> 8 ) & 7 );

  TinyWireM.beginTransmission( i2c_addr );  // chip addr + MSB address
  TinyWireM.send( addr & 0xFF );            // LSB address
  
  for ( i = 0; i < 16; i++ )
  {
    TinyWireM.send( *data++ );
    delay( 5 );
  }
  TinyWireM.endTransmission();
}

void write_byte( int addr, char data )
{
  unsigned char i2c_addr = EEPROM_ADDR | ( ( addr >> 8 ) & 7 );
  
  TinyWireM.beginTransmission( i2c_addr );  // chip addr + MSB address
  TinyWireM.send( addr & 0xFF );            // LSB address
  TinyWireM.send( data );
  delay( 5 );
  TinyWireM.endTransmission();
}