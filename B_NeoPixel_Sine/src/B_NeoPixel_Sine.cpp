/* 
 * Project B_NeoPixel_Sine
 * Author: Nicole DeVoe Rogers
 * Date: 1 July 2025
 * Description: NeoPixels set to sine wave, sub-project for midterm1
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */


#include "Particle.h"
#include "math.h"
#include "neopixel.h"
#include "Colors.h"

SYSTEM_MODE(MANUAL);

const int PIXELCOUNT = 12;
float t = 6;
float y;
void pixelFill(int start, int end, int color);

Adafruit_NeoPixel pixel (PIXELCOUNT, SPI1, WS2812B);



void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected, 2000);


  WiFi.on ();
  WiFi.clearCredentials();
  WiFi.setCredentials("IoTNetwork");
  WiFi.connect();
  while (WiFi.connecting()) {
    Serial.printf(".");
  }
  Serial.printf("\n\n");

 
  pixel.begin();

 
  }


void loop(){   
  y = 127.5*sin(2*M_PI*0.16*t)+127.5;
  pixel.setBrightness((int)y);
  pixelFill(0,12,blue);
 
  Serial.printf("%i\n",y);
pixel.show();
  
}

void pixelFill(int start, int end, int color){
  int p; 
  for (p=start; p<=end; p++){
    pixel.setPixelColor (p, color);
    }


  }
