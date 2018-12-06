#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include "FS.h"
#include "SH1106Wire.h"
#include "SSD1306Wire.h"
#include "OLEDDisplayUi.h"

#include "Patterns.h"
#include "HTML.h"
#include "OpenWeatherMapClient.h"

#define VERSION "1.0"
#define HOSTNAME "IOT-WEATHER-CLOUD"
#define CONFIG "/conf.txt"

String WeatherApiKey = "";
int CityID;
boolean IS_METRIC = true;

const int WEBSERVER_PORT = 80;
char* www_username = "admin";
char* www_password = "password";

String OTA_Password = "password";

const int buttonPin = D3;
int externalLight = LED_BUILTIN;
int weatherID;
int currentMode = 0;
int currentPattern = -1;
long previousMillis = 0;
long previousMillisWeather = 0;
long previousMillisDisplay = 0;
long interval = 1800000;
long intervalWeather = 600000;
long intervalDisplay = 10000;
int currentWeatherID = 0;
boolean displayOn = true;
boolean firstDisplay = true;

int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

// Display Settings
const int I2C_DISPLAY_ADDRESS = 0x3c; // I2C Address of your Display (usually 0x3c or 0x3d)
const int SDA_PIN = D2;
const int SCL_PIN = D5;
const boolean INVERT_DISPLAY = true; // true = pins at top | false = pins at the bottom
//#define DISPLAY_SH1106       // Uncomment this line to use the SH1106 display -- SSD1306 is used by default and is most common

// Initialize the oled display for I2C_DISPLAY_ADDRESS
// SDA_PIN and SCL_PIN
#if defined(DISPLAY_SH1106)
SH1106Wire display(I2C_DISPLAY_ADDRESS, SDA_PIN, SCL_PIN);
#else
SSD1306Wire display(I2C_DISPLAY_ADDRESS, SDA_PIN, SCL_PIN); // this is the default
#endif

OLEDDisplayUi   ui( &display );

// Set the number of Frames supported
const int numberOfFrames = 3;
FrameCallback frames[numberOfFrames];
FrameCallback clockFrame[2];

OpenWeatherMapClient weatherClient(WeatherApiKey, CityID, 1, IS_METRIC);

ESP8266WebServer server(WEBSERVER_PORT);

void handleSystemReset();
void parseWeatherConditionID(int i);
int8_t getWifiQuality();
void readSettings();
void writeSettings();
void handleUpdateConfig();
void handleNotFound();
void handleRoot();
void handleConfigure();
void handleConfigureNoPassword();
void handleControl();
void handleAutomatic();
void handleClearClouds();
void handleSpringDay();
void handleseizureMode();
void handleLightningStorm();
void handleRain();
void handleSnow();
void handleRainbowCycles();
void handleCloudy();
void handleSunset();
String parseCurrentMode();
String parseCurrentPattern();
int getID();

void setup() {
  Serial.begin(115200);
  SPIFFS.begin();
  delay(10);

  Serial.println();
  pinMode(externalLight, OUTPUT);
  pinMode(buttonPin, INPUT);

  readSettings();

  //initialize display
  display.init();
  if (INVERT_DISPLAY) {
    display.flipScreenVertically(); // connections at top of OLED display
  }

  display.clear();
  display.display();

  parseHomePage();
  parseConfigurePage();
  parseControlPage();
  initializePixels();

  WiFiManager wifiManager;

  String hostname(HOSTNAME);
  if (!wifiManager.autoConnect((const char *)hostname.c_str())) {// new addition
    delay(3000);
    WiFi.disconnect(true);
    ESP.reset();
    delay(5000);
  }

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.setHostname((const char *)hostname.c_str());
  if (OTA_Password != "") {
    ArduinoOTA.setPassword(((const char *)OTA_Password.c_str()));
  }
  ArduinoOTA.begin();

  Serial.println("WEBSERVER_ENABLED");
  server.on("/Home", HTTP_GET, handleRoot);
  server.on("/Configure", handleConfigure);
  server.on("/updateConfig", handleUpdateConfigure);
  server.on("/Control", handleControl);
  server.on("/FactoryReset", handleSystemReset);
  server.on("/WifiReset", handleWifiReset);
  server.on("/Automatic", handleAutomatic);
  server.on("/ClearClouds", handleClearClouds);
  server.on("/SpringDay", handleSpringDay);
  server.on("/SeizureMode", handleSeizureMode);
  server.on("/LightningStorm", handleLightningStorm);
  server.on("/Rain", handleRain);
  server.on("/Snow", handleSnow);
  server.on("/RainbowCycles", handleRainbowCycles);
  server.on("/Cloudy", handleCloudy);
  server.on("/Sunset", handleSunset);
  server.onNotFound(handleRoot);
  server.begin();
  Serial.println("Server Started");
  String webAddress = "http://" + WiFi.localIP().toString() + ":" + String(WEBSERVER_PORT) + "/";
  Serial.println("Use this URL : " + webAddress);

  weatherClient.updateWeather();
  currentWeatherID = weatherClient.getWeatherId().toInt();
  parseWeatherConditionID(currentWeatherID);
  Serial.println(currentWeatherID);
}

