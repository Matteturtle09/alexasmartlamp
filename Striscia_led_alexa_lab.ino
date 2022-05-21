/*   
  _                                     _                                   _                             _                
 | |                                   | |                                 | |                           | |               
 | |     __ _ _ __ ___  _ __   __ _  __| | __ _    ___ _ __ ___   __ _ _ __| |_    ___ ___  _ __     __ _| | _____  ____ _ 
 | |    / _` | '_ ` _ \| '_ \ / _` |/ _` |/ _` |  / __| '_ ` _ \ / _` | '__| __|  / __/ _ \| '_ \   / _` | |/ _ \ \/ / _` |
 | |___| (_| | | | | | | |_) | (_| | (_| | (_| |  \__ \ | | | | | (_| | |  | |_  | (_| (_) | | | | | (_| | |  __/>  < (_| |
 |______\__,_|_| |_| |_| .__/ \__,_|\__,_|\__,_|  |___/_| |_| |_|\__,_|_|   \__|  \___\___/|_| |_|  \__,_|_|\___/_/\_\__,_|
                       | |                                                                                                 
                       |_|    V1, 2022 by Matteo Mauri                                                                                           
 */


#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#define ESPALEXA_ASYNC
#include <Espalexa.h>


// *Lascia invariato*
boolean connectWifi();

// *Lascia incariato*
void colorLightChanged(uint8_t brightness, uint32_t rgb);


// Cambia con le tue credenziali
const char* ssid = "nome-wifi";
const char* password = "password-wifi";

boolean wifiConnected = false;

Espalexa espalexa;

void setup()
{
  Serial.begin(115200);
  // Initialise wifi connection
  wifiConnected = connectWifi();

  if (wifiConnected) {
    espalexa.addDevice("Nome-Lampada", colorLightChanged);
    espalexa.begin();

  } else
  {
    while (1) {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}

void loop()
{
  espalexa.loop();
  delay(1);
}

//the color device callback function has two parameters
void colorLightChanged(uint8_t brightness, uint32_t rgb) {
  //do what you need to do here, for example control RGB LED strip

  if (brightness) {
    Serial.print(", Red: ");
    Serial.print((rgb >> 16) & 0xFF); 
    analogWrite(0, (rgb >> 16) & 0xFF); // Led rosso
    Serial.print(", Green: ");
    Serial.print((rgb >>  8) & 0xFF); // Led verde
    analogWrite(4, (rgb >> 8) & 0xFF);
    Serial.print(", Blue: ");
    Serial.println(rgb & 0xFF); // Led blu
    analogWrite(5, (rgb & 0xFF));
  }
  else  {
    // spegnimento
    digitalWrite(0,0);
    digitalWrite(4,0);
    digitalWrite(5,0);
  }
}



// Funzione da non modificare
boolean connectWifi() {
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 40) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
