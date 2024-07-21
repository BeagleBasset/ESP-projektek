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
int g_jumptic = 0;
int g_playerstate = 0;
int g_rock1pos = 16;
int g_rock2pos = 16;
bool g_rock1spawn = true;
bool g_rock2spawn = true;
bool g_rock1move = false;
bool g_rock2move = false;

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
const int ANALOG_PIN = 34;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  randomSeed(analogRead(ANALOG_PIN));
  Serial.begin(9600);
  lcd.init(); //LCD inicializálása
  lcd.backlight(); //Háttérvilágítás bekapcsolása
  lcd.createChar(0, Player); //Játékos legenerálása
  lcd.createChar(1, Player2);
  //Főcímkép kiíráatása
  lcd.setCursor(0, 0); //Kurzur a belfelső sarokba
  lcd.print("**JUMPING GAME**");
  lcd.setCursor(0, 1);
  for(int i = 0; i <= 16; i++) //Kamu töltő képernyő :)
  {
    lcd.print("*");
    delay(100);
    lcd.setCursor(i, 1);
  }
  delay(700);
  lcd.clear();
} //end setup

void loop() {
  g_score = ingame(g_score, BUTTON_PIN);
  g_score = gameover(g_score, BUTTON_PIN);
} // end loop
