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
  byte temp;
  memset( data_array, 0x42, sizeof( data_array ) );

  write_byte( 0x00, 'a' );
  write_page( 0x10, data_array );

  temp = readEEPROM( 0x11 );

  if ( temp == 0x42 )
  {
    pinMode( 0, OUTPUT );
    digitalWrite( 0, HIGH );
  }

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

byte readEEPROM( unsigned int eeaddress )
{
  byte rdata = 0xFF;
  const uint8_t upper_three_eeprom_adress_bits = (eeaddress >> 8) & 0x7;
  const uint8_t i2c_address = EEPROM_ADDR | upper_three_eeprom_adress_bits;
  TinyWireM.beginTransmission(i2c_address);
  TinyWireM.write(eeaddress & 0xFF); // address LSB
  
  TinyWireM.endTransmission();

  TinyWireM.requestFrom(EEPROM_ADDR, 1);

  if (TinyWireM.available()) rdata = TinyWireM.read();

  return rdata;
}