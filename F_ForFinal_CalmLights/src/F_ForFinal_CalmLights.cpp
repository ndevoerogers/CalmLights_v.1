/* 
 * Project F_ForFinal_CalmLights
 * Author: Nicole DeVoe Rogers
 * Date: 7 July 2025
 * Description: combining sub-projects A, B, C, and E
 */


#include "Particle.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
#include "Adafruit_BME280.h"
#include "IoTClassroom_CNM.h"
#include "math.h"
#include "neopixel.h"



bool status; // BME
float tempc, tempf; //BME
float humidRH; //BME
const int OLED = -1; //OLED
const int ADDRESS = 0x76; //BME
const int OLEDADDRESS = 0x3C; //OLED
const int BULB = 6; //hue
int BRI = 170; //hue
const int PIXELCOUNT = 12; //Pixel ring
float t; //Pixel ring
float y; //Pixel ring 
float OFFSET = 127.5; //Pixel ring
float AMPLITUDE = 127.5; //Pixel ring
float V= 0.1; //Pixel ring 
int wemo = 0; //wemos
const int BUTTONPIN = D3; //wemos
int i; //wemos
bool onOff; //wemos
Button greyButton(BUTTONPIN); //wemos





void pixelFill(int start, int end, int color); //pixel fill
Adafruit_BME280 bme; //BME
IoTTimer timer; //OLED
Adafruit_SSD1306 display (OLED); //OLED
Adafruit_NeoPixel pixel (PIXELCOUNT, SPI1, WS2812B); //pixel ring



SYSTEM_MODE(SEMI_AUTOMATIC);



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
  Serial.begin(9600);
  waitFor(Serial.isConnected, 5000);

  status = bme.begin(ADDRESS);
  if (status == false) {
    Serial.printf("BME at address 0x%02X failed to start", ADDRESS);
  }
  display.begin(SSD1306_SWITCHCAPVCC, OLEDADDRESS);
  display.setTextSize(1);
  display.setRotation (0);
  display.setTextColor(WHITE);

  timer.startTimer(500);

  if (ADDRESS )

  pixel.begin();
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
  display.clearDisplay();
  tempc = bme.readTemperature();
  humidRH = bme.readHumidity();


  tempf = (tempc *9/5.0) + 32;
  if (timer.isTimerReady()) {
    Serial.printf("Temperature %0.1f\nHumidity %0.1f\n", tempf, humidRH);
    display.setCursor (0,0);
    display.printf("Temperature %0.1f\nHumidity %0.1f\n", tempf, humidRH);
    display.display ();
    timer.startTimer(500);
  }
  t = millis() / 1000.0;
  y = OFFSET*sin(2*M_PI*V*t)+AMPLITUDE;
  pixel.setBrightness((int)y);
  pixel.show ();
  pixelFill(0,12,blue);
  pixel.show();
  Serial.printf("%f\n",y);

  if ((tempf >78)){ //|| (humidRH >50)) {
    setHue(BULB, true, HueBlue, BRI, 255);

  }
  else { 
    setHue(BULB, true, HueYellow, BRI, 255);
  }
  // t = millis()/1000.0;

  // setHue(5, true, HueBlue, BRI, 255);
  // if ((millis()-LH)>30){
  //   LH = millis();
  //   setHue(BULB, true, HueBlue, BRI, 255);
  // }
}



void pixelFill(int start, int end, int color){
  int p; 
  for (p=start; p<=end; p++){
    pixel.setPixelColor (p, color);
  }

}
