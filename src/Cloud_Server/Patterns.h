#include <Adafruit_NeoPixel.h>

#define PIN D4
#define NUMPIXELS 300
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void initializePixels();
void clearClouds();
void rainbowCycle();
uint32_t Wheel(byte WheelPos);
void sunrise();
void springDay();
void snow();
void sunset();
void rainbowSky();
void lightningStorm();
void scrollFlash();
void flash(int duration);
void dualFlash(int duration);
void lightningReset();
void rain();
void cloudy();

int interval1 = 1;
int interval2 = 5;
int interval3 = 20;
int interval4 = 50;
int interval5 = 100;
int interval6 = 200;

int rainbowCycleLoop0 = 0;
int sunriseLoop0 = 300;
int sunriseLoop1 = 250;
int sunriseLoop2 = 200;
int sunriseLoop3 = 150;
int sunriseLoop4 = 100;
int sunriseLoop5 = 50;
int snowLoop0 = 0;
int sunsetLoop0 = 90;
int rainbowSkyLoop0 = 0;
int rainLoop0 = 0;
int cloudyLoop0 = 100;
int cloudyLoop1 = 254;

int previousMillisArray[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void initializePixels() {
  pixels.begin();
  pixels.show();
  //  pixels.setBrightness(50);
}

void clearClouds() {
  Serial.println("CLEAR");
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 150));
  }
  pixels.show();
}

void rainbowCycle() {
  Serial.println("RAINBOWCYCLE");

  if (rainbowCycleLoop0 < 256) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[0] > interval1) {
      previousMillisArray[0] = currentMillis;
      for (int i = 0; i < pixels.numPixels(); i++) {
        pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + rainbowCycleLoop0) & 255));
      }
      pixels.show();
    }
    rainbowCycleLoop0++;
  } else if (rainbowCycleLoop0 >= 256) {
    rainbowCycleLoop0 = 0;
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void sunrise() {
  Serial.println("SUNRISE");

  if (sunriseLoop0 > ((NUMPIXELS / 6) * 5)) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[1] > interval5) {
      previousMillisArray[1] = currentMillis;
      pixels.setPixelColor(sunriseLoop0, 150, 50, 0);
      pixels.show();
    }
    sunriseLoop0++;
  } else if (sunriseLoop0 <= ((NUMPIXELS / 6) * 5)) {
    sunriseLoop0 = NUMPIXELS;
  }

  if (sunriseLoop1 > ((NUMPIXELS / 6) * 4)) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[2] > interval5) {
      previousMillisArray[2] = currentMillis;
      pixels.setPixelColor(sunriseLoop0, 150, 70, 0);
      pixels.show();
    }
    sunriseLoop1++;
  } else if (sunriseLoop1 <= ((NUMPIXELS / 6) * 4)) {
    sunriseLoop1 = ((NUMPIXELS / 6) * 5);
  }

  if (sunriseLoop2 > ((NUMPIXELS / 6) * 3)) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[3] > interval5) {
      previousMillisArray[3] = currentMillis;
      pixels.setPixelColor(sunriseLoop0, 150, 90, 0);
      pixels.show();
    }
    sunriseLoop2++;
  } else if (sunriseLoop2 <= ((NUMPIXELS / 6) * 3)) {
    sunriseLoop2 = ((NUMPIXELS / 6) * 4);
  }

  if (sunriseLoop3 > ((NUMPIXELS / 6) * 2)) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[4] > interval5) {
      previousMillisArray[4] = currentMillis;
      pixels.setPixelColor(sunriseLoop0, 150, 20, 0);
      pixels.show();
    }
    sunriseLoop3++;
  } else if (sunriseLoop3 <= ((NUMPIXELS / 6) * 2)) {
    sunriseLoop3 = ((NUMPIXELS / 6) * 3);
  }

  if (sunriseLoop4 > (NUMPIXELS / 6)) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[5] > interval5) {
      previousMillisArray[5] = currentMillis;
      pixels.setPixelColor(sunriseLoop0, 150, 40, 0);
      pixels.show();
    }
    sunriseLoop4++;
  } else if (sunriseLoop4 <= (NUMPIXELS / 6)) {
    sunriseLoop4 = ((NUMPIXELS / 6) * 2);
  }

  if (sunriseLoop5 > 0) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[6] > interval5) {
      previousMillisArray[6] = currentMillis;
      pixels.setPixelColor(sunriseLoop0, 150, 50, 0);
      pixels.show();
    }
    sunriseLoop5++;
  } else if (sunriseLoop5 <= 0) {
    sunriseLoop5 = (NUMPIXELS / 6);
  }
}

void springDay() {
  Serial.println("SPRING");

  for (int i = NUMPIXELS / 6; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, 0, 170, 175);
  }
  for (int j = 0; j < (NUMPIXELS / 6); j++) {
    pixels.setPixelColor(j, 255, 255, 0);
  }
  pixels.show();
}