void loop() {
  server.handleClient();
  ArduinoOTA.handle();

  delay(1);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    weatherClient.updateWeather();
    currentWeatherID = weatherClient.getWeatherId().toInt();
    parseWeatherConditionID(currentWeatherID);
    Serial.println(currentWeatherID);
  }

  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    buttonState = reading;
  }

  lastButtonState = reading;

  if (buttonState == HIGH) {
    displayOn = true;
  }

  if (displayOn) {
    displayOn = false;
    previousMillisDisplay = currentMillis;
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 10, "Web Interface On");
    display.drawString(64, 20, "You May Connect to IP");
    display.setFont(ArialMT_Plain_16);
    display.drawString(64, 30, WiFi.localIP().toString());
    display.drawString(64, 46, "Port: " + String(WEBSERVER_PORT));
    display.display();
  }

  if (currentMillis - previousMillisDisplay > intervalDisplay) {
    display.clear();
  }

  if (currentMode == 0) {
    if (currentPattern == 0) {
      clearClouds();
    } else if (currentPattern == 1) {
      springDay();
    } else if (currentPattern == 2) {
      seizureMode();
    } else if (currentPattern == 3) {
      lightningStorm();
    } else if (currentPattern == 4) {
      rain();
    } else if (currentPattern == 5) {
      snow();
    } else if (currentPattern == 6) {
      rainbowCycle();
    } else if (currentPattern == 7) {
      cloudy();
    } else if (currentPattern == 8) {
      sunset();
    }
  } else if (currentMode == 1) {
    clearClouds();
    currentPattern = 0;
  } else if (currentMode == 2) {
    springDay();
    currentPattern = 1;
  } else if (currentMode == 3) {
    seizureMode();
    currentPattern = 2;
  } else if (currentMode == 4) {
    lightningStorm();
    currentPattern = 3;
  } else if (currentMode == 5) {
    rain();
    currentPattern = 4;
  } else if (currentMode == 6) {
    snow();
    currentPattern = 5;
  } else if (currentMode == 7) {
    rainbowCycle();
    currentPattern = 6;
  } else if (currentMode == 8) {
    cloudy();
    currentPattern = 7;
  } else if (currentMode == 9) {
    sunset();
    currentPattern = 8;
  }
}

void handleSystemReset() {
  if (!server.authenticate(www_username, www_password)) {
    return server.requestAuthentication();
  }
  Serial.println("Reset System Configuration");
  if (SPIFFS.remove(CONFIG)) {
    handleRoot();;
    ESP.restart();
  }
}

void handleWifiReset() {
  if (!server.authenticate(www_username, www_password)) {
    return server.requestAuthentication();
  }
  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  handleRoot();
  WiFiManager wifiManager;
  wifiManager.resetSettings();
  ESP.restart();
}

// converts the dBm to a range between 0 and 100%
int8_t getWifiQuality() {
  int32_t dbm = WiFi.RSSI();
  if (dbm <= -100) {
    return 0;
  } else if (dbm >= -50) {
    return 100;
  } else {
    return 2 * (dbm + 100);
  }
}

