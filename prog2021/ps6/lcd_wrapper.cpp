#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
#include "lcd_wrapper.h"
#include "mastermind.h"
LiquidCrystal_I2C lcd(0x27,16,2);

void lcd_init(){
  randomSeed(analogRead(0));
  pinMode(LED_BLUE_1,OUTPUT);
  pinMode(LED_BLUE_2,OUTPUT);
  pinMode(LED_BLUE_3,OUTPUT);
  pinMode(LED_BLUE_4,OUTPUT);
  pinMode(LED_RED_1,OUTPUT);
  pinMode(LED_RED_2,OUTPUT);
  pinMode(LED_RED_3,OUTPUT);
  pinMode(LED_RED_4,OUTPUT);
  pinMode(BTN_1_PIN,INPUT);
  pinMode(BTN_2_PIN,INPUT);
  pinMode(BTN_3_PIN,INPUT);
  pinMode(BTN_4_PIN,INPUT);
  pinMode(BTN_ENTER_PIN,INPUT);
  
  lcd.init();                     
  lcd.backlight();                
 /* lcd.setCursor(0,0);              
  lcd.print("Welcome to");       
  lcd.setCursor(0,1);              
  lcd.print("MasterMind!");  
  delay(1500);   */
  
}

void lcd_clear(){
  lcd.clear();
}


void lcd_set_cursor(int y, int x){
  lcd.setCursor(x,y);
}


void lcd_print(char* text){
    Serial.println(text);
    lcd.print(text);
}
void lcd_print_int(const int n){
    lcd.print(n);
}


void lcd_print_at(int y, int x, char* text){
    lcd_set_cursor(y, x);
    lcd_print(text);
}
