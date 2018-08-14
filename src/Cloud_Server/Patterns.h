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
int interval6;  //variable

int previousMillisArray[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void initializePixels() {
  pixels.begin();
  pixels.show();
}

void clearClouds() {
  Serial.println("CLEAR");
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 150));
    pixels.show();
    yield();
  }
}

void rainbowCycle() {
  Serial.println("RAINBOW");
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[0] > interval1) {
      previousMillisArray[0] = currentMillis;
      for (i = 0; i < pixels.numPixels(); i++) {
        pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
        yield();
      }
      pixels.show();
    }
    yield();
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
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[1] > interval5) {
      previousMillisArray[1] = currentMillis;
      pixels.setPixelColor(i, 150, 50, 0);
      pixels.show();
    }
    yield();
  }
  for (int i = 250; i > 200; i--) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[2] > interval5) {
      previousMillisArray[2] = currentMillis;
      pixels.setPixelColor(i, 150, 70, 0);
      pixels.show();
    }
    yield();
  }

  for (int i = 200; i > 150; i--) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[3] > interval5) {
      previousMillisArray[3] = currentMillis;
      pixels.setPixelColor(i, 150, 90, 0);
      pixels.show();
    }
    yield();
  }

  for (int i = 150; i > 100; i--) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[4] > interval5) {
      previousMillisArray[4] = currentMillis;
      pixels.setPixelColor(i, 150, 20, 0);
      pixels.show();
    }
    yield();
  }

  for (int i = 100; i > 50; i--) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[5] > interval5) {
      previousMillisArray[5] = currentMillis;
      pixels.setPixelColor(i, 150, 40, 0);
      pixels.show();
    }
    yield();
  }

  for (int i = 50; i > 0; i--) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[6] > interval5) {
      previousMillisArray[6] = currentMillis;
      pixels.setPixelColor(i, 150, 50, 0);
      pixels.show();
    }
    yield();
  }
}

void springDay() {
  Serial.println("SPRING");
  for (int i = 50; i < 300; i++) {
    pixels.setPixelColor(i, 0, 170, 175);
    pixels.show();
    yield();
  }
  for (int i = 0; i < 50; i++) {
    pixels.setPixelColor(i, 255, 255, 0);
    pixels.show();
    yield();
  }
}

void snow() {
  Serial.println("SNOW");
  int x = 0;
  for (x = 0; x < 300; x++) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[7] > interval4) {
      previousMillisArray[7] = currentMillis;
      for (int i = 0; i < 300; i++) {
        pixels.setPixelColor(i, 17, 72, 143);
        yield();
      }
      for (int i = 0; i < 12; i++) {
        for (int n = 0; n < 3; n++) {
          pixels.setPixelColor((i * 25 + n + x) % 300, 232, 248, 250);
          yield();
        }
        yield();
      }
      pixels.show();
      yield();
    }
  }
}

void sunset() {
  Serial.println("SUNSET");
  for (int k = 90; k < 220; k++) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisArray[8] > interval4) {
      previousMillisArray[8] = currentMillis;
      for (int i = 0; i < 300; i++) {
        if (k < 180) {
          pixels.setPixelColor(i, k, 180 - k, 0);
        } else {
          pixels.setPixelColor(i, k, 0, 0);
        }
        yield();
      }
      pixels.show();
    }
    yield();
  }
}

void rainbowSky() {
  Serial.println("RAINBOW");
  for (int timer = 0; timer < 2; timer++) {
    for (int i = 0; i < 300; i++) {
      if (i >= 0 && i < 50)
        pixels.setPixelColor(i, 255, 0, 0);
      if (i >= 50 && i < 100)
        pixels.setPixelColor(i, 255, 165, 0);
      if (i >= 100 && i < 150)
        pixels.setPixelColor(i, 255, 255, 0);
      if (i >= 150 && i < 200)
        pixels.setPixelColor(i, 0, 255, 0);
      if (i >= 200 && i < 250)
        pixels.setPixelColor(i, 0, 0, 255);
      if (i >= 250 && i < 300)
        pixels.setPixelColor(i, 255, 0, 255);
      yield();
    }
    pixels.show();
    for (int i = 0; i < 300; i++) {
      pixels.setPixelColor(i, 0, 0, 0);
      pixels.show();
      yield();
    }
    for (int i = 0; i < 300; i++) {
      if (i >= 0 && i < 50)
        pixels.setPixelColor(i, 255, 0, 0);
      if (i >= 50 && i < 100)
        pixels.setPixelColor(i, 255, 165, 0);
      if (i >= 100 && i < 150)
        pixels.setPixelColor(i, 255, 255, 0);
      if (i >= 150 && i < 200)
        pixels.setPixelColor(i, 0, 255, 0);
      if (i >= 200 && i < 250)
        pixels.setPixelColor(i, 0, 0, 255);
      if (i >= 250 && i < 300)
        pixels.setPixelColor(i, 255, 0, 255);
      pixels.show();
      yield();
    }
    yield();
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
  for (int i = 0; i < 600; i++) {
    for (int x = 0; x < 15; x++) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillisArray[9] > interval3) {
        previousMillisArray[9] = currentMillis;
        for (int a = 0; a < 300; a++) {
          pixels.setPixelColor(a, 5, 5, 5); //set LEDs a gray color
          yield();
        }
        for (int b = 0; b < 20; b++) {
          pixels.setPixelColor(15 * b + x, 235, 235, 255); //set rain color
          yield();
        }
        pixels.show();
      }
    }
    yield();
  }
}

void cloudy() {
  Serial.println("CLOUDY");
  for (int loopcount = 0; loopcount < 5; loopcount++) {
    int i, a;
    for (i = 100; i < 255; i++) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillisArray[10] > interval2) {
        previousMillisArray[10] = currentMillis;
        for (a = 0; a < 300; a++) {
          pixels.setPixelColor(a, i, i, i); //set LEDs a gray color
          yield();
        }
        pixels.show();
      }
      yield();
    }
    for (i = 254; i > 99; i--) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillisArray[11] > interval2) {
        previousMillisArray[11] = currentMillis;
        for (a = 0; a < 300; a++) {
          pixels.setPixelColor(a, i, i, i); //set LEDs a gray color
          yield();
        }
        pixels.show();
      }
      yield();
    }
    yield();
  }
}
