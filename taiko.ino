#include <LiquidCrystal.h>
// Pin numbers
const int LCD_RS = 4;
const int LCD_EN = 0;
const int LCD_D4 = 10;
const int LCD_D5 = 9;
const int LCD_D6 = 8;
const int LCD_D7 = 7;
const int BUZZER = 2;
const int FORCE_LEFT = A5;
const int FORCE_RIGHT = A4;
const int LED_LEFT = 13;
const int LED_CENTER = 12;
const int LED_RIGHT = 11;
const int BLUE = 5;
const int RED = 3;
const int GREEN = 6;

// Game variables
int lives = 3;
int score = 0;
float tempos[] = {0.7, 0.52, 0.47};
float tempo_delay = 1.0;

// Initialize 
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
const int LCD_COLS = 16;
const int LCD_ROWS = 2;

void start_screen()
{
  lcd.clear();
  lcd.print("Taiko 1 line");
  lcd.setCursor(0, 1);
  lcd.print("Display only");
  delay(1500);
  lcd.clear();
}

void setup() 
{
  // put your setup code here, to run once:
  lcd.begin(LCD_COLS, LCD_ROWS);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_LEFT, OUTPUT);
  pinMode(LED_CENTER, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(GREEN,OUTPUT);
  start_screen();
  // Serial.begin(9600);
  main_loop();
}

int melody1[] = {
  294, 294, 587, 440, 415, 0, 392, 349, 349, 294, 349, 392, 262, 262, 587, 440, 415, 0, 392, 349, 349, 294, 349, 392, 247, 247, 587, 440, 415, 0, 392, 349, 349, 294, 349, 392, 233, 233, 587, 440, 415, 0, 392, 349, 349, 294, 349, 392, 294, 294, 587, 440, 415, 0, 392, 349, 349, 294, 349, 392, 262, 262, 587, 440, 415, 0, 392, 349, 349, 294, 349, 392, 247, 247, 587, 440, 415, 0, 392, 349, 349, 294, 349, 392, 233, 233, 587, 440, 415, 0, 392, 349, 349, 294, 349, 392, 587, 587, 1175, 880, 831, 0, 784, 698, 698, 587, 698, 784, 523, 523, 1175, 880, 831, 0, 784, 698, 698, 587, 698, 784, 494, 494, 1175, 880, 831, 0, 784, 698, 698, 587, 698, 784, 466, 466, 1175, 880, 831, 0, 784, 698, 698, 587, 698, 784, 587, 587, 1175, 880, 831, 0, 784, 698, 698, 587, 698, 784, 523, 523, 1175, 880, 831, 0, 784, 698, 698, 587, 698, 784, 494, 494, 1175, 880, 831, 0, 784, 698, 698, 587, 698, 784, 466, 466, 1175
};

int durations1[] = {
  125, 125, 250, 375, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 250, 375, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 250, 375, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 250, 375, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 250, 375, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 250, 375, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 250, 375, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 250, 375, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 250, 375, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 250, 375, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 250, 375, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 250, 375, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 250, 375, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 250, 375, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 250, 375, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 250
};

int melody2[] = { 
  988, 659, 988, 988, 831, 659, 831, 831, 659, 659, 659, 659, 659, 659, 740, 988, 659, 988, 988, 831, 659, 831, 831, 659, 659, 659, 659, 659, 659, 740, 554, 554, 554, 554, 554, 494, 554, 494, 494, 554, 554, 554, 554, 415, 494, 494, 494, 494, 494, 494, 494, 494, 494, 415, 370, 370, 415, 494, 415, 554, 554, 554, 554, 554, 494, 554, 494, 494, 554, 554, 554, 622, 494, 554, 1109, 622, 1245, 494, 988, 494, 440, 330, 659, 330, 659, 370, 740, 622, 659, 0
};
int durations2[] = { 
  500, 250, 250, 1000, 500, 250, 250, 1000, 750, 250, 1000, 750, 250, 250, 750, 500, 250, 250, 1000, 500, 250, 250, 1000, 750, 250, 1000, 750, 250, 250, 750, 250, 250, 250, 250, 500, 500, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 500, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 500, 500, 250, 250, 250, 250, 250, 500, 250, 250, 500, 500, 250, 250, 1000, 1000, 250, 500, 250, 250, 250, 250, 250, 250, 250, 250, 0 
};