void snow() {
  Serial.println("SNOW");

  if (snowLoop0 < NUMPIXELS) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[7] > interval4) {
      previousMillisArray[7] = currentMillis;
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, 17, 72, 143);
      }
      for (int j = 0; j < 12; j++) {
        for (int n = 0; n < 3; n++) {
          pixels.setPixelColor((j * 25 + n + snowLoop0) % 300, 232, 248, 250);
        }
      }
      pixels.show();
    }
    snowLoop0++;
  } else if (snowLoop0 >= NUMPIXELS) {
    snowLoop0 = 0;
  }
}

void sunset() {
  Serial.println("SUNSET");
  if (sunsetLoop0 < 220) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[8] > interval4) {
      previousMillisArray[8] = currentMillis;
      for (int i = 0; i < NUMPIXELS; i++) {
        if (sunsetLoop0 < 180) {
          pixels.setPixelColor(i, sunsetLoop0, 180 - sunsetLoop0, 0);
        } else {
          pixels.setPixelColor(i, sunsetLoop0, 0, 0);
        }
      }
      pixels.show();
    }
    sunsetLoop0++;
  } else if (sunsetLoop0 >= 220) {
    sunsetLoop0 = 90;
  }
}

void rainbowSky() {
  Serial.println("RAINBOW");

  if (rainbowSkyLoop0 == 0) {
    for (int i = 0; i < NUMPIXELS; i++) {
      if (i >= 0 && i < ((NUMPIXELS / 6) * 1))
        pixels.setPixelColor(i, 255, 0, 0);
      if (i >= ((NUMPIXELS / 6) * 1) && i < ((NUMPIXELS / 6) * 2))
        pixels.setPixelColor(i, 255, 165, 0);
      if (i >= ((NUMPIXELS / 6) * 2) && i < ((NUMPIXELS / 6) * 3))
        pixels.setPixelColor(i, 255, 255, 0);
      if (i >= ((NUMPIXELS / 6) * 3) && i < ((NUMPIXELS / 6) * 4))
        pixels.setPixelColor(i, 0, 255, 0);
      if (i >= ((NUMPIXELS / 6) * 4) && i < ((NUMPIXELS / 6) * 5))
        pixels.setPixelColor(i, 0, 0, 255);
      if (i >= ((NUMPIXELS / 6) * 5) && i < NUMPIXELS)
        pixels.setPixelColor(i, 255, 0, 255);
    }
    pixels.show();
    rainbowSkyLoop0 = 1;
  } else if (rainbowSkyLoop0 == 1) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, 0, 0, 0);
    }
    pixels.show();
    rainbowSkyLoop0 = 2;
  } else if (rainbowSkyLoop0 == 2) {
    for (int i = 0; i < NUMPIXELS; i++) {
      if (i >= 0 && i < ((NUMPIXELS / 6) * 1))
        pixels.setPixelColor(i, 255, 0, 0);
      if (i >= ((NUMPIXELS / 6) * 1) && i < ((NUMPIXELS / 6) * 2))
        pixels.setPixelColor(i, 255, 165, 0);
      if (i >= ((NUMPIXELS / 6) * 2) && i < ((NUMPIXELS / 6) * 3))
        pixels.setPixelColor(i, 255, 255, 0);
      if (i >= ((NUMPIXELS / 6) * 3) && i < ((NUMPIXELS / 6) * 4))
        pixels.setPixelColor(i, 0, 255, 0);
      if (i >= ((NUMPIXELS / 6) * 4) && i < ((NUMPIXELS / 6) * 5))
        pixels.setPixelColor(i, 0, 0, 255);
      if (i >= ((NUMPIXELS / 6) * 5) && i < NUMPIXELS)
        pixels.setPixelColor(i, 255, 0, 255);
    }
    pixels.show();
    rainbowSkyLoop0 = 0;
  }
}

void lightningStorm() {
  Serial.println("LIGHTNING");
  int num = 4; //Change Later if need be
  for (int i = 0; i < num; i++) {
    //Creates random number to see what bolt happens, 0 = scroll flash, 1-3 is flash, 4 = dual flash
    int randNum = random(4);
    switch (randNum) {
      case 0:
        scrollFlash();
        break;
      case 1:
        flash(random(999) + 500);
        break;
      case 2:
        flash(random(999) + 500);
        break;
      case 3:
        flash(random(999) + 500);
        break;
      case 4:
        dualFlash(random(999) + 500);
        break;
    }
    yield();
  }
}

