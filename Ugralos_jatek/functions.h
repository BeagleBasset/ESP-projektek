///////////////////////////////////////////////////
// FUNCTIONS.H
///////////////////////////////////////////////////

/*

Ebben a fájlban vannak a játék során használt segédfüggvények.
A játék végén lévő gördülő szöveg, a játékos ugrását lekezelő,
a kövek lerakását biztosító és végsősoron a rajzoló függvény.

*/

/* Függvény a gördülő szövegekhez

A függvény semmit se ad vissza. Bemenő paraméterei: kiiratás sora, 
a szöveg, sebesség, oszlopok, és a megszakító gomb pinje.

*/
void scrollText(int row, String message, int delayTime, int lcdColumns, int pin) {
  for (int i=0; i < lcdColumns; i++) {
    message = " " + message; 
  } 
  message = message + " "; 
  for (int pos = 0; pos < message.length(); pos++) {
    //megszakíthatóság
    if(!digitalRead(pin)){
      break;
    }
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
  }//kiiratás vége
}//end scrollText

/* Játékos ugrása

A playerJump függvény kezeli a játékos ugrását.
Bekéri a játékos pozícióját (hiszen az ugrás több ideig tart) és azt is adja vissza.
Illetve a nyomógomb pinjét, ami megvalósítja az ugrást.

*/

int playerJump(int playerPos, int pin) {
  if(playerPos == 0){
    if(g_jumptic == 3){
      g_jumptic = 0;
      playerPos = 1;
      return playerPos;
    }//Az ugrés a játék szerint 3 időegységig tart.
    else {
      g_jumptic++;
      return playerPos;
    }
  }
  if(!digitalRead(pin))   //ugrás
  {
    playerPos = 0;
    return playerPos;
  }
  else                    //nem történik semmi
  {
    playerPos = 1;
    return playerPos;
  }
}//end playerJump

/* Akadály lerakás

A rockSpawn felel az akadályok lerakásáért.
A függvény a program futását nézi és maradékot vizsgál.
Az osztás a futásidő és az akadályhoz beállított véletlenszám szerint történik.
Ezzel biztosítva a játék véletlenszerűségét.

*/

bool rockSpawn(bool rockspawn, bool* rockMove, int chance){
  if(rockspawn){
  unsigned long check = millis() + random(1, 1000);
  Serial.println("check:");
  Serial.println(check);
  int modulo = check % chance;
  Serial.println(modulo);  
  if((modulo == 0) && (rockspawn == true)){
    *rockMove = true;
    rockspawn = false;
    return rockspawn;
    }
  }
  else{
    return rockspawn;
  }
}//end rockSpawn

/* Kirajzolás a kijelzőre

Voltaképp a játék "grafikus motorja".
Kirajzolja a játékost és a sziklákat pozícióiknak megfelelően.
Bekéri a játékos és az akadályok helyzetét.
A rock1Move és rock2Move értelmében rajzolja ki a köveket.
És végezetül az eddig elért pontszámot is kiírja.

*/

void Draw(int playerPos, int rock1Pos, int rock2Pos, bool rock1Move, bool rock2Move, int score){
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("SCORE:");
  lcd.setCursor(10, 0);
  lcd.print(score);
  //játékos kirajzolása
  if(playerPos == 0){
    lcd.setCursor(0, playerPos);
    lcd.write(byte(1));
  }
  else{
    if(g_playerstate == 0){
    lcd.setCursor(0, playerPos);
    lcd.write(byte(0));
    g_playerstate = 1;
    }
    else {
    lcd.setCursor(0, playerPos);
    lcd.write(byte(1));
    g_playerstate = 0;
    }
  }//játékos kirajzolásának vége
  //akadályok kirajzolása
  if(rock1Move == true){
    lcd.setCursor(rock1Pos, 1);
    lcd.print("o");
  }
  if(rock2Move == true){
    lcd.setCursor(rock2Pos, 1);
    lcd.print("o");    
  }//akadályok kirajzolásának vége
}//end of Draw