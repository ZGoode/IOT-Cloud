void setImage(int cloudMode);
String parseHomePage();
String parseControlPage();
String parseConfigurePage();

String footer = "<!-- Footer -->"
                "<footer class='w3-bottom w3-center w3-black w3-padding-small w3-opacity w3-hover-opacity-off'>"
                "<div class='w3-xlarge'>"
                "<a href='https://github.com/ZGoode/IOT-Cloud'><i class='fa fa-github w3-hover-opacity'></i></a>"
                "<a href='https://twitter.com/FlamingBandaid'><i class='fa fa-twitter w3-hover-opacity'></i></a>"
                "<a href='http://linkedin.com/in/zachary-goode-724441160'><i class='fa fa-linkedin w3-hover-opacity'></i></a>"
                "</div>"
                "</footer>"
                ""
                "</body>"
                "</html>";

String header = "<!DOCTYPE html>"
                "<html>"
                "<title>IOT Cloud</title>"
                "<meta charset='UTF-8'>"
                "<meta name='viewport' content='width=device-width, initial-scale=1'>"
                "<link rel='stylesheet' href='https://www.w3schools.com/w3css/4/w3.css'>"
                "<link rel='stylesheet' href='https://fonts.googleapis.com/css?family=Lato'>"
                "<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css'>"
                "<style>"
                "body,h1,h2,h3,h4,h5,h6 {font-family: 'Lato', sans-serif;}"
                "body, html {"
                "height: 100%;"
                "color: #777;"
                "line-height: 1.8;"
                "}"
                "/* Create a Parallax Effect */"
                ".bgimg{"
                "background-attachment: fixed;"
                "background-position: center;"
                "background-repeat: no-repeat;"
                "background-size: cover;"
                "}"
                "/* Background Picture */"
                ".bgimg{"
                "background-image: url('%BACKGROUND_IMAGE%');"
                "min-height: 100%;"
                "}"
                ".w3-wide {letter-spacing: 10px;}"
                ".w3-hover-opacity {cursor: pointer;}"
                "</style>"
                "<body>"
                "<!-- Navbar (sit on top) -->"
                "<div class='w3-top'>"
                "<div class='w3-bar' id='myNavbar'>"
                "<a href='Home' class='w3-bar-item w3-button'>HOME</a>"
                "<a href='Control' class='w3-bar-item w3-button w3-hide-small'><i class='fa fa-user'></i> CONTROL</a>"
                "<a href='Configure' class='w3-bar-item w3-button w3-hide-small'><i class='fa fa-cogs'></i> CONFIGURE</a>"
                "<a href='https://github.com/ZGoode/IOT-Cloud' class='w3-bar-item w3-button w3-hide-small'><i class='fa fa-th'></i> ABOUT</a>"
                "<a href='/WifiReset' class='w3-bar-item w3-button w3-hide-small w3-right w3-hover-red'>WIFI RESET</a>"
                "<a href='/FactoryReset' class='w3-bar-item w3-button w3-hide-small w3-right w3-hover-red'>FACTORY RESET</a>"
                "</div>"
                "</div>";

String homePage = "<!-- First Parallax Image with Logo Text -->"
                  "<div class='bgimg w3-display-container w3-opacity-min' id='home'>"
                  "<div class='w3-display-middle' style='white-space:nowrap;'>"
                  "<p><span class='w3-center w3-padding-large w3-black w3-xlarge w3-wide w3-animate-opacity'>IOT<span class='w3-hide-small'> WEATHER</span> CLOUD</span></p>"
                  "<p><span class='w3-center w3-padding-large w3-black w3-xlarge w3-wide w3-animate-opacity'>CURRENT PATTERN:<span class='w3-hide-small'> %CURRENT_PATTERN%</span></span></p>"
                  "</div>"
                  "</div>";

