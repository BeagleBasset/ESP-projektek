///////////////////////////////////////////////////
//Ugrálós játék
///////////////////////////////////////////////////

/*
✝JMJ✝

LEÍRÁS:

A játék egy 2x16 LCD I2C kijelzőn fut. Voltaképp a Google dinósjátékának felel meg.
A játékos balszélen van és jobbról jönnek az akadályok, amiket át kell ugrani.
Ugrani egy gomb segítségével lehet, ami az ESP32 13 pinjére van kötve.
A kapcsolás az ESP32 beépített felhúzó ellenállásával történik.
Az elemek véletlen feltűnését az eltelt idő és az Arduino beépített random függvényével történik.
A random függvényhez a seedet a 34 analóg pinről szedjük.

A játék célja minél több pontot összegyűjteni.


DÁTUM: 2024.07.21. Pünkösd utáni IX. vasárnap,  Szent Praxedis szúz emléknapján. 

✝JMJ✝
*/

///////////////////////////////////////////////////
//GLOBÁLIS VÁLTOZÓK
///////////////////////////////////////////////////

int g_score = 0;              //Pontszámláló 
int g_jumptic = 0;            //Az ugrás időtartamát határozza meg
int g_playerstate = 0;        //A játékos státuszát határozza meg az animációhoz
int g_rock1pos = 16;          //1. kő kiinduló pozíciója
int g_rock2pos = 16;          //2. kő kiinduló pozíciója
bool g_rock1spawn = true;     //1. kő lerakható false = nem rakható
bool g_rock2spawn = true;      
bool g_rock1move = false;     //1. kő mozgatható a kijelzőn, false = nem mozgatható
bool g_rock2move = false;

///////////////////////////////////////////////////
//Konstansok
///////////////////////////////////////////////////

const int LCD_COLUMNS = 1;    //kijelző deklarálása
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

const int BUTTON_PIN = 13;   //nyomógomb
const int ANALOG_PIN = 34;   //Random seedhez analóg zaj

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
  randomSeed(analogRead(ANALOG_PIN));
  Serial.begin(9600); //debughoz
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
  } //end for
  delay(700);
  lcd.clear();
} //end setup

void loop() {
  //A játék két fő részre bontható, amikor fut és amikor a játékos vesztett.
  g_score = ingame(g_score, BUTTON_PIN);
  g_score = gameover(g_score, BUTTON_PIN);
} // end loop