int melody3[] = { 
  659, 659, 0, 659, 0, 523, 659, 784, 0, 392, 0, 523, 0, 392, 392, 0, 330, 0, 440, 494, 494, 466, 440, 392, 659, 784, 880, 698, 784, 0, 659, 523, 587, 494, 523, 0, 392, 392, 0, 330, 0, 440, 494, 494, 466, 440, 392, 659, 784, 880, 698, 784, 0, 659, 523, 587, 494, 0, 784, 740, 698, 622, 659, 0, 415, 440, 523, 0, 440, 523, 587, 0, 784, 740, 698, 622, 659, 0, 392, 1047, 392, 1047, 392, 1047, 0, 0, 784, 740, 698, 622, 659, 0, 415, 440, 523, 0, 440, 523, 587, 0, 622, 0, 587, 523, 0, 0, 0, 784, 740, 698, 622, 659, 0, 415, 440, 523, 0, 440, 523, 587, 0, 784, 740, 698, 622, 659, 0, 392, 1047, 392, 1047, 392, 1047, 0, 0, 784, 740, 698, 622, 659, 0, 415, 440, 523, 0, 440, 523, 587, 0, 622
};
int durations3[] = {
  249, 249, 249, 249, 249, 249, 498, 498, 498, 498, 498, 498, 249, 249, 249, 249, 498, 249, 498, 249, 249, 249, 498, 332, 332, 332, 498, 249, 249, 249, 498, 249, 249, 747, 498, 249, 249, 249, 249, 498, 249, 498, 249, 249, 249, 498, 332, 332, 332, 498, 249, 249, 249, 498, 249, 249, 747, 498, 249, 249, 249, 498, 249, 249, 249, 249, 249, 249, 249, 249, 249, 498, 249, 249, 249, 498, 249, 249, 498, 498, 249, 249, 498, 498, 498, 498, 249, 249, 249, 498, 249, 249, 249, 249, 249, 249, 249, 249, 249, 498, 498, 249, 747, 498, 498, 996, 498, 249, 249, 249, 498, 249, 249, 249, 249, 249, 249, 249, 249, 249, 498, 249, 249, 249, 498, 249, 249, 498, 498, 249, 249, 498, 498, 498, 498, 249, 249, 249, 498, 249, 249, 249, 249, 249, 249, 249, 249, 249, 498, 498
};

int song_choice = 0;

char top_sequence[15];
char bottom_sequence[15];
int left_force = analogRead(A4);
int right_force = analogRead(A5);

void turn_lights()
{
if (lives == 3)
{
digitalWrite(LED_LEFT,HIGH);
digitalWrite(LED_CENTER,HIGH);
digitalWrite(LED_RIGHT,HIGH);
}
else if (lives == 2)
{
digitalWrite(LED_LEFT,LOW);
digitalWrite(LED_CENTER,HIGH);
digitalWrite(LED_RIGHT,HIGH);
}
else if (lives == 1)
{
digitalWrite(LED_LEFT,LOW);
digitalWrite(LED_CENTER,LOW);
digitalWrite(LED_RIGHT,HIGH);
} 
else
{
digitalWrite(LED_LEFT,LOW);
digitalWrite(LED_CENTER,LOW);
digitalWrite(LED_RIGHT,LOW);
}
}

