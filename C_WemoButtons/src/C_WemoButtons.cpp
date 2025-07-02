/* 
 * Project C_WemoButtons
 * Author: Nicole DeVoe ROgers
 * Date: 2 July 2025
 * Description: Midterm Sub-Project button to two wemos
 */


#include "Particle.h"
#include "IoTClassroom_CNM.h"



SYSTEM_MODE(MANUAL);


int wemo =0;
const int BUTTONPIN = D3;
bool onOff;
int i;
Button greyButton(BUTTONPIN);
IoTTimer timer;



void setup() {
Serial.begin(9600);
waitFor(Serial.isConnected, 15000);

timer.startTimer (5000);

WiFi.on();
WiFi.clearCredentials();
WiFi.setCredentials("IoTNetwork");
WiFi.connect();
while (WiFi.connecting()) {
Serial.printf(".");
}
Serial.printf("\n\n");
}


void loop() {
  
  if (greyButton.isClicked()) {
    onOff = !onOff;
    Serial.printf("%i\n", onOff);
    if (onOff == TRUE ){
      for(i =0; i <= 5; i++){
        wemoWrite(i, HIGH);
        delay(200);  
      }
    }
    if (onOff == FALSE) {
      for(i =0; i <= 5; i++){
        wemoWrite(i, LOW);
        delay(200);
      }
    }
  }
}
