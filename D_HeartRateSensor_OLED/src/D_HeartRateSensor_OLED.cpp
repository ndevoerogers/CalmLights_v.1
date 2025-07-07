/* 
 * Project D_HeartRateSensor_OLED
 * Author: Nicole DeVoe Rogers
 * Date: 3 July 2025
 * Description: connecting hr sensor to read to serial monitor then, read to OLED screen
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "max30105.h"
#include "heartRate.h"



MAX30105 theSensor;
int IRvalue, BPM, BPMsum, count;
unsigned int deltaTime, lastBeat;
bool status;




SYSTEM_MODE(SEMI_AUTOMATIC);



void setup() {
    Serial.begin(9600);
    waitFor(Serial.isConnected, 5000);
    delay(500);

    WiFi.on ();
     WiFi.clearCredentials();
    WiFi.setCredentials("IoTNetwork");
    WiFi.connect();
  
    while (WiFi.connecting()) {
       Serial.printf(".");
        }
    Serial.printf("\n\n");

    status = theSensor.begin();
    delay (2000);
    if(status) {
        Serial.printf("The Sensor has Started \n");
        }
    else {
        Serial.printf("Sensor Not Starting\n");
    }
    delay (2000);
}


void loop() {
    IRvalue = theSensor.getIR();
    Serial.printf("IR Value = %i\n", IRvalue);
    if ((checkForBeat(IRvalue)) && (IRvalue > 1200)) {
        deltaTime = millis() - lastBeat;
        lastBeat = millis ();
        BPM = 60 / (deltaTime/1000.0);
        BPMsum = BPMsum + BPM;
        Serial.printf("IR = %i, BPM = %i\n", IRvalue, BPM);
        count++;
    }

    if (count == 10) {
        Serial.printf("\n***** PULSE *****\n");
        Serial.printf("Average BPM == %i\n", BPMsum/10);
        Serial.printf("***** PULSE *****\n\n");
        count = 0;
        BPMsum = 0;
    }
}
  

