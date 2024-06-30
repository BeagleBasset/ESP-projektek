///////////////////////////////////////////////////
//Ugrálós játék
///////////////////////////////////////////////////

/*
✝JMJ✝

A játék egy LCD I2C kijelzőn fut. Voltaképp a Google dinósjátékának felel meg.
A játékos balszélen van és jobbról jönnek az akadályok, amiket át kell ugrani.
Ugrani egy gomb segítségével lehet.

✝JMJ✝
*/

///////////////////////////////////////////////////
//GLOBÁLIS VÁLTOZÓK
///////////////////////////////////////////////////

int g_score = 0;

///////////////////////////////////////////////////
//Konstansok
///////////////////////////////////////////////////

const int LCD_COLUMNS = 1;
const int LCD_ROWS = 15;


///////////////////////////////////////////////////
//Könyvtárak meghívása
///////////////////////////////////////////////////

#include <LiquidCrystal_I2C.h> //LCD kijelzőt kezelő könyvtár
LiquidCrystal_I2C lcd(0x27, LCD_COLUMNS, LCD_ROWS);
#include <functions.h>
#include <karakter.h>
#include <gamestates.h>


///////////////////////////////////////////////////
//PINKIOSZTÁS
///////////////////////////////////////////////////

const int BUTTON_PIN = 13; //nyomógomb
 

void setup() {
  
  lcd.init(); //LCD inicializálása
  lcd.backlight(); //Háttérvilágítás bekapcsolása
  lcd.createChar(0, Player); //Játékos legenerálása
  //Főcímkép kiíráatása
  lcd.setCursor(0, 0); //Kurzur a belfelső sarokba
  lcd.print("**JUMPING GAME**");
  lcd.setCursor(0, 1);
  for(int i; i <= 15; i++) //Kamu töltő képernyő :)
  {
    lcd.print("*");
    delay(100);
    lcd.setCursor(i, 1);
  }
  delay(500);
  lcd.clear();
} //end setup

void loop() {
  lcd.setCursor(0, 0);
  lcd.write(0);
  lcd.clear();
  delay(1000);
  gameover(g_score);
  g_score++;
} // end loop