void gameloop(int melody[], int durations[], int size)
{
  score = 0;
  for (int i = 0; i < 15; i++)
  {
    top_sequence[i] = '-';
    bottom_sequence[i] = '-';
  }
  lcd.setCursor(0, 0);
  lcd.print(">");
  lcd.print(top_sequence);
  lcd.setCursor(0, 1);
  lcd.print(">");
  lcd.print(bottom_sequence);

  bool need_click = false;

  for (int thisNote = 0; thisNote < size; thisNote++) {
  {
    tone(BUZZER, melody[thisNote], durations[thisNote] * .7);
    char next_note;
    int random_choice = random(0, 100);
    int count = 0;
    for (int i = 0; i < 14; i++)
    {
      top_sequence[i] = top_sequence[i + 1];
      bottom_sequence[i] = bottom_sequence[i + 1];
    }
    if (random_choice <= 15 && top_sequence[13] == '-' && size - thisNote > 15)
    {
      top_sequence[14] = 'L';
      bottom_sequence[14] = '-';
    }
    else if (random_choice <= 30 && bottom_sequence[13] == '-' && size - thisNote > 15)
    {
      top_sequence[14] = '-';
      bottom_sequence[14] = 'R';
    }
    else 
    {
      top_sequence[14] = '-';
      bottom_sequence[14] = '-';
    }

    lcd.setCursor(1, 0);
    lcd.print(top_sequence);

    lcd.setCursor(1, 1);
    lcd.print(bottom_sequence);

    if (top_sequence[0] == 'L' || bottom_sequence[0] == 'R')
    {
      need_click = true;
    }

    while (count < durations[thisNote] * tempos[song_choice - 1] * tempo_delay) // 2pi LOL
    {
      left_force = analogRead(A4);
      right_force = analogRead(A5);
      if (left_force > 100)
      {
        tempo_delay = 0.65;
        lcd.setCursor(1, 0);
        lcd.print("O");
        if (need_click && top_sequence[0] == 'L')
        {
          score++;
          analogWrite(GREEN, 255);
          need_click = false;
        }
      }
      else if (right_force > 100)
      {
        tempo_delay = 0.65;
        lcd.setCursor(1, 1);
        lcd.print("O");
        if (need_click && bottom_sequence[0] == 'R')
        {
          analogWrite(BLUE, 255);
          score++;
          need_click = false;
        }
      }
      else {
        tempo_delay = 1.0;
        analogWrite(GREEN, 0);
        analogWrite(BLUE, 0);
        analogWrite(RED, 0);
      }
      count++;
      delay(1);
    }
    if (need_click == true)
    {
      analogWrite(RED, 255);
      score--;
      lives--;
      need_click = false;
    }
  }
  turn_lights();
    noTone(BUZZER);
  if (lives == 0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("You died.");
    tone(BUZZER, 1000, 350);
    delay(500);
    tone(BUZZER, 200, 350);
    delay(500);
    lcd.clear();
    return;
  }
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    YOU WIN!    ");
  delay(1000);
  lcd.clear();
}

void song_select()
{
  int songDisplayed = 0;
  delay(500);
  left_force = 0;
  right_force = 0;
  while(left_force + right_force == 0)
  {
    songDisplayed = (songDisplayed == 3) ? 1 : songDisplayed += 1;
    int count = 0;
    lcd.setCursor(0, 0);
    lcd.print("Press button for");
    lcd.setCursor(0, 1);
    lcd.print("Music ");
    lcd.print(songDisplayed);
    while (count < 1000)
    {
      left_force = analogRead(A5);
      right_force = analogRead(A4);
      if (right_force + left_force > 0)
      {
        break;
      }
      count++;
      delay(1);
    }
    lcd.clear();
  }
  song_choice = songDisplayed;
  lcd.clear();
}

bool continue_check()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Score: ");
  lcd.print(score);
  delay(1500);
  int time_left = 10;
  int count = 0;
  song_choice = 0;
  while (time_left > 0)
  {
    left_force = analogRead(A4);
    right_force = analogRead(A5);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Continue (L)");
    lcd.setCursor(0, 1);
    lcd.print("End (R)     ");
    lcd.print(time_left);
    while (count < 1000)
    {
      left_force = analogRead(A4);
      right_force = analogRead(A5);
      if (left_force > 0)
      {
        lcd.clear();
        return true;
      }
      else if (right_force > 0)
      {
        lcd.clear();
        return false;
      }
      count++;
      delay(1);
    }
    time_left--;
    count = 0;
  }
  lcd.clear();
  return false;
}

void main_loop() 
{
  while(true)
  {
    song_select();
    lcd.setCursor(0, 0);
    lcd.print("Selected Song:");
    lcd.setCursor(0, 1);
    lcd.print(song_choice);
    delay(1000);
    lcd.clear();
    if (song_choice == 1)
    {
      gameloop(melody1, durations1, sizeof(melody1) / sizeof(int));
    }
    else if (song_choice == 2)
    {
      gameloop(melody2, durations2, sizeof(melody2) / sizeof(int));
    }
    else {
      gameloop(melody3, durations3, sizeof(melody3) / sizeof(int));
    }
    if (lives == 0 && continue_check()) {
      lives = 3;
      continue;
    }
    else if (lives > 0 && continue_check()) {
      lcd.clear();
      lives = 3;
      continue;
    }
    else {
      lcd.clear();
      break;
    }
  }
}

void loop()
{
  
}