void writeSettings() {
  // Save decoded message to SPIFFS file for playback on power up.
  File f = SPIFFS.open(CONFIG, "w");
  if (!f) {
    Serial.println("File open failed!");
  } else {
    Serial.println("Saving settings now...");
    f.println("www_username=" + String(www_username));
    f.println("www_password=" + String(www_password));
    f.println("weatherKey=" + WeatherApiKey);
    f.println("CityID=" + String(CityID));
    f.println("isMetric=" + String(IS_METRIC));
  }
  f.close();
  readSettings();
}

void handleUpdateConfigure() {
  if (!server.authenticate(www_username, www_password)) {
    return server.requestAuthentication();
  }

  String temp = server.arg("userid");
  temp.toCharArray(www_username, sizeof(temp));
  temp = server.arg("stationpassword");
  temp.toCharArray(www_password, sizeof(temp));
  OTA_Password = server.arg("otapassword");
  WeatherApiKey = server.arg("openWeatherMapApiKey");
  CityID = server.arg("city1").toInt();
  IS_METRIC = server.hasArg("metric");

  writeSettings();
  handleConfigureNoPassword();
}

void readSettings() {
  if (SPIFFS.exists(CONFIG) == false) {
    Serial.println("Settings File does not yet exists.");
    writeSettings();
    return;
  }
  File fr = SPIFFS.open(CONFIG, "r");
  String line;
  while (fr.available()) {
    line = fr.readStringUntil('\n');

    if (line.indexOf("www_username=") >= 0) {
      String temp = line.substring(line.lastIndexOf("www_username=") + 13);
      temp.trim();
      temp.toCharArray(www_username, sizeof(temp));
      Serial.println("www_username=" + String(www_username));
    }
    if (line.indexOf("www_password=") >= 0) {
      String temp = line.substring(line.lastIndexOf("www_password=") + 13);
      temp.trim();
      temp.toCharArray(www_password, sizeof(temp));
      Serial.println("www_password=" + String(www_password));
    }
    if (line.indexOf("weatherKey=") >= 0) {
      WeatherApiKey = line.substring(line.lastIndexOf("weatherKey=") + 11);
      WeatherApiKey.trim();
      Serial.println("WeatherApiKey=" + WeatherApiKey);
    }
    if (line.indexOf("CityID=") >= 0) {
      CityID = line.substring(line.lastIndexOf("CityID=") + 7).toInt();
      Serial.println("CityID: " + String(CityID));
    }
    if (line.indexOf("isMetric=") >= 0) {
      IS_METRIC = line.substring(line.lastIndexOf("isMetric=") + 9).toInt();
      Serial.println("IS_METRIC=" + String(IS_METRIC));
    }
  }
  fr.close();
  weatherClient.updateWeatherApiKey(WeatherApiKey);
  weatherClient.updateCityId(CityID);
  weatherClient.setMetric(IS_METRIC);
  weatherClient.updateCityId(CityID);
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URL in the request
}

void handleRoot() {
  String form = parseHomePage();
  setImage(currentPattern);
  form.replace("%CURRENT_PATTERN%", parseCurrentPattern());
  server.send(200, "text/html", form);  // Home webpage for the cloud
}

void handleConfigure() {
  if (!server.authenticate(www_username, www_password)) {
    return server.requestAuthentication();
  }
  String form = parseConfigurePage();
  form.replace("%USERID%", www_username);
  form.replace("%STATIONPASSWORD%", www_password);
  form.replace("%OTAPASSWORD%", OTA_Password);
  form.replace("%WEATHERKEY%", WeatherApiKey);
  form.replace("%CITY%", String(CityID));

  Serial.println(String(CityID));
  server.send(200, "text/html", form);  // Configure portal for the cloud
}

void handleConfigureNoPassword() {
  String form = parseConfigurePage();
  form.replace("%USERID%", www_username);
  form.replace("%STATIONPASSWORD%", www_password);
  form.replace("%OTAPASSWORD%", OTA_Password);
  form.replace("%WEATHERKEY%", WeatherApiKey);
  form.replace("%CITY%", String(CityID));

  server.send(200, "text/html", form);  // Configure portal for the cloud
}

