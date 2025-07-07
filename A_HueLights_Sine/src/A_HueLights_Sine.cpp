/* 
 * Project A_HueLights_Sine
 * Author: Nicole DeVoe Rogers
 * Date: 1 July 2025
 * Description: sub-project A for midterm, syning Hue Lights with sine wave for breathing
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "math.h"
#include "IoTClassroom_CNM.h"
#include "hue.h"


SYSTEM_MODE(MANUAL);

int BULB;
float t = 6; // time in seconds
float OFFSET = 1.75; //max inspiratory 
float AMPLITUDE = 1.75; //max expiratory
float V= 0.16; //period
float BRI; //brightness
float LH; //Last Hue

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected, 15000);


  WiFi.on ();
  WiFi.clearCredentials();
  WiFi.setCredentials("IoTNetwork");
  WiFi.connect();
  while (WiFi.connecting()) {
    Serial.printf(".");
  }
  Serial.printf("\n\n");

}


void loop() {
  for (BULB = 1; BULB <7; BULB++) {
    setHue(BULB, true, HueBlue, BRI, 255);
  }
  t = millis()/1000.0;
  BRI = 127.5*sin(2*M_PI*0.16*t)+127.5;
  setHue(5, true, HueBlue, BRI, 255);
  if ((millis()-LH)>30){
    LH = millis();
   setHue(BULB, true, HueBlue, BRI, 255);
    }

}