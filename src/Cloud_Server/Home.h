String homePage;

void parseHomePage () {
  homePage = "<!DOCTYPE html>";
  homePage += "<html>";
  homePage += "<title>IOT Cloud</title>";
  homePage += "<meta charset='UTF-8'>";
  homePage += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  homePage += "<link rel='stylesheet' href='https://www.w3schools.com/w3css/4/w3.css'>";
  homePage += "<link rel='stylesheet' href='https://fonts.googleapis.com/css?family=Lato'>";
  homePage += "<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css'>";
  homePage += "<style>";
  homePage += "body,h1,h2,h3,h4,h5,h6 {font-family: 'Lato', sans-serif;}";
  homePage += "body, html {";
  homePage += "height: 100%;";
  homePage += "color: #777;";
  homePage += "line-height: 1.8;";
  homePage += "}";
  homePage += "";
  homePage += "/* Create a Parallax Effect */";
  homePage += ".bgimg{";
  homePage += "background-attachment: fixed;";
  homePage += "background-position: center;";
  homePage += "background-repeat: no-repeat;";
  homePage += "background-size: cover;";
  homePage += "}";
  homePage += "";
  homePage += "/* Background Picture */";
  homePage += ".bgimg{";
  homePage += "background-image: url('%BACKGROUND_IMAGE%');";
  homePage += "min-height: 100%;";
  homePage += "}";
  homePage += "";
  homePage += "";
  homePage += ".w3-wide {letter-spacing: 10px;}";
  homePage += ".w3-hover-opacity {cursor: pointer;}";
  homePage += "";
  homePage += "</style>";
  homePage += "<body>";
  homePage += "";
  homePage += "<!-- Navbar (sit on top) -->";
  homePage += "<div class='w3-top'>";
  homePage += "<div class='w3-bar' id='myNavbar'>";
  homePage += "<a href='Home' class='w3-bar-item w3-button'>HOME</a>";
  homePage += "<a href='Control' class='w3-bar-item w3-button w3-hide-small'><i class='fa fa-user'></i> CONTROL</a>";
  homePage += "<a href='Configure' class='w3-bar-item w3-button w3-hide-small'><i class='fa fa-th'></i> CONFIGURE</a>";
  homePage += "<a href='https://github.com/ZGoode/IOT-Cloud' class='w3-bar-item w3-button w3-hide-small'><i class='fa fa-th'></i> ABOUT</a>";
  homePage += "<a href='/WifiReset' class='w3-bar-item w3-button w3-hide-small w3-right w3-hover-red'>WIFI RESET</a>";
  homePage += "<a href='/FactoryReset' class='w3-bar-item w3-button w3-hide-small w3-right w3-hover-red'>FACTORY RESET</a>";
  homePage += "</div>";
  homePage += "</div>";
  homePage += "";
  homePage += "<!-- First Parallax Image with Logo Text -->";
  homePage += "<div class='bgimg w3-display-container w3-opacity-min' id='home'>";
  homePage += "<div class='w3-display-middle' style='white-space:nowrap;'>";
  homePage += "<p><span class='w3-center w3-padding-large w3-black w3-xlarge w3-wide w3-animate-opacity'>IOT<span class='w3-hide-small'> WEATHER</span> CLOUD</span></p>";
  homePage += "<p><span class='w3-center w3-padding-large w3-black w3-xlarge w3-wide w3-animate-opacity'>CURRENT PATTERN:<span class='w3-hide-small'> %CURRENT_PATTERN%</span></span></p>";
  homePage += "</div>";
  homePage += "</div>";
  homePage += "";
  homePage += "<!-- Footer -->";
  homePage += "<footer class='w3-center w3-black w3-padding-64 w3-opacity w3-hover-opacity-off'>";
  homePage += "  <div class='w3-xlarge w3-section'>";
  homePage += "    <a href='https://github.com/ZGoode/IOT-Cloud'><i class='fa fa-github w3-hover-opacity'></i></a>";
  homePage += "    <a href='https://twitter.com/FlamingBandaid'><i class='fa fa-twitter w3-hover-opacity'></i></a>";
  homePage += "    <a href='http://linkedin.com/in/zachary-goode-724441160'><i class='fa fa-linkedin w3-hover-opacity'></i></a>";
  homePage += "  </div>";
  homePage += "</footer>";
  homePage += "";
  homePage += "</body>";
  homePage += "</html>";
}

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
  }
}