String controlPage = "<!-- First Parallax Image with Logo Text -->"
                     "<div class='bgimg w3-display-container w3-opacity-min' id='home'>"
                     "<div class='w3-display-middle' style='white-space:nowrap;'>"
                     "<h2><center><b>Cloud Mode: %MODE%</b></center></h2>"
                     "<p><a href='/Automatic' class='w3-bar-item w3-button w3-hide-small'><i class='fa fa-user'></i> AUTOMATIC</a>"
                     "<a href='/ClearClouds' class='w3-bar-item w3-button w3-hide-small'><i class='fa fa-sun-o'></i> CLEAR CLOUDS</a>"
                     "<a href='/SpringDay' class='w3-bar-item w3-button w3-hide-small'><i class='fa fa-spinner'></i> SPRING DAY</a></p>"
                     "<p><a href='/SeizureMode' class='w3-bar-item w3-button w3-hide-small'><i class='fa fa-american-sign-language-interpreting'></i> SEIZURE MODE</a>"
                     "<a href='/LightningStorm' class='w3-bar-item w3-button w3-hide-small'><i class='fa fa-bolt'></i> LIGHTNING STORM</a>"
                     "<a href='/Rain' class='w3-bar-item w3-button w3-hide-small'><i class='fa fa-tint'></i> RAIN</a></p>"
                     "<p><a href='/Snow' class='w3-bar-item w3-button w3-hide-small'><i class='fa fa-snowflake-o'></i> SNOW</a>"
                     "<a href='/RainbowCycles' class='w3-bar-item w3-button w3-hide-small'><i class='fa fa-smile-o'></i> RAINBOW CYCLES</a>"
                     "<a href='/Cloudy' class='w3-bar-item w3-button w3-hide-small'><i class='fa fa-cloud'></i> CLOUDY</a></p>"
                     "<p><a href='/Sunset' class='w3-bar-item w3-button w3-hide-small'><i class='fa fa-sun-o'></i> SUNSET</a></p>"
                     "</div>"
                     "</div>";

String configurePage = "<div class='bgimg w3-display-container w3-opacity-min' id='home'>"
                       "<div class='w3-display-middle' style='white-space:nowrap;'>"
                       "<form class='w3-container' action='/updateConfig' method='get'><h2>Cloud Config:</h2>"
                       "<p><label>User ID (for this interface)</label><input class='w3-input w3-border w3-margin-bottom' type='text' name='userid' value='%USERID%' maxlength='20'></p>"
                       "<p><label>Password </label><input class='w3-input w3-border w3-margin-bottom' type='password' name='stationpassword' value='%STATIONPASSWORD%'></p>"
                       "<p><label>OTA Password </label><input class='w3-input w3-border w3-margin-bottom' type='password' name='otapassword' value='%OTAPASSWORD%'></p>"
                       "<p><label>OpenWeatherMap API Key (get from <a href='https://openweathermap.org/' target='_BLANK'>here</a>)</label><input class='w3-input w3-border w3-margin-bottom' type='text' name='openWeatherMapApiKey' value='%WEATHERKEY%' maxlength='60'></p>"
                       "<p><label>City Code (get from <a href='https://openweathermap.org/find?q=' target='_BLANK'>here</a>)</label><input class='w3-input w3-border w3-margin-bottom' type='text' name='city1' value='%CITY%' onkeypress='return isNumberKey(event)'></p>"
                       "<button class='w3-button w3-block w3-grey w3-section w3-padding' type='submit'>Save</button>"
                       "</form>"
                       "</div>"
                       "</div>";

void setImage(int cloudMode) {
  if (cloudMode == 0) {
    homePage.replace("%BACKGROUND_IMAGE%", "");
  } else if (cloudMode == 1) {
    homePage.replace("%BACKGROUND_IMAGE%", "");
  } else if (cloudMode == 2) {
    homePage.replace("%BACKGROUND_IMAGE%", "");
  } else if (cloudMode == 3) {
    homePage.replace("%BACKGROUND_IMAGE%", "");
  } else if (cloudMode == 4) {
    homePage.replace("%BACKGROUND_IMAGE%", "");
  } else if (cloudMode == 5) {
    homePage.replace("%BACKGROUND_IMAGE%", "");
  } else if (cloudMode == 6) {
    homePage.replace("%BACKGROUND_IMAGE%", "");
  } else if (cloudMode == 7) {
    homePage.replace("%BACKGROUND_IMAGE%", "");
  } else if (cloudMode == 8) {
    homePage.replace("%BACKGROUND_IMAGE%", "");
  }
}

String parseHomePage() {
  return header + homePage + footer;
}

String parseControlPage() {
  return header + controlPage + footer;
}

String parseConfigurePage() {
  return header + configurePage + footer;
}

