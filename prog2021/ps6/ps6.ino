#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
#include "mastermind.h"
#include "lcd_wrapper.h"

void setup()
{
  lcd_init();
  Serial.begin(9600);
  turn_off_leds(); 
};


void loop()
{ 
  char *code = generate_code(false,4);
  play_game(code);
  free(code);
}
