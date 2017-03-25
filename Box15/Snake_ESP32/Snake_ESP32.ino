/**
 * Snake Game
 * Author : Anand Satya
 * Git Repo: 
 * Description: Basic snake game was implemented
 * using ESP32 and oled display (SSD1306)
 */

#include <Keypad.h>
#include <Wire.h>
#include "SSD1306.h" 
#include <QList.h>
#include "QList.cpp" 

// Initialize the OLED display using Wire library
SSD1306  display(0x3c, 21, 22);
// Initialize Keypad Settings 
const byte ROWS = 4; 
const byte COLS = 4; 
// Define the symbols on the buttons of the keypads
// For Snake game we will only use first column 
// as direction keys. L - Left; U - Up; D - Down; R - Right 
char hexaKeys[ROWS][COLS] = {
  {'L','*','*','*'},
  {'U','*','*','*'},
  {'D','*','*','*'},
  {'R','*','*','*'}
};
byte rowPins[ROWS] = {12, 14, 27, 26};    //connect to the row pinouts of the keypad
byte colPins[COLS] = {25, 999, 999, 999}; //Using only one column of Pins so setting remaining pins to 999
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// Initialise Snake game variables
char direction = 'R';
long timeSinceLastScreenUpdate = 0;
int GAME_RefreshDuration = 1000;
int Game_status = 1;  //1 - Running, 2 - GameEnd
int X = 3;
int Y = 4;
int Score = 0;
QList<int> Food_X;
QList<int> Food_Y;
QList<int> Snake_X;
QList<int> Snake_Y;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  // Update Food Location
  Food_X.push_back(random(0,24));
  Food_Y.push_back(random(0,11));

  Food_X.push_back(random(0,24));
  Food_Y.push_back(random(0,11));
}

void loop() {

  if (Game_status == 1) {
    //Update Snake Direction
    char new_direction = customKeypad.getKey();
    if  (new_direction == 'U' || new_direction == 'D' || new_direction == 'L' || new_direction == 'R') {
      direction = new_direction;
    }

    //Update Snake Location 
    if (millis() - timeSinceLastScreenUpdate > GAME_RefreshDuration) { 
      if (direction == 'R') {
        Serial.println(direction);
        X = X + 1;
      } else if (direction == 'L') {
        Serial.println(direction);
        X = X - 1;
      } else if (direction == 'U') {
        Serial.println(direction);
        Y = Y + 1;
      } else if (direction == 'D') {
        Serial.println(direction);
        Y = Y - 1;
      }

      display.clear();
      SwitchOnPixel(X,Y);
      DisplayFood();
      display.drawString(110, 2, String(Score));
      display.display();
      timeSinceLastScreenUpdate = millis();

      //Check if game should end
      ShouldGameEnd();
    }
  } else {
    // Print EndGame Screen
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 22, "Game Over :(");
    display.drawString(55, 40, "Your Score :");
    display.drawString(95, 40, String(Score));
    display.display();
  }
  
  delay(10);
}

void DisplayFood() {
   int same_list_size = Food_X.length();
   Serial.println("Food Length");
   Serial.print(same_list_size);

   for (int i=0; i < same_list_size; i++) {
    if ( !(X == Food_X.get(i) && Y == Food_Y.get(i)) ) {
      SwitchOnPixel(Food_X.get(i), Food_Y.get(i));
    } else {
      // Snake found food increase score and 
      // create new food. Make the snake
      // move faster.
      Score = Score + 1;
      GAME_RefreshDuration = 0.90 * GAME_RefreshDuration;
      Food_X[i] = random(0,24);
      Food_Y[i] = random(0,11);
      SwitchOnPixel(Food_X.get(i), Food_Y.get(i));
    }
   }
}

void SwitchOnPixel(int X, int Y) {
  if ( (X >= 0 && X <= 24) && (Y >=0 && Y <=11)) {
    // Fill the rectangle
    display.fillRect((X*5) , (Y*5), 5, 5);
     
  }
}

int ShouldGameEnd() {
  if ((X < 0 || X > 24) || (Y <0 || Y >11)) {
    Game_status = 0;
  }
}
