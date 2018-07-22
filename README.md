RGBStrip_Color_Lib.h for Arduino
=========================

RGBStrip_Color_Lib library is an Arduino RGB Strip colors library
##### TLDR;
 1. one-dimensional variable that returns red, green and blue values of a rainbow,
 2. color temperatrue of a white color (from 1000K to 10000K),


------

#### To initialize class:
```
RGBStrip_Color_Lib colors(0);
```

rgb input depends on your strip -> if it is rgb (0) or grb (1). For most cases rgb should be sufficient, becuase Strip library also takes care of this (Adafruit Neopixel library for example). If no input variable is given rgb is taken as default.

------

#### Rainbow

Rainbow function takes one-dimensional byte value - colorScale (from 0 to 255) and returns red, green and blue values. colorScale returns cycle of rainbow from red and goes to orange, yellow, green, blue, purple, pink and 255 back to red. Red, green and blue values are passed as pointers, so you can operate on the values as you please before passing them to strip. Function also takes brightness byte value (from 0 to 255). If no brightness value is given, max (255) is taken as default.
```
colors.rainbow(colorScale, &red, &green, &blue, brightness);
```

------

#### White

White function just returns red, green and blue variables as max - brightness value. If no brightness value is given, default is taken (255).
```
colors.white(&red, &green, &blue, brightness);
```

------

#### White Temperature

White temperature function takes color temperature value (from 1000K to 10000K) and returns white color of given temperature. If no brightness value is given, default is taken (255). Mind you, color temperature is not calibrated. It was tested, but not by any scientific measurement device.
```
colors.whiteTemperature(colorTemperature, &red, &green, &blue, brightness);
```


------

**Everything here is in public domain, use it, abuse it, change it, make it fly!**
