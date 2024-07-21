////////////////////////////////////////////////////////////
//  GAMESTATES.H
///////////////////////////////////////////////////////////

/*

Ebben a header fájlban történnek a különböző játékstátuszok implementálása.
Ez a két játékstátusz maga a játék közbeni és játék végi állapot.


*/

/*

Az ingame függvény felel magáért a játékért. A függvény lekezeli a játékos és a tárgyak mozgatását,
illetve kirajzolását. A játék logikája nagyon egyszerű. Játékos esetén csak az függőleges irányt nézi,
az akadályok esetén csak a vízszintest. Ha a játékos és a kövek koordinátája megegyezik, akkor vége a játéknak.
Az akadélyoknál két logikai változó dolgozik. Az egyik a lehetőségét biztosítja, a másik a mozgatását.
Értelemszerűen, ha az akadály nem létezik, akkor nem mozoghat, ha pedig mozog, akkor nem lehet lerakni.

*/

int ingame(int score, int pin) //Játék menet
{
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("SCORE:");
  lcd.setCursor(10, 0);
  lcd.print(score);
  //változók alaphelyzetbe hozása új játék esetén
  int playerPos = 1;
  g_rock1pos = 16;
  g_rock2pos = 16;
  g_rock1spawn = true;
  g_rock2spawn = true;
  g_rock1move = false;
  g_rock1move = false;
  //Véletlenszerűség biztosítása
  int rock1chance = random(1, 4);
  Serial.println("rock1chance:");
  Serial.println(rock1chance);  //debug
  int rock2chance = random(5, 11);
  Serial.println("rock2chance:");
  Serial.println(rock2chance); //debug
  //Játékciklus
  while(1){
    //Death check
    if(playerPos == 1 && (g_rock1pos == 0 || g_rock2pos == 0 )){
      break;
    }
    else {
      score++;
      //ciklus frissítés
      if(g_rock1pos == 0) {
        g_rock1move = false;
        g_rock1spawn =  true;
        g_rock1pos = 16;
      }
      if(g_rock2pos == 0){
        g_rock2move = false;
        g_rock2spawn = true;
        g_rock2pos = 16;
      }
      //kövek létrehozása
      g_rock1spawn = rockSpawn(g_rock1spawn, &g_rock1move, rock1chance);
      if(g_rock1spawn == false && g_rock2spawn == true && g_rock1pos < 16 && ((millis() % 3) == 0)){
        g_rock2spawn = rockSpawn(g_rock2spawn, &g_rock2move, rock2chance);
      }
      //kövek mozgatása
      if(g_rock1spawn == false && g_rock1move == true && g_rock1pos != 0){
        g_rock1pos--;
      }
      if(g_rock2spawn == false && g_rock2move == true && g_rock2pos != 0){
        g_rock2pos--;
      }
      //A játékos mozgásának kiszámítása
      playerPos = playerJump(playerPos, pin);
      //A fentiek kirajzolása a kijelzőre
      Draw(playerPos, g_rock1pos, g_rock2pos, g_rock1move, g_rock2move, score);
      delay(100); //Lényegében itt állítható a játék sebessége
    }
  }//end while
  return score;
}//end ingame

/*

A gameover státuszban jelenik meg az elért pontszám.
Gombnyomásra a játék újraindítható.

*/

int gameover(int score, int pin) //Gameover képernyő
{
  lcd.clear();
  lcd.setCursor(3, 0); //Kurzur a belfelső sarokba
  lcd.print("GAMEOVER!");
  lcd.setCursor(0, 1);
  String gameover_score = "SCORE:" + String(score);
  String gameover_hint = " PRESS THE BUTTON TO PLAY AGAIN!  "; 
  String gameover_message = gameover_score + gameover_hint;
  //szöveg kiiratása
  while(1)
  {
    if(!digitalRead(pin)){
      lcd.clear();
      break;
    }
    scrollText(1, gameover_message, 300, 16, pin);
    if(!digitalRead(pin)){
      lcd.clear();
      break;
    }
  }//end while
  score = 0; //pontszám nullázása
  return score;  
} //end gameover