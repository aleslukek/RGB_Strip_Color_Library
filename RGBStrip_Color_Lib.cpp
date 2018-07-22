/*
   Ales Lukek
 */

#include "RGBStrip_Color_Lib.h"

RGBStrip_Color_Lib::RGBStrip_Color_Lib(bool colorFormat){
        if(colorFormat == grb) {
                format = grb;
        }else if(colorFormat == rgb) {
                format = rgb;
        }
}


void RGBStrip_Color_Lib::rainbow(byte colorScale, byte *red, byte *green, byte *blue, float brightness){//colorScale shows the color, mode saves the colors in case they are needed, rainbow == 1 saves colors to rainbow, rainbow == 0 saves to colorr/g/b...
        byte Red = 0, Green = 0;
        if(colorScale > 255 || colorScale < 0) {
                colorScale = mobiosReturn(colorScale);
        }

        const byte boundaries[9] = {0,32,64,96,128,160,192,224,255};
        byte redBrightness[9] = {(byte)brightness, (byte)(brightness * 0.671), (byte)(brightness * 0.671), 0, 0, 0, (byte)(brightness * 0.333), (byte)(brightness * 0.671), (byte)brightness};
        byte greenBrightness[9] = {0, (byte)(brightness * 0.333), (byte)(brightness * 0.671), (byte)brightness, (byte)(brightness * 0.671), 0, 0, 0, 0};
        byte blueBrightness[9] = {0, 0, 0, 0, (byte)(brightness * 0.333), (byte)brightness, (byte)(brightness * 0.671), (byte)(brightness * 0.333), 0};

        for(byte i = 0; i < 8; i++) {
                if(colorScale >= boundaries[i] && colorScale <= boundaries[i+1]) {
                        Red = map(colorScale, boundaries[i], boundaries[i+1], redBrightness[i], redBrightness[i+1]);
                        Green = map(colorScale, boundaries[i], boundaries[i+1], greenBrightness[i], greenBrightness[i+1]);
                        *blue = map(colorScale, boundaries[i], boundaries[i+1], blueBrightness[i], blueBrightness[i+1]);
                }
        }

        if(format == rgb) {
                *red = Red;
                *green = Green;
                return;
        }else if(format == grb) {
                *red = Green;
                *green = Red;
                return;
        }
        return;
}



void RGBStrip_Color_Lib::white(byte *red, byte *green, byte *blue, float brightness){
        *red = brightness;
        *green = brightness;
        *blue = brightness;
        return;
}



void RGBStrip_Color_Lib::whiteTemperature(int colorTemperature, byte *red, byte *green, byte *blue, byte brightness){
        if(colorTemperature > 6100) { //normalises high temperature
                if(colorTemperature > 10000) {
                        colorTemperature = 10000;
                }
                colorTemperature = map(colorTemperature, 6100, 10000, 6100, 39000);
        }else if(colorTemperature < 2700) { //normalises low temperature
                if(colorTemperature < 1100) {
                        colorTemperature = 1100;
                }
                colorTemperature = map(colorTemperature, 1100, 2700, 1100, 2700);
        }
        double float_temperature = (log(colorTemperature) - 8.79) / 1.8;
        double float_brightness = (double)brightness / 255.0;
        if(float_brightness >= 0.0 && float_brightness <= 1.0) {
                uint8_t Red = redColor(float_temperature) * float_brightness;
                uint8_t Green = greenColor(float_temperature) * float_brightness;
                uint8_t Blue = blueColor(float_temperature) * float_brightness;
                if(format == rgb) {
                        *red = (byte)Red;
                        *green = (byte)Green;
                        *blue = (byte)Blue;
                }else if(format == grb) {
                        *red = (byte)Green;
                        *green = (byte)Red;
                        *blue = (byte)Blue;
                }
        }
        return;
}


uint8_t RGBStrip_Color_Lib::redColor(double temperature) {
        if(temperature >= -1.0) {
                if(temperature <= 0.0) {
                        return 255 * (1);
                }
                if(temperature <= 1.0) {
                        return 255 * (-0.990 * temperature * temperature * temperature + 2.34 * temperature * temperature - 1.99 * temperature + 0.970);
                }
        }
        return 0;
}

uint8_t RGBStrip_Color_Lib::greenColor(double temperature) {
        if(temperature >= -1.0) {
                if(temperature <= 0.0) {
                        return 255 * (-0.402 * temperature * temperature * temperature - 0.211 * temperature * temperature + 1.09 * temperature + 0.958);
                }
                if(temperature <= 1.0) {
                        return 255 * (-0.542 * temperature * temperature * temperature + 1.37 * temperature * temperature - 1.28 * temperature + 0.941);
                }
        }
        return 0;
}

uint8_t RGBStrip_Color_Lib::blueColor(double temperature) {
        if(temperature >= -1.0) {
                if(temperature <= -0.7) {
                        return 255 * (0);
                }
                if(temperature <= 0.0) {
                        return 255 * (0.0117 * temperature * temperature * temperature + 2.05 * temperature * temperature + 2.85 * temperature + 1.00);
                }
                if(temperature <= 1.0) {
                        return 255 * (1);
                }
        }
        return 0;
}



int RGBStrip_Color_Lib::mobiosReturn(int variable, int minValue, int maxValue){ //returns variable if it cycles above max as continuing from mins - default: min = 0, max = 255
        int result = variable;
        if(maxValue > minValue) {
                if(variable > maxValue) {
                        result = variable % (maxValue + 1) + minValue;
                        result = mobiosReturn(result, minValue, maxValue);
                }else if(variable < minValue) {
                        if(minValue == 0) {
                                result = (variable % maxValue) + maxValue + 1;
                                result = mobiosReturn(result, minValue, maxValue);
                        }else{
                                result = (variable % (maxValue + 1)) - minValue + maxValue + 1;
                                result = mobiosReturn(result, minValue, maxValue);
                        }
                }else{
                        result = variable;
                }
        }else if(minValue > maxValue) {
                result = mobiosReturn(variable, maxValue, minValue);
        }else{
                result = variable;
        }
        return result;
}
