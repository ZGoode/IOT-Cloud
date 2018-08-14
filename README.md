# IOT-Cloud
# Created by: Zachary Goode

*-------------------------------------------------------------Summary--------------------------------------------------------------*

This project is a cloud that uses RGB LED's to display different light patterns on from a cloud hanging from the ceiling.  It uses data from OpenWeatherMaps to decide what pattern to display depending on the weather conditions.  The patterns can be set to cycle automatically depending on the weather or can be toggled manually through a web interface.

Current Patterns include:
*  Clear Clouds
*  Spring Day
*  Rainbow Sky
*  Lightning Storm
*  Rain
*  Snow
*  Rainbow Cycles
*  Cloudy
  
*--------------------------------------------------------------------------------------------------------------------------------------*

I wrote this code to replace some inefficient and un-user friendly code that the previous person at my school who created this project wrote.  This code is much more lightweight, uses less hardware, has a few extra features that the original didn't, has some extra security features and has a much better user interface allowing to change settings without reflashing the device.

Features:
*  Admin username and password so that the settings cannot be changed by anyone at random
*  Home Page that says what pattern is playing and background that updates based on the pattern playing
*  Control page that allows the user to manually choose what pattern is being played or set it to cycle automatically
*  Configuration page that allows the user to input the API key for OpenWeatherMaps, city ID for the city they want the weather of, and change the admin password and username for the station
*  About link that takes you to this github to show off my work
*  Link to reset just the wifi settings of the esp8266
*  Link to factory reset the esp8266 to the default settings of the sketch

*--------------------------------------------------------------------------------------------------------------------------------------*

Parts used in creating this:

(Most of the parts here I already had sitting around, but here is a complete list of parts with links in case anyone wants to replicate this project)

*  Wemos D1 Mini - https://www.aliexpress.com/item/ESP8266-ESP-12-ESP-12F-CH340G-CH340-V2-USB-WeMos-D1-Mini-WIFI-Development-Board-D1/32659152063.html?spm=a2g0s.9042311.0.0.27424c4dpCl0ue
*  Wemos D1 Mini Breadboard Shield - https://www.aliexpress.com/item/10PCS-LOT-Breadboard-Expansion-Shield-Pin-Lithium-battery-For-WeMos-D1-Mini-Module-Sensor/32810542983.html?spm=a2g0s.9042311.0.0.27424c4dpCl0ue
*  Wemos D1 Mini Battery Shield - https://www.aliexpress.com/item/D1-Mini-Battery-Shield-Lithium-Battery-Charging-Boost-With-LED-Light-Module-Mini-Micro-USB-Interface/32796781920.html?spm=a2g0s.9042311.0.0.27424c4dpCl0ue
*  GX12 3 Pin Connector - https://www.aliexpress.com/item/1set-GX12-2-3-4-5-6-7-Pin-Male-Female-12mm-L88-93-Circular-Aviation/32866277697.html?spm=a2g0s.13010208.99999999.265.6b863c004SYoxM
*  5.5x2.1mm Female DC Jack - https://www.aliexpress.com/item/10Pcs-PCB-Mount-5-5-x-2-1-mm-Female-DC-Power-Black-Jack-Plug-Socket/32809309617.html?spm=a2g0s.13010208.99999999.317.75383c00jF3tlK
*  WS2812 LED Strip (300 LED/5M) - 
*  SSD1306 128x64 .96" SPI Display - https://www.aliexpress.com/item/Yellow-blue-double-color-and-white-128X64-0-96-inch-OLED-LCD-LED-Display-Module-For/32584349265.html?spm=a2g0s.9042311.0.0.27424c4dpCl0ue
*  JMT SM 2 Pin Cables - https://www.aliexpress.com/item/Promotion-10Pairs-15cm-Long-JST-SM-2Pins-Plug-Male-to-Female-Wire-Connector/32818098582.html?spm=a2g0s.9042311.0.0.27424c4dpCl0ue
*  10K Ohm Resistor - https://www.aliexpress.com/store/product/600pcs-set-30-Kinds-1-4W-Resistance-1-Metal-Film-Resistor-Pack-Assorted-Kit-1K-10K/1326062_32840627690.html?spm=2114.12010615.8148356.4.3d8d7d90EdDfe6
*  220 Ohm Resistor - https://www.aliexpress.com/item/100Pcs-lot-220-Ohm-1-4w-Metal-Film-Resistor-Watt-0-25W-1-220OHM/32691394844.html?spm=a2g0s.9042311.0.0.17854c4dZ0OpGa
*  Pushbutton - https://www.aliexpress.com/item/50pcs-lot-6x6x4-3MM-4PIN-G89-Tactile-Tact-Push-Button-Micro-Switch-Direct-Plug-in-Self/32669948621.html?spm=2114.search0104.3.8.63747021lq8IAI&ws_ab_test=searchweb0_0,searchweb201602_4_10152_10151_10065_10344_10130_10068_10324_10342_10547_10325_10343_10546_10340_10548_10341_315_10545_5012515_10696_5012615_10084_531_10083_10618_10307_10059_100031_10103_10624_10623_10622_10621_10620,searchweb201603_51,ppcSwitch_5&algo_expid=40026fa5-12e0-4c78-9bed-659c658cfdcd-4&algo_pvid=40026fa5-12e0-4c78-9bed-659c658cfdcd&priceBeautifyAB=0
*  Toggle Switch - https://www.aliexpress.com/item/Promotion-5-Pcs-AC-ON-ON-SPDT-2-Position-Latching-Toggle-Switch-6A-125V/32813324272.html?spm=a2g0s.9042311.0.0.27424c4dpCl0ue
*  Wire - https://www.amazon.com/Voltage-LED-Conductor-Jacketed-Speaker/dp/B01KWBPC7M/ref=sr_1_7?s=home-garden&ie=UTF8&qid=1534210594&sr=1-7&keywords=speaker+wire
*  Relay Module - 
*  Polyester Stuffing - https://www.amazon.com/Mybecca-Polyester-Re-Stuffing-Fiberfill-LB/dp/B00W0GPDI6/ref=sr_1_8?ie=UTF8&qid=1534210405&sr=8-8&keywords=cotton+stuffing
*  Paper Lanterns of miscellaneous sizes - https://www.amazon.com/Pieces-4-6-8-10-12-Lanterns-Wedding-Hanging/dp/B07FMV86F5/ref=sr_1_2_sspa?ie=UTF8&qid=1534207762&sr=8-2-spons&keywords=paper+ball+lantern&psc=1
*  Hot Glue - https://www.amazon.com/Tacklife-Flexible-Trigger-Anti-hot-Repairs/dp/B075DDD9VN/ref=sr_1_1_sspa?s=arts-crafts&ie=UTF8&qid=1534214642&sr=1-1-spons&keywords=hot+glue+gun&psc=1
*  Zip Ties - https://www.amazon.com/TR-Industrial-TR88302-Multi-Purpose-Cable/dp/B01018DC96/ref=sr_1_4?s=electronics&ie=UTF8&qid=1534212890&sr=1-4&keywords=zip+ties
*  Fishing Line - https://www.amazon.com/dp/B01KLWADZS/ref=twister_B01KLW9ER6?_encoding=UTF8&th=1&psc=1

*--------------------------------------------------------------------------------------------------------------------------------------*