//Scroll flash
//Should have lightning go throughout the cloud (in theory, no idea if it will look good or not)
void scrollFlash() {
  //scrolling
  for (int i = 0; i < 30; i++) {
    for (int j = 0; j < 10; j++) {
      pixels.setPixelColor(i * 10 + j, 255, 255, 255);
      yield();
    }
    yield();
    pixels.show();
  }
}

//Creats a single flash somehwere in the cloud with an int duration (in miliseconds)
void flash(int duration) {
  int randNum = random(2); //Random number 0-3 for use in deciding bolt location within cloud
  int min, max = 0; //min = minumum light value that the bolt will strike, max = maximum light value bolt will end
  //Determines whether the bolt will be in front, mid, or back of light string
  switch (randNum) {
    case 0: //Bolt in front
      min = random(24); //Starts between 0-24
      max = random(49) + 75; //Ends between 100 - 124
      break;
    case 1: //Bolt in middle
      min = random(49) + 125; //starts between 125 - 174
      max = random(49) + 175; //ends between 175 - 224
      break;
    case 2:
      min = random(49) + 200; //starts between 200 - 249
      max = random(49) + 250; //ends between 250 - 299
      break;
  }
  //activates chosen lights
  for (int i = min; i < max; i++) {
    pixels.setPixelColor(i, 255, 255, 255);
    yield();
  }
  pixels.show();
  delay(50); //Hopefully creates a quick flicker effect
  lightningReset();
  delay(50);
  for (int i = min; i < max; i++) {
    pixels.setPixelColor(i, 255, 255, 255);
    yield();
  }
  delay(duration);
  lightningReset(); //Resets lights to nothing at end of program
  yield();
}

//Creates 2 flashes of lightning, one in the front, one in the back
void dualFlash(int duration) {
  int min1, min2, max1, max2 = 0;
  min1 = random(49);
  max1 = random(49) + 100;
  min2 = random(49) + 150; //Numbers same as flash program, but 2 instead of 1
  max2 = random(49) + 250;
  //Displays first bolt
  for (int i = min1; i < max1; i++) {
    pixels.setPixelColor(i, 255, 255, 255);
    yield();
  }
  pixels.show();
  delay(50); //"Flicker effect"
  lightningReset();
  for (int i = min1; i < max1; i++) {
    pixels.setPixelColor(i, 255, 255, 255);
    yield();
  }
  delay(100); //waits 100 miliseconds until 2nd bolt
  //shows second bolt
  for (int i = min2; i < max2; i++) {
    pixels.setPixelColor(i, 255, 255, 255);
    yield();
  }
  pixels.show();
  delay(50); //"Flicker effect"
  for (int i = min2; i < max2; i++) {
    pixels.setPixelColor(i, 0, 0, 0);
    yield();
  }
  pixels.show();
  delay(50);
  for (int i = min2; i < max2; i++) {
    pixels.setPixelColor(i, 255, 255, 255);
    yield();
  }
  pixels.show();
  delay(duration); //shows bolt for duration
  lightningReset(); //resets lights to nothing at end of program
  yield();
}

//Quick method to reset lights to nothing
void lightningReset() {
  for (int i = 0; i < 300; i++) {
    pixels.setPixelColor(i, 0, 0, 0);
    yield();
  }
  pixels.show();
  yield();
}

void rain() {
  Serial.println("RAIN");

  if (rainLoop0 < 15) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[9] > interval6) {
      previousMillisArray[9] = currentMillis;
      for (int a = 0; a < NUMPIXELS; a++) {
        pixels.setPixelColor(a, 5, 5, 5); //set LEDs a gray color
      }
      for (int b = 0; b < 20; b++) {
        pixels.setPixelColor(15 * b + rainLoop0, 235, 235, 255); //set rain color
      }
      pixels.show();
    }
    rainLoop0++;
  } else if (rainLoop0 >= 15) {
    rainLoop0 = 0;
  }
}

void cloudy() {
  Serial.println("CLOUDY");

  if (cloudyLoop0 < 255) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[10] > interval2) {
      previousMillisArray[10] = currentMillis;
      for (int a = 0; a < NUMPIXELS; a++) {
        pixels.setPixelColor(a, cloudyLoop0, cloudyLoop0, cloudyLoop0); //set LEDs a gray color
      }
      pixels.show();
    }
    cloudyLoop0++;
  } else if (cloudyLoop0 >= 255) {
    cloudyLoop0 = 100;
  }

  if (cloudyLoop1 > 99) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[11] > interval2) {
      previousMillisArray[11] = currentMillis;
      for (int a = 0; a < NUMPIXELS; a++) {
        pixels.setPixelColor(a, cloudyLoop1, cloudyLoop1, cloudyLoop1); //set LEDs a gray color
      }
      pixels.show();
    }
    cloudyLoop1++;
  } else if (cloudyLoop1 <= 99) {
    cloudyLoop1 = 254;
  }
}
