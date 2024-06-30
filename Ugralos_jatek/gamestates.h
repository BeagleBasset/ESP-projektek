void ingame(int score) //Játék menet
{

}

void gameover(int score) //Gameover képernyő
{
  lcd.setCursor(0, 0); //Kurzur a belfelső sarokba
  lcd.print("GAMEOVER!");
  lcd.setCursor(0, 1);
  String gameover_score = "SCORE:" + score;
  String gameover_hint = " PRESS THE BUTTON TO PLAY AGAIN!  "; 
  String gameover_message = gameover_score + gameover_hint;
  scrollText(1, gameover_message, 100, 0);
} //end gameover