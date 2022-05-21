

## Occorrente

- Scheda esp8266 [(Nodemcu)](https://www.amazon.it/AZDelivery-NodeMCU-esp8266-esp-12e-gratuito/dp/B074Q2WM1Y/ref=mp_s_a_1_3?crid=213I44HMX08RE&keywords=nodemcu&qid=1653126222&sprefix=nodemc%2Caps%2C200&sr=8-3)
- [Led RGB](https://www.amazon.it/Youmile-emissione-Tri-Color-glassate-potrebbero/dp/B0897LDR9N/ref=mp_s_a_1_2_sspa?crid=1U8U674GT3L7O&keywords=led%2Brgb%2Barduino&qid=1653126291&sprefix=lled%2Brgb%2B%2Caps%2C218&sr=8-2-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExU04ySVdLNTJNVVFMJmVuY3J5cHRlZElkPUEwMDExMjkzMjJPQTBLMzJWWTRBVSZlbmNyeXB0ZWRBZElkPUEwNjk2MjUxMktKTVJRRlVQVks4OSZ3aWRnZXROYW1lPXNwX3Bob25lX3NlYXJjaF9hdGYmYWN0aW9uPWNsaWNrUmVkaXJlY3QmZG9Ob3RMb2dDbGljaz10cnVl&th=1)
- [Resistenze](https://www.amazon.it/AZDelivery-Resistenze-Resistori-Arduino-gratuito/dp/B07Q87JZ9G/ref=mp_s_a_1_8?crid=3B4FJC0DCCJTT&keywords=resistenze+arduino&qid=1653126158&sprefix=resistenze+ard%2Caps%2C229&sr=8-8) da 100 ohm
- [Jumper](https://www.amazon.it/dp/B08HQ7K6M7/ref=) (comunemente chiamati cavetti)
- [Breadboard](https://www.amazon.it/Elegoo-Mini-Breadboard-Punti-Arduino/dp/B06XRJPVZV/ref=mp_s_a_1_3?crid=2IB040IMB635J&keywords=mini+breadboard+elegoo&qid=1653126044&sprefix=mini+breadboard+elegoo%2Caps%2C258&sr=8-3#) (Opzionale)
- Copri lampada (opzionale)

## Hardware

L' hardware di questo progetto è molto semplice. Si tratta di collegare il led RGB alla scheda esp8266 (il cervello del nostro progetto).

Collegate con molta attenzione il led senza fare contatto tra i vari “gambetti”

Ricordatevi di mettere tra il cavo e il pin del led una resistenza di circa 100 Ω (ohm)

![20220521_160223.jpg](/20220521_160223.jpg)

## Software

Il software è leggermente più complesso, ma non spaventavi, in pochi passaggi capirete tutto.

**Includere le schede nell' IDE**

Installate l'arduino IDE se non lo avete già fatto.

Dalla schermata principale andate su File>impostazioni.

Inserite la stringa **http://arduino.esp8266.com/stable/package_esp8266com_index.json** nel campo "**URL aggiuntivo per il Gestore Schede**". Quindi, fate clic sul pulsante "**OK**".

Ora vedrete che all'interno del percorso **strumenti>scheda** potrete selezionare **Generic ESP8266 Module** che prima non compariva in elenco. Selezionatelo e sarete pronti a programmare le schede con **ESP8266**

### Includere ESPALEXA

Per installare espalexa vi basterà scaricare il codice in formato .zip da [https://github.com/Aircoookie/Espalexa](https://github.com/Aircoookie/Espalexa)

Ed inserirlo nella cartella arduino/libraries.

Decomprimete il file .zip e riavvate l'arduino ide.

Siete pronti per caricare il codice. 

### Il codice + personalizzazioni

Il codice da inserire nell’editor è il seguente:

```arduino
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
```

Per quanto riguarda le personalizzazioni dall’applicazione “Amazon Alexa” è possibile cambiare il nome del dispositivo o includerlo in un gruppo.

Inoltre se cercate dei copri lampada originali e avete una stampante 3D su siti come [https://www.thingiverse.com/](https://www.thingiverse.com/) trovate tanti modelli originali.

Io per esempio ho stampato questo: [https://www.thingiverse.com/thing:2955930](https://www.thingiverse.com/thing:2955930).

### Come aggiungere il dispositivo sull’App Alexa

1. Scaricare l’applicazione dall’ App store / Play store
2. Creare un account Amazon o accedere
3. Aprire la schermata dispositivi dal menù inferiore
4. Cliccare su aggiungi dispositivi
5. Scorrere in fondo alla lista e premere su “Altro”
6. Cliccare su ricerca dispositivi
7. Attendere 45 secondi circa
8. Seguire la configurazione guidata