void handleControl() {
  if (!server.authenticate(www_username, www_password)) {
    return server.requestAuthentication();
  }
  String form = parseControlPage();
  form.replace("%MODE%", parseCurrentMode());
  Serial.println(currentWeatherID);

  server.send(200, "text/html", form);  // Control page for the cloud
}

void handleAutomatic() {
  currentMode = 0;
  handleControl();
}

void handleClearClouds() {
  currentMode = 1;
  handleControl();
}

void handleSpringDay() {
  currentMode = 2;
  handleControl();
}

void handleSeizureMode() {
  currentMode = 3;
  handleControl();
}

void handleLightningStorm() {
  currentMode = 4;
  handleControl();
}

void handleRain() {
  currentMode = 5;
  handleControl();
}

void handleSnow() {
  currentMode = 6;
  handleControl();
}

void handleRainbowCycles() {
  currentMode = 7;
  handleControl();
}

void handleCloudy() {
  currentMode = 8;
  handleControl();
}

void handleSunset() {
  currentMode = 9;
  handleControl();
}

String parseCurrentMode() {
  if (currentMode == 0) {
    return "Automatic";
  } else if (currentMode == 1) {
    return "Clear Clouds";
  } else if (currentMode == 2) {
    return "Spring Day";
  } else if (currentMode == 3) {
    return "Seizure Mode";
  } else if (currentMode == 4) {
    return "Lightning Storm";
  } else if (currentMode == 5) {
    return "Rain";
  } else if (currentMode == 6) {
    return "Snow";
  } else if (currentMode == 7) {
    return "Rainbow Cycles";
  } else if (currentMode == 8) {
    return "Cloudy";
  } else if (currentMode == 9) {
    return "Sunset";
  } else {
    return "";
  }
}

String parseCurrentPattern() {
  String temp = "";
  if (currentPattern == -1) {
    temp = "NOT ACTIVE";
  } else if (currentPattern == 0) {
    temp = "Clear Clouds";
  } else if (currentPattern == 1) {
    temp = "Spring Day";
  } else if (currentPattern == 2) {
    temp = "Seizure Mode";
  } else if (currentPattern == 3) {
    temp = "Lightning Storm";
  } else if (currentPattern == 4) {
    temp = "Rain";
  } else if (currentPattern == 5) {
    temp = "Snow";
  } else if (currentPattern == 6) {
    temp = "Rainbow Cycles";
  } else if (currentPattern == 7) {
    temp = "Cloudy";
  } else if (currentPattern == 8) {
    temp = "Sunset";
  } else {
    temp = "";
  }
  temp.toUpperCase();
  return temp;
}

void parseWeatherConditionID(int i) {
  int randomseed = random(2);
  byte msg[1];
  if (i == 800) {
    Serial.printf("Clear Skies: %d\n", i);
    if (randomseed == 0) {
      currentPattern = 0;
    } else {
      currentPattern = 1;
    }
    return;
  }
  else if (i == 962) {
    Serial.printf("Hurricane: %d\n", i);
    if (randomseed == 1) {
      currentPattern = 3;
    } else {
      currentPattern = 4;
    }
  }
  i = i / 100;
  if (i == 2) {
    Serial.printf("Thunderstorm: %d\n", i);
    if (randomseed == 1) {
      currentPattern = 3;
    } else {
      currentPattern = 4;
    }
  }
  else if (i == 3) {
    Serial.printf("Drizzle: %d\n", i);
    currentPattern = 4;
  }
  else if (i == 5) {
    Serial.printf("Rain: %d\n", i);
    currentPattern = 4;
  }
  else if (i == 6) {
    Serial.printf("Snow: %d\n", i);
    currentPattern = 5;
  }
  else if (i == 7) {
    Serial.printf("Crap: %d\n", i);
    currentPattern = 6;
  }
  else if (i == 8) {
    Serial.printf("Clouds: %d\n", i);
    currentPattern = 7;
  }
}
