
#include <Arduino.h>
#include <Buzzer.h>
#include "notes.h"

#define REST 0


#define SIXTEENTH_TIME 278	 // Time of a sixteenth note in microseconds
#define EIGHTH_TIME 417      // Time of an eighth note in microseconds
#define QUARTER_TIME 833     // Time of a quarter note in microseconds
#define HALF_TIME 1666       // Time of a half note in microseconds


//estonian anthem melody
int melody[] = { 
  NOTE_E4, EIGHTH_TIME,
  NOTE_C4, EIGHTH_TIME,
  NOTE_D4, EIGHTH_TIME, 
  NOTE_E4, QUARTER_TIME, 
  NOTE_A4, EIGHTH_TIME, 
  NOTE_B4, EIGHTH_TIME, 
  NOTE_E4, EIGHTH_TIME,
  NOTE_C5, HALF_TIME,
  NOTE_A4, QUARTER_TIME,
};

 

//Pin definition for the buzzer (GPIO15)
#define BUZZER_PIN D8
 
Buzzer buzzer(BUZZER_PIN);

void setup()
{
  Serial.begin(115200); // setting up serial connection parameter
  Serial.println("Booting");

  for(int i = 0; i < 18 ; i+=2)
  {
    buzzer.sound(melody[i], melody[i+1]); // Play the melody
  } 
}

void loop()
{
  delay(200); // Wait for 0.2 second
}