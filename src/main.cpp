
#include <Arduino.h>
#include <Buzzer.h>
#include <ittiot.h>

#include "notes.h"

#define REST 0


#define SIXTEENTH_TIME 278	 // Time of a sixteenth note in microseconds
#define EIGHTH_TIME 417      // Time of an eighth note in microseconds
#define QUARTER_TIME 833     // Time of a quarter note in microseconds
#define HALF_TIME 1666       // Time of a half note in microseconds


#define MOTION_TOPIC "ESP23/motion"
#define WIFI_NAME "TalTech"
#define WIFI_PASSWORD ""

//Pin definition for the buzzer (GPIO15)
#define BUZZER_PIN D8

//Estonian anthem melody
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

bool isPlaying = false;
 
Buzzer buzzer(BUZZER_PIN);

void iot_received(String topic, String msg)
{ 
  // Custom
  if(topic == MOTION_TOPIC)
  {
    if(msg == "1")
    {
      isPlaying = true;
    }
  }
  
}
 
void iot_connected()
{
  Serial.println("MQTT connected callback");

  // Custom
  iot.subscribe(MOTION_TOPIC);
}

// Custom function
void playAnthem()
{
  for(int i = 0; i < 18 ; i+=2)
  {
    buzzer.sound(melody[i], melody[i+1]); 
  } 
}

void setup()
{
  Serial.begin(115200); 
  Serial.println("Booting");
 
  iot.setConfig("wname", WIFI_NAME);
  iot.setConfig("wpass", WIFI_PASSWORD);
  iot.setConfig("msrv", "193.40.245.72");
  iot.setConfig("mport", "1883");
  iot.setConfig("muser", "test");
  iot.setConfig("mpass", "test");


  iot.printConfig();
  iot.setup(); 
}

void loop()
{
  iot.handle(); 
  delay(200);


  // Custom
  if(isPlaying)
  {
    playAnthem();
    isPlaying = false;
  }
}