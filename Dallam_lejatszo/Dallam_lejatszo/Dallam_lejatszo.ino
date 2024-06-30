/*

†JMJ†

///////////////////////////////////////////////
//             DALLAM LEJÁTSZÓ               //
///////////////////////////////////////////////

A program leírása:

A program egy tetszőleges dallamot játszik le egy passzív buzzer segítségével.
A program elején a zenei hangok kerülnek definiálásra. Jelenleg 1 oktáv terjedelemben
A dallamot egy tömben tároljuk. Ezen tömb módosításával lehet a dallamot átírni.
A dallamot egy gomb lenyomásával lehet elindítani, illetve újraindítani.


Verzió: 1.0
Készült: Az Úr 2024. évében, Jézus Krisztus Szentséges Szívének havának 22. napján.
AMDG

†JMJ†

*/

///////////////////////////////////////////////
//              DEFINIÁLÁSOK                 //
///////////////////////////////////////////////

//Zenei hangok frekvenciáinak definiálása

#define C4  261.63
#define D4  293.66
#define E4  329.63
#define F4  349.23
#define G4  392
#define A4  440
#define B4  493.88
#define C5  523.25
#define D5  587.33
#define E5  659.25

///////////////////////////////////////////////
//              DALLAM TÖMB                  //
///////////////////////////////////////////////

// Ezen tömben kerülnek eltárolásra a dallam hangjai
// A tömb elemeinek módosításával lehet más dallamot lejátszatni.

float melody[] = {

  C5, B4, A4, G4, A4, A4, E4, E4, E4, A4, A4, B4, C5, D5, E5, A4, D5, G4, C5, C5, B4, C5
};

//Dallam tömb hossza

int Length;

// A hangok hossza

int NoteDuration[] = {

  4, 4, 4, 4, 12, 16, 2, 12, 16, 2, 4, 4, 2, 2, 2, 2, 2, 4, 4, 2, 2, 1

};                  //1 másodperccel leosztva a hanghossz
int DelayBetweenNotes = 1000 / 16 * 1.30;  //Hangok közötti szünet

///////////////////////////////////////////////
//            GLOBÁLIS VÁLTOZÓK              //
///////////////////////////////////////////////

int Status = 0;   //Indítógomb státusza

///////////////////////////////////////////////
//               PIN KIOSZTÁS                //
///////////////////////////////////////////////

const int BUZZERPIN   =   12;   //Hangszóró pin
const int STARTPIN    =   27;   //Indítógomb pin
const int STARTPINVCC =   25;   //Indítógomb VCC pin


//--------------------------------------------//


void setup() {
  
  pinMode(STARTPIN, INPUT_PULLDOWN);       //Indítógomb pinmode deklarálása
  pinMode(STARTPINVCC, OUTPUT);            

  for(auto i: melody)                      //A dallam hosszának megállapítása
  {

    Length++;

  }

}

void loop() {
  digitalWrite(STARTPINVCC, HIGH);
  Status = digitalRead(STARTPIN); //A gomb állapota
  if(Status)
  {
    
    //Lejátsza a dallamot
    for(int Note = 0; Note < Length; Note++)
    {
      tone(BUZZERPIN, melody[Note], 2000 / NoteDuration[Note]);
      delay(2000 / NoteDuration[Note] * 1.30);
      noTone(BUZZERPIN);
      
    }
    Status = 0;
  }
  

}
