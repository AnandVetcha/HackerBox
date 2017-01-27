//
// Arduino LED+Buzzer Beacon using Morse Code
//
// Original Author:
// By Mark VandeWettering, K6HX
// Email: k6hx@arrl.net
// Blog: http://brainwagon.org 
//
// Above code was slightly modified to interface a buzzer.
//

struct t_mtab { char c, pat; } ;

struct t_mtab morsetab[] = {
  {'.', 106},
  {',', 115},
  {'?', 76},
  {'/', 41},
  {'A', 6},
  {'B', 17},
  {'C', 21},
  {'D', 9},
  {'E', 2},
  {'F', 20},
  {'G', 11},
  {'H', 16},
  {'I', 4},
  {'J', 30},
  {'K', 13},
  {'L', 18},
  {'M', 7},
  {'N', 5},
  {'O', 15},
  {'P', 22},
  {'Q', 27},
  {'R', 10},
  {'S', 8},
  {'T', 3},
  {'U', 12},
  {'V', 24},
  {'W', 14},
  {'X', 25},
  {'Y', 29},
  {'Z', 19},
  {'1', 62},
  {'2', 60},
  {'3', 56},
  {'4', 48},
  {'5', 32},
  {'6', 33},
  {'7', 35},
  {'8', 39},
  {'9', 47},
  {'0', 63}
} ;

#define N_MORSE  (sizeof(morsetab)/sizeof(morsetab[0]))

#define SPEED  (10)  // SET THE MORSE SPEED in WPM
#define DOTLEN  (1200/SPEED)
#define DASHLEN  (3*(1200/SPEED))

int LEDpin = 13;
int Buzzer = 11;       // Buzzer Connection
int buzzer_vol = 300;  // Buzzer volume

void setup()
{
  pinMode(LEDpin, OUTPUT) ;
  pinMode(Buzzer, OUTPUT) ;
}

void loop()
{
  sendmsg("SOS") ;
  delay(3000) ;
}

void dash()
{
  digitalWrite(LEDpin, HIGH) ;
  analogWrite(Buzzer, buzzer_vol);
  delay(DASHLEN);
  digitalWrite(LEDpin, LOW) ;
  analogWrite(Buzzer, 0);
  delay(DOTLEN) ;
}

void dit()
{
  digitalWrite(LEDpin, HIGH);
  analogWrite(Buzzer, buzzer_vol);
  delay(DOTLEN);
  digitalWrite(LEDpin, LOW);
  analogWrite(Buzzer, 0);
  delay(DOTLEN);
}

void send(char c)
{
  int i ;
  if (c == ' ') {
    delay(7*DOTLEN) ;
    return ;
  }
  for (i=0; i<N_MORSE; i++) {
    if (morsetab[i].c == c) {
      unsigned char p = morsetab[i].pat ;

      while (p != 1) {
          if (p & 1)
            dash() ;
          else
            dit() ;
          p = p / 2 ;
      }
      delay(2*DOTLEN) ;
      return ;
    }
  }
}

void sendmsg(char *str)
{
  while (*str)
    send(*str++) ;
}
