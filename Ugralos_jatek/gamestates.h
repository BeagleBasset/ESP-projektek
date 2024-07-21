int ingame(int score, int pin) //Játék menet
{
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("SCORE:");
  lcd.setCursor(10, 0);
  lcd.print(score);
  int playerPos = 1;
  int rock1Pos = 15;
  int rock2Pos = 15;
  

  while(1){
    if(playerPos == 1 && (rock1Pos == 0 || rock2Pos == 0 )){
      Serial.println("Collosion!");
      break;
    }
    else {
      score++;
      if(rock1Pos == 0) {
        Serial.println("Rock1 end");
        g_rock1move = false;
        g_rock1spawn =  true;
        rock1Pos = 15;
      }
      if(rock2Pos == 0){
        Serial.println("Rock2 end");
        g_rock2move = false;
        g_rock2spawn = true;
        rock2Pos = 15;
      }
      rockSpawn(g_rock1spawn, &g_rock1move);
      if(g_rock1spawn == false && g_rock2spawn == true){
        Serial.println("Rock2 spawning...");
        rockSpawn(g_rock2spawn, &g_rock2move);
      }
    
      rock2Pos = rockMove(rock2Pos, g_rock2move, &g_rock2spawn);
      rock1Pos = rockMove(rock1Pos, g_rock1move, &g_rock1spawn);
      playerPos = playerJump(playerPos, pin);
      Serial.println("Rock1 Pos:");
      Serial.println(rock1Pos);
      Serial.println("Rock2 Pos:");
      Serial.println(rock2Pos);
      Serial.println("Rock1 move:");
      Serial.println(g_rock1move);
      Serial.println("Rock2 move:");
      Serial.println(g_rock2move);
      Serial.println("Rock1 spawn value:");
      Serial.println(g_rock1spawn);
      Serial.println("Rock2 spawn value:");
      Serial.println(g_rock2spawn);
      Draw(playerPos, rock1Pos, rock2Pos, g_rock1move, g_rock2move, score);

      delay(100);
    }
  }
  return score;

}

int gameover(int score, int pin) //Gameover képernyő
{
  lcd.clear();
  lcd.setCursor(3, 0); //Kurzur a belfelső sarokba
  lcd.print("GAMEOVER!");
  lcd.setCursor(0, 1);
  String gameover_score = "SCORE:" + String(score);
  String gameover_hint = " PRESS THE BUTTON TO PLAY AGAIN!  "; 
  String gameover_message = gameover_score + gameover_hint;
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
  }
  score = 0;
  return score;  
} //end gameover