/*
Simple demonstration of a rainbow function. It cycles through rainbow, each pixel is dimmer than the other,
enjoy.
*/

#include <Adafruit_NeoPixel.h>
#include <RGBStrip_Color_Lib.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define rgb 0     //for rgb strip
#define grb 1     //for grb strip

#define PIN            6      //To what pin is the strip connected to.
#define NUMPIXELS      10     //How many pixels are in the strip.

int colorScale = 0;      //On scale from 0 to 255 it returns red, green, blue values of a rainbow.
byte jumpColor = 3;      //What is the jump from one colorScale to another.
byte brightness = 255;   //Pixel brightness. Optional, if not in rainbow function than it will take default value of 255 (max).
#define delayval  250

//Constructors
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
RGBStrip_Color_Lib colors(rgb);     //input rgb or grb, depends on your strip. If there is no input, it will go to default rgb.

void setup() {
  Serial.begin(115200);
  pixels.begin();     // This initializes the NeoPixel library.
}

void loop() {
  byte red = 0, green = 0, blue = 0;      //Red, green and blue MUST be byte type.
  colorScale += jumpColor;     //This changes color for every loop.
  if(colorScale > 255){
    colorScale -= 256;
  }else if(colorScale < 0){
    colorScale -= 255;
  }

  for(int i=0;i<NUMPIXELS;i++){
    colors.rainbow(colorScale, &red, &green, &blue, brightness);
    brightness -= (255/NUMPIXELS);     //Every pixel is darker than the one before

    // Prints colorScale and rgb values.
    Serial.print("Color Scale: ");
    Serial.print(colorScale);
    Serial.print(" Pixel number: ");
    Serial.print(i+1);
    Serial.print(", Red: ");
    Serial.print(red);
    Serial.print(", Green: ");
    Serial.print(green);
    Serial.print(", Blue: ");
    Serial.println(blue);

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(red, green, blue));

    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  brightness = 255;  //resets brightness to max
  delay(delayval); // Delay for a period of time (in milliseconds).
}
