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
void seizureMode();
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
int seizureModeLoop0 = 0;
int rainLoop0 = 0;
int cloudyLoop0 = 100;
int cloudyLoop1 = 254;
int scrollFlashLoop0 = 0;
int flashNum = 0;
int dualFlashNum = 0;
int minFlash = 0;
int maxFlash = 0;

boolean scrollFlashOn = false;
boolean flashOn = false;
boolean dualFlashOn = false;
boolean firstFlashOn = true;
boolean delayOneDone = false;
boolean delayTwoDone = false;
boolean delayThreeDone = false;

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

  for (int i = 300; i > 250; i--) {
    pixels.setPixelColor(i, 150, 50, 0);
  }
  for (int i = 250; i > 200; i--) {
    pixels.setPixelColor(i, 150, 70, 0);
  }
  for (int i = 200; i > 150; i--) {
    pixels.setPixelColor(i, 150, 90, 0);
  }
  for (int i = 150; i > 100; i--) {
    pixels.setPixelColor(i, 150, 20, 0);
  }
  for (int i = 100; i > 50; i--) {
    pixels.setPixelColor(i, 150, 40, 0);
  }
  for (int i = 50; i > 0; i--) {
    pixels.setPixelColor(i, 150, 50, 0);
  }
  pixels.show();
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
    if (currentMillis - previousMillisArray[7] > interval5 /*6*/) {
      previousMillisArray[7] = currentMillis;
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, 17, 72, 143);
      }
      for (int j = 0; j < 12; j++) {
        for (int n = 0; n < 3; n++) {
          pixels.setPixelColor((j * 5/*10*/ + n + snowLoop0) % NUMPIXELS, 232, 248, 250);
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
  int i;
  for (i = 0; i < (NUMPIXELS / 3); i++) {
    pixels.setPixelColor(i, 150, 20, 0);
  }
  for (i = ((NUMPIXELS / 3) + 1); i < (NUMPIXELS / 2); i++) {
    pixels.setPixelColor(i, 150, 90, 0);
  }
  for (i = ((NUMPIXELS / 2) + 1); i < ((NUMPIXELS / 6) * 5); i++) {
    pixels.setPixelColor(i, 150, 50, 0);
  }
  for (i = (((NUMPIXELS / 6) * 5) + 1); i < ((NUMPIXELS / 30) * 26); i++) {
    pixels.setPixelColor(i, 150, 50, 0);
  }
  for (i = (((NUMPIXELS / 30) * 26) + 1); i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, Wheel(((i * 256 / NUMPIXELS)) & 255));
  }
  pixels.show();
}

void seizureMode() {
  Serial.println("SEIZURE");
  if (seizureModeLoop0 == 0) {
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
    seizureModeLoop0 = 1;
  } else if (seizureModeLoop0 == 1) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, 0, 0, 0);
    }
    pixels.show();
    seizureModeLoop0 = 2;
  } else if (seizureModeLoop0 == 2) {
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
    seizureModeLoop0 = 0;
  }
}

void lightningStorm() {
  Serial.println("LIGHTNING");
  if (scrollFlashOn == true) {
    scrollFlash();
  } else if (flashOn == true) {
    flash(flashNum);
  } else if (dualFlashOn == true) {
    dualFlash(dualFlashNum);
  } else {
    //Creates random number to see what bolt happens, 0 = scroll flash, 1-3 is flash, 4 = dual flash
    int randNum = random(4);
    switch (randNum) {
      case 0:
        scrollFlash();
        scrollFlashOn = true;
        break;
      case 1:
        flashNum = random(999) + 500;
        flash(flashNum);
        flashOn = true;
        firstFlashOn = true;
        break;
      case 2:
        flashNum = random(999) + 500;
        flash(flashNum);
        flashOn = true;
        firstFlashOn = true;
        break;
      case 3:
        flashNum = random(999) + 500;
        flash(flashNum);
        flashOn = true;
        firstFlashOn = true;
        break;
      case 4:
        dualFlashNum = random(999) + 500;
        dualFlash(dualFlashNum);
        dualFlashOn = true;
        break;
    }
  }
}

//Scroll flash
//Should have lightning go throughout the cloud (in theory, no idea if it will look good or not)
void scrollFlash() {
  //scrolling
  if (scrollFlashLoop0 < 30) {
    //for (int i = 0; i < 30; i++) {
    for (int j = 0; j < 10; j++) {
      pixels.setPixelColor(scrollFlashLoop0 * 10 + j, 255, 255, 255);
    }
    pixels.show();
    scrollFlashLoop0++;
  } else {
    scrollFlashOn = false;
  }
}

//Creats a single flash somehwere in the cloud with an int duration (in miliseconds)
void flash(int duration) {
  //  int min, max = 0; //min = minumum light value that the bolt will strike, max = maximum light value bolt will end
  //Determines whether the bolt will be in front, mid, or back of light string
  if (firstFlashOn == true) {
    int randNum = random(2); //Random number 0-3 for use in deciding bolt location within cloud
    switch (randNum) {
      case 0: //Bolt in front
        minFlash = random(24); //Starts between 0-24
        maxFlash = random(49) + 75; //Ends between 100 - 124
        break;
      case 1: //Bolt in middle
        minFlash = random(49) + 125; //starts between 125 - 174
        maxFlash = random(49) + 175; //ends between 175 - 224
        break;
      case 2:
        minFlash = random(49) + 200; //starts between 200 - 249
        maxFlash = random(49) + 250; //ends between 250 - 299
        break;
    }
    firstFlashOn = false;
  }
  //activates chosen lights
  for (int i = minFlash; i < maxFlash; i++) {
    pixels.setPixelColor(i, 255, 255, 255);
  }
  pixels.show();

  if (delayOneDone == false) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[12] > interval5) {
      previousMillisArray[12] = currentMillis;
      lightningReset();
      delayOneDone = true;
    }
  }

  if (delayTwoDone == false && delayOneDone == true) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[13] > interval5) {
      previousMillisArray[13] = currentMillis;
      delayTwoDone = true;
    }
  }

  for (int i = minFlash; i < maxFlash; i++) {
    pixels.setPixelColor(i, 255, 255, 255);
  }

  if (delayThreeDone == false && delayTwoDone == true && delayOneDone == true) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[14] > duration) {
      previousMillisArray[14] = currentMillis;
      lightningReset(); //Resets lights to nothing at end of program
      delayThreeDone = true;
      flashOn = false;

      delayOneDone = false;
      delayTwoDone = false;
      delayThreeDone = false;
    }
  }
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
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, 0, 0, 0);
  }
  pixels.show();
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
        pixels.setPixelColor(10 * b + rainLoop0, 235, 235, 255); //set rain color
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

  if (cloudyLoop0 < 125) {
    for (int a = 0; a < NUMPIXELS; a++) {
      pixels.setPixelColor(a, cloudyLoop0, cloudyLoop0, cloudyLoop0); //set LEDs a gray color
    }
    cloudyLoop0++;
  } else if (cloudyLoop0 >= 125) {
    cloudyLoop0 = 100;
  }
  pixels.show();
}
