int ingame(int score, int pin) //Játék menet
{
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("SCORE:");
  lcd.setCursor(10, 0);
  lcd.print(score);
  int playerPos = 1;

  

  while(1){
    if(playerPos == 1 && (g_rock1pos == 0 || g_rock2pos == 0 )){
      Serial.println("Collosion!");
      break;
    }
    else {
      score++;
      if(g_rock1pos == 0) {
        Serial.println("Rock1 end");
        g_rock1move = false;
        g_rock1spawn =  true;
        g_rock1pos = 15;
      }
      if(g_rock2pos == 0){
        Serial.println("Rock2 end");
        g_rock2move = false;
        g_rock2spawn = true;
        g_rock2pos = 15;
      }
      rockSpawn(g_rock1spawn, &g_rock1move);
      if(g_rock1spawn == false && g_rock2spawn == true){
        Serial.println("Rock2 spawning...");
        rockSpawn(g_rock2spawn, &g_rock2move);
      }
    
      g_rock2pos = rockMove(g_rock2pos, g_rock2move, &g_rock2spawn);
      g_rock1pos = rockMove(g_rock2pos, g_rock1move, &g_rock1spawn);
      playerPos = playerJump(playerPos, pin);
      Serial.println("Rock1 Pos:");
      Serial.println(g_rock1pos);
      Serial.println("Rock2 Pos:");
      Serial.println(g_rock2pos);
      Serial.println("Rock1 move:");
      Serial.println(g_rock1move);
      Serial.println("Rock2 move:");
      Serial.println(g_rock2move);
      Serial.println("Rock1 spawn value:");
      Serial.println(g_rock1spawn);
      Serial.println("Rock2 spawn value:");
      Serial.println(g_rock2spawn);
      Draw(playerPos, g_rock1pos, g_rock2pos, g_rock1move, g_rock2move, score);

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