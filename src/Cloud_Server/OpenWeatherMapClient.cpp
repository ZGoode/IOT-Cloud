/** The MIT License (MIT)

  Copyright (c) 2018 David Payne

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "OpenWeatherMapClient.h"

OpenWeatherMapClient::OpenWeatherMapClient(String ApiKey, int CityID, int cityCount, boolean isMetric) {
  updateCityId(CityID);
  myApiKey = ApiKey;
  setMetric(isMetric);
}

void OpenWeatherMapClient::updateWeatherApiKey(String ApiKey) {
  myApiKey = ApiKey;
}

void OpenWeatherMapClient::updateWeather() {
  WiFiClient weatherClient;
  String apiGetData = "GET /data/2.5/group?id=" + myCityIDs + "&units=" + units + "&cnt=1&APPID=" + myApiKey + " HTTP/1.1";

  Serial.println("Getting Weather Data");
  Serial.println(apiGetData);
  result = "";
  if (weatherClient.connect(servername, 80)) {  //starts client connection, checks for connection
    weatherClient.println(apiGetData);
    weatherClient.println("Host: " + String(servername));
    weatherClient.println("User-Agent: ArduinoWiFi/1.1");
    weatherClient.println("Connection: close");
    weatherClient.println();
  }
  else {
    Serial.println("connection for weather data failed"); //error message if no client connect
    Serial.println();
    return;
  }

  while (weatherClient.connected() && !weatherClient.available()) delay(1); //waits for data

  Serial.println("Waiting for data");

  // Check HTTP status
  char status[32] = {0};
  weatherClient.readBytesUntil('\r', status, sizeof(status));
  Serial.println("Response Header: " + String(status));
  if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
    Serial.print(F("Unexpected response: "));
    Serial.println(status);
    return;
  }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!weatherClient.find(endOfHeaders)) {
    Serial.println(F("Invalid response"));
    return;
  }

  const size_t bufferSize = 710;
  DynamicJsonBuffer jsonBuffer(bufferSize);

  weathers.cached = false;
  weathers.error = "";
  // Parse JSON object
  JsonObject& root = jsonBuffer.parseObject(weatherClient);
  if (!root.success()) {
    Serial.println(F("Weather Data Parsing failed!"));
    weathers.error = "Weather Data Parsing failed!";
    return;
  }

  weatherClient.stop(); //stop client

  if (root.measureLength() <= 150) {
    Serial.println("Error Does not look like we got the data.  Size: " + String(root.measureLength()));
    weathers.cached = true;
    weathers.error = (const char*)root["message"];
    Serial.println("Error: " + weathers.error);
    return;
  }
  int count = root["cnt"];

  for (int inx = 0; inx < count; inx++) {
    weathers.lat = (const char*)root["list"][inx]["coord"]["lat"];
    weathers.lon = (const char*)root["list"][inx]["coord"]["lon"];
    weathers.dt = (const char*)root["list"][inx]["dt"];
    weathers.city = (const char*)root["list"][inx]["name"];
    weathers.country = (const char*)root["list"][inx]["sys"]["country"];
    weathers.temp = (const char*)root["list"][inx]["main"]["temp"];
    weathers.humidity = (const char*)root["list"][inx]["main"]["humidity"];
    weathers.condition = (const char*)root["list"][inx]["weather"][0]["main"];
    weathers.wind = (const char*)root["list"][inx]["wind"]["speed"];
    weathers.weatherId = (const char*)root["list"][inx]["weather"][0]["id"];
    weathers.description = (const char*)root["list"][inx]["weather"][0]["description"];
    weathers.icon = (const char*)root["list"][inx]["weather"][0]["icon"];

    Serial.println("lat: " + weathers.lat);
    Serial.println("lon: " + weathers.lon);
    Serial.println("dt: " + weathers.dt);
    Serial.println("city: " + weathers.city);
    Serial.println("country: " + weathers.country);
    Serial.println("temp: " + weathers.temp);
    Serial.println("humidity: " + weathers.humidity);
    Serial.println("condition: " + weathers.condition);
    Serial.println("wind: " + weathers.wind);
    Serial.println("weatherId: " + weathers.weatherId);
    Serial.println("description: " + weathers.description);
    Serial.println("icon: " + weathers.icon);
    Serial.println();

  }
}

String OpenWeatherMapClient::roundValue(String value) {
  float f = value.toFloat();
  int rounded = (int)(f + 0.5f);
  return String(rounded);
}

void OpenWeatherMapClient::updateCityId(int CityID) {
  myCityIDs = "";
  myCityIDs = CityID;
}

void OpenWeatherMapClient::setMetric(boolean isMetric) {
  if (isMetric) {
    units = "metric";
  } else {
    units = "imperial";
  }
}

String OpenWeatherMapClient::getWeatherResults() {
  return result;
}

String OpenWeatherMapClient::getLat() {
  return weathers.lat;
}

String OpenWeatherMapClient::getLon() {
  return weathers.lon;
}

String OpenWeatherMapClient::getDt() {
  return weathers.dt;
}

String OpenWeatherMapClient::getCity() {
  return weathers.city;
}

String OpenWeatherMapClient::getCountry() {
  return weathers.country;
}

String OpenWeatherMapClient::getTemp() {
  return weathers.temp;
}

String OpenWeatherMapClient::getTempRounded() {
  return roundValue(getTemp());
}

String OpenWeatherMapClient::getHumidity() {
  return weathers.humidity;
}

String OpenWeatherMapClient::getHumidityRounded() {
  return roundValue(getHumidity());
}

String OpenWeatherMapClient::getCondition() {
  return weathers.condition;
}

String OpenWeatherMapClient::getWind() {
  return weathers.wind;
}

String OpenWeatherMapClient::getWindRounded() {
  return roundValue(getWind());
}

String OpenWeatherMapClient::getWeatherId() {
  return weathers.weatherId;
}

String OpenWeatherMapClient::getDescription() {
  return weathers.description;
}

String OpenWeatherMapClient::getIcon() {
  return weathers.icon;
}

boolean OpenWeatherMapClient::getCached() {
  return weathers.cached;
}

String OpenWeatherMapClient::getMyCityIDs() {
  return myCityIDs;
}

String OpenWeatherMapClient::getError() {
  return weathers.error;
}

String OpenWeatherMapClient::getWeatherIcon()
{
  int id = getWeatherId().toInt();
  String W = ")";
  switch (id)
  {
    case 800: W = "B"; break;
    case 801: W = "Y"; break;
    case 802: W = "H"; break;
    case 803: W = "H"; break;
    case 804: W = "Y"; break;

    case 200: W = "0"; break;
    case 201: W = "0"; break;
    case 202: W = "0"; break;
    case 210: W = "0"; break;
    case 211: W = "0"; break;
    case 212: W = "0"; break;
    case 221: W = "0"; break;
    case 230: W = "0"; break;
    case 231: W = "0"; break;
    case 232: W = "0"; break;

    case 300: W = "R"; break;
    case 301: W = "R"; break;
    case 302: W = "R"; break;
    case 310: W = "R"; break;
    case 311: W = "R"; break;
    case 312: W = "R"; break;
    case 313: W = "R"; break;
    case 314: W = "R"; break;
    case 321: W = "R"; break;

    case 500: W = "R"; break;
    case 501: W = "R"; break;
    case 502: W = "R"; break;
    case 503: W = "R"; break;
    case 504: W = "R"; break;
    case 511: W = "R"; break;
    case 520: W = "R"; break;
    case 521: W = "R"; break;
    case 522: W = "R"; break;
    case 531: W = "R"; break;

    case 600: W = "W"; break;
    case 601: W = "W"; break;
    case 602: W = "W"; break;
    case 611: W = "W"; break;
    case 612: W = "W"; break;
    case 615: W = "W"; break;
    case 616: W = "W"; break;
    case 620: W = "W"; break;
    case 621: W = "W"; break;
    case 622: W = "W"; break;

    case 701: W = "M"; break;
    case 711: W = "M"; break;
    case 721: W = "M"; break;
    case 731: W = "M"; break;
    case 741: W = "M"; break;
    case 751: W = "M"; break;
    case 761: W = "M"; break;
    case 762: W = "M"; break;
    case 771: W = "M"; break;
    case 781: W = "M"; break;

    default: break;
  }
  return W;
}
