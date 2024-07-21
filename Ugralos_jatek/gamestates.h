int ingame(int score, int pin) //Játék menet
{
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("SCORE:");
  lcd.setCursor(10, 0);
  lcd.print(score);
  int playerPos = 1;
  g_rock1pos = 16;
  g_rock2pos = 16;
  g_rock1spawn = true;
  g_rock2spawn = true;
  g_rock1move = false;
  g_rock1move = false;
  int rock1chance = random(1, 4);
  Serial.println("rock1chance:");
  Serial.println(rock1chance);
  int rock2chance = random(5, 11);
  Serial.println("rock2chance:");
  Serial.println(rock2chance);
  while(1){
    if(playerPos == 1 && (g_rock1pos == 0 || g_rock2pos == 0 )){
      break;
    }
    else {
      score++;
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
      g_rock1spawn = rockSpawn(g_rock1spawn, &g_rock1move, rock1chance);
      if(g_rock1spawn == false && g_rock2spawn == true && g_rock1pos < 16 && ((millis() % 3) == 0)){
        g_rock2spawn = rockSpawn(g_rock2spawn, &g_rock2move, rock2chance);
      }
      if(g_rock1spawn == false && g_rock1move == true && g_rock1pos != 0){
        g_rock1pos--;
      }
      if(g_rock2spawn == false && g_rock2move == true && g_rock2pos != 0){
        g_rock2pos--;
      }
      playerPos = playerJump(playerPos, pin);

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