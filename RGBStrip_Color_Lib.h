/*
Ales Lukek
*/

#include "Arduino.h"

#define rgb 0
#define grb 1

class RGBStrip_Color_Lib {
public:
//constructor
RGBStrip_Color_Lib(bool colorFormat = rgb);        //colorFormat is rgb (default) 0 or grb 1. All colors are returned that way.

//colors
void rainbow(byte colorScale, byte *red, byte *green, byte *blue, float brightness = 255);        //RGB rainbow by scale. Input colorScale number (byte from 0 to 255) and it returns colors. 0 is red, goes to yellow, green, blue, purple, red. Cyclic scale special to Neopixel strip. Increased yellow and decreased green.
void white(byte *red, byte *green, byte *blue, float brightness = 255);        //returns red, green, blue numbers, max values. Max white.
void whiteTemperature(int colorTemperature, byte *red, byte *green, byte *blue, byte brightness = 255);        //returns white color of different temperatures. Input color temperature (in Kelvins) from 1100K to 10000K

private:
int mobiosReturn(int variable, int minValue = 0, int maxValue = 255);        //given variable returns to value in min/max window.
uint8_t redColor(double temperature);        //Red for white Temperature function.
uint8_t greenColor(double temperature);        //Green for white Temperature function.
uint8_t blueColor(double temperature);        //Blue for white Temperature function.
bool format;        //rgb or grb format used in rgb return.

};
