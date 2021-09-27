
#include "mastermind.h"
#include "lcd_wrapper.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <Arduino.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
char* generate_code(bool repeat, int length) {
  if (length < 1) {
    return NULL;
  }
  char * ans = (char*)calloc(length + 1, sizeof(char));
  bool arr[10] = {false, false, false, false, false, false, false, false, false, false};
  for (int i = 0; i < length; i++) {
    int k = 0;
    do {
      k = random() % 10;
    } while (arr[k] && !repeat);
    char n = (char)(k + 48);
    arr[k] = true;
    ans[i] = n;
  }
  ans[length] = '\0';
  return ans;
}
void get_score(const char* s, const char* g, int* peg_a, int* peg_b) {
  *peg_a = 0;
  *peg_b = 0;
  char gg[10];
  
  strcpy(gg, g);
  for (int i = 0; s[i]; i+=1) {
    for (int j = 0; gg[j]; j +=1) {
      if (s[i] == gg[j]) {
        *peg_b +=1;
        gg[j] = ' ';
        break;
      }
    }
    if (s[i] == g [i]) {
      *peg_a += 1;
      *peg_b -= 1;
    }
  }
}
void render_leds(const int peg_a, const int peg_b){
    int  c = 0 ;
    //LED_BLUE_1 = 6
    //LED_RED_1 = 7
    for(int i = 0; i< peg_a; i += 1){
      digitalWrite(LED_RED_1+i*2,1);  
    }
    for(int i = peg_a; i<peg_a + peg_b; i +=1){
      digitalWrite(LED_BLUE_1 + i*2,1);
    }
}
void turn_off_leds(){
  for(int i = 6; i <14; i++){
    digitalWrite(i,0);
  }
}
void render_history(char* secret, char** history, const int entry_nr){
  int a,b;
  lcd_clear();
  turn_off_leds();
  get_score(secret,history[entry_nr],&a,&b);
  render_leds(a,b);
  lcd_set_cursor(0,0);
  lcd_print_int(entry_nr);
  lcd_print(" ");
  lcd_print(history[entry_nr]);
  lcd_print(" ");
  lcd_print_int(a);
  lcd_print("A");
  lcd_print_int(b);
  lcd_print("B");
}
void play_game(char* secret){
  lcd_print_at(0,0,"Mastermind.");
  delay(1000);
  lcd_clear();
  turn_off_leds();
  char **history = (char **)calloc(11,sizeof(char*));
  for(int i = 0; i < 10; i++){
    history[i] = (char*)calloc(5,sizeof(char));
  }
  lcd_clear();
  lcd_print_at(0,0,"Try guess: ");
 // lcd_print(secret);
  lcd_print_at(1,0,"0000");
  char gues[5] ="0000";
  delay(500);
  int btn_enter = !digitalRead(BTN_ENTER_PIN);
  int btn1 = digitalRead(BTN_1_PIN);
  int btn2 = digitalRead(BTN_2_PIN);
  int btn3 = digitalRead(BTN_3_PIN);
  int btn4 = digitalRead(BTN_4_PIN);
  int tryed = 10;
  while(1){
    lcd_print_at(1,0,gues);
    btn_enter = !digitalRead(BTN_ENTER_PIN);
    btn1 = digitalRead(BTN_1_PIN);
    btn2 = digitalRead(BTN_2_PIN);
    btn3 = digitalRead(BTN_3_PIN);
    btn4 = digitalRead(BTN_4_PIN);
    Serial.print("btn1: ");Serial.println(btn1);
    Serial.print("btn2: ");Serial.println(btn2);
    Serial.print("btn3: ");Serial.println(btn3);
    Serial.print("btn4: ");Serial.println(btn4);
    Serial.print("btn_enter: ");Serial.println(btn_enter);
    if(btn1 == HIGH){
      int was = 1;
      btn1 = digitalRead(BTN_1_PIN);
      int h = -1;
      while(btn1 == HIGH && tryed != 10){
        btn1 = digitalRead(BTN_1_PIN);
        btn2 = digitalRead(BTN_2_PIN);
        btn3 = digitalRead(BTN_3_PIN);

        if(btn2 == HIGH || btn3 == HIGH){
          was = 0;
          
          if(btn2 == HIGH){
            Serial.print("tryed = "); Serial.println(tryed);
            if(h+1 != 10-tryed){
              Serial.print("h = "); Serial.println(h);
              h = (h+1)%(10 - tryed);
              delay(300);  
            }
          }else if(btn3 == HIGH){
            if(h  > 0 ){
              h = h-1;
            }
            delay(300);
         }
         
          render_history(secret,history,h);
          lcd_print_at(1,0,gues);
        }
         delay(50);
         
      } 
      turn_off_leds();
      lcd_clear();
      lcd_print_at(0,0,"Try guess: ");
     // lcd_print(secret);
      lcd_print_at(1,0,gues);
      if(was){
        gues[0] = (char)(((int)gues[0] - 47)%10+48);
        digitalWrite(LED_BLUE_1,HIGH);
        delay(500);
        digitalWrite(LED_BLUE_1,LOW);
      }
    }if(btn2 == HIGH){
      gues[1] = (char)(((int)gues[1] - 47)%10+48);
      digitalWrite(LED_BLUE_2,HIGH);
      delay(500);
      digitalWrite(LED_BLUE_2,LOW);
    }if(btn3 == HIGH){
        int was = 1;
        btn3 = digitalRead(BTN_3_PIN);
        btn4 = digitalRead(BTN_4_PIN);
      while(btn3 == HIGH){
        btn3 = digitalRead(BTN_3_PIN);
        btn4 = digitalRead(BTN_4_PIN);
        if(btn4 == HIGH){
          was = 0;
          lcd_print_at(0,11,secret);
        }
      }
      if(was == 0){
        delay(1000);  
        lcd_print_at(0,11,"    ");
        continue;
      }
      if(was){
        gues[2] = (char)(((int)gues[2] - 47)%10+48);
        digitalWrite(LED_BLUE_3,HIGH);
        delay(500);
        digitalWrite(LED_BLUE_3,LOW);
      }
    }if(btn4 == HIGH){
      gues[3] = (char)(((int)gues[3] - 47)%10+48);
      digitalWrite(LED_BLUE_4,HIGH);
      delay(500);
      digitalWrite(LED_BLUE_4,LOW);
    }
    if(btn_enter == HIGH){
      strcpy(history[10-tryed],gues);
      tryed -= 1;
      lcd_clear();
      lcd_print_at(0,0,"Try guess: ");
     // lcd_print(secret);
      lcd_print_at(1,0,gues);
      int a,b;
      get_score(secret,gues,&a,&b); 
      Serial.print("a and b :");
      Serial.print(a);
      Serial.print(" ");
      Serial.print(b);
      render_leds(a,b);
      if(a == 4){
        lcd_clear();
        lcd_print_at(0,0,"You Win");
        lcd_print_at(1,0,"Code:");
        lcd_print_at(1,6,secret);
        delay(5000);
        return;
      }else{
        lcd_clear();
        lcd_print_at(0,0,"Nice try!");
        lcd_print_at(1,0,"Tries: ");
        lcd_print_int(tryed);
        lcd_set_cursor(1,11);
        lcd_print_int(a);
        lcd_print("A");
        lcd_print_int(b);
        lcd_print("B");
        delay(1300);
        lcd_clear();
      }
      if(tryed == 0){
       lcd_clear();
        lcd_print_at(0,0,"You Lose");
        lcd_print_at(1,0,"Code:");
        lcd_print_at(1,6,secret);
        delay(5000);
        return;
      }
     turn_off_leds();
     lcd_print_at(0,0,"Try guess: ");
    //lcd_print(secret);
    for(int s = 0; s <4 ; s++){
      gues[s] = 48;
    }
    lcd_print_at(1,0,gues);
    }
  }
  lcd_clear();
  for(int i = 0; i < 11; i++){
    free(history[i]);
  }
  free(history);

}
