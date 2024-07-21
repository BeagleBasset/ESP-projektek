
//Függvény a gördülő szövegekhez
void scrollText(int row, String message, int delayTime, int lcdColumns, int pin) {
  for (int i=0; i < lcdColumns; i++) {
    message = " " + message; 
  } 
  message = message + " "; 
  for (int pos = 0; pos < message.length(); pos++) {
    if(!digitalRead(pin)){
      break;
    }
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
  }
}

int playerJump(int playerPos, int pin) {
  if(playerPos == 0){
    if(g_jumptic == 3){
      g_jumptic = 0;
      playerPos = 1;
      return playerPos;
    }
    else {
      g_jumptic++;
      return playerPos;
    }
  }
  if(!digitalRead(pin))
  {
    playerPos = 0;
    return playerPos;
  }
  else
  {
    playerPos = 1;
    return playerPos;
  }
}

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
}


void Draw(int playerPos, int rock1Pos, int rock2Pos, bool rock1Move, bool rock2Move, int score) {

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("SCORE:");
  lcd.setCursor(10, 0);
  lcd.print(score);
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
  }

  if(rock1Move == true){
    lcd.setCursor(rock1Pos, 1);
    lcd.print("o");
  }
  if(rock2Move == true){
    lcd.setCursor(rock2Pos, 1);
    lcd.print("o");    
  }
}