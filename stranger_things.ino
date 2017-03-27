#include <Wire.h>
#include <map>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include <AdafruitIO_WiFi.h>
#include "config.h"

// Which pin on the ESP is connected to the NeoPixels?
#define NEOPIN         D7

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      30

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_RGB + NEO_KHZ800);
      
Adafruit_SSD1306 display(D8);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#if (SUBSCRIPTIONDATALEN < 200)
#error("MQTT buffer size too low, please fix in Adafruit_MQTT.h");
#endif

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
// set up the 'strangerthings' feed
AdafruitIO_Feed *feed = io.feed("strangerthings");

// global variables
std::map<char, int> pixelmap;
char message[201] = {'\0'};
bool updated = false;
int counter = 0;

void setup() {
  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // top row
  pixelmap['a'] = 29;
  pixelmap['b'] = 28;
  pixelmap['c'] = 27;
  pixelmap['d'] = 26;
  pixelmap['e'] = 25;
  pixelmap['f'] = 24;
  pixelmap['g'] = 23;
  pixelmap['h'] = 22;
  pixelmap['i'] = 21;
  pixelmap['j'] = 20;

  // second row
  pixelmap['t'] = 19;
  pixelmap['s'] = 18;
  pixelmap['r'] = 17;
  pixelmap['q'] = 16;
  pixelmap['p'] = 15;
  pixelmap['o'] = 14;
  pixelmap['n'] = 13;
  pixelmap['m'] = 12;
  pixelmap['l'] = 11;
  pixelmap['k'] = 10;

  // bottom row
  pixelmap['u'] = 9;
  pixelmap['v'] = 8;
  pixelmap['w'] = 7;
  pixelmap['x'] = 6;
  pixelmap['y'] = 5;
  pixelmap['z'] = 4;
  pixelmap[' '] = 3;
  pixelmap['?'] = 2;
  pixelmap[','] = 1;
  pixelmap['.'] = 0;

  pixels.begin(); // This initializes the NeoPixel library.
  pixels.clear();
  pixels.show();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x78 (for the 128x64)
  
  Serial.print("Connecting to Adafruit IO");
  oled_print("Connecting...");
  
  // connect to io.adafruit.com
  io.connect();
  feed->onMessage(handleMessage);

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());
  oled_print("Connected");
}

void loop() {
  io.run();
  updateNeopixels();
}

// handle new messages sent to feed
void handleMessage(AdafruitIO_Data *data) {
  Serial.print("received <- ");
  Serial.println(data->value());
  strncpy(message, data->value(), 200);
  oled_print(message);
  counter = 0;
  updated = true;
}

void updateNeopixels() {
  if (updated) {
    if (!counter) {
      delay(1000);
    }

    if (counter > strlen(message) - 1) {
      updated = false;
      counter = 0;
      delay(1000);
    
    } else {
      
      char c = tolower(message[counter]);
      int pixel = 0;

      Serial.printf("Next character is: %c\n", c);
      
      if (pixelmap.find(c) != pixelmap.end()) {
        pixel = pixelmap[c];
        Serial.printf("Lighting pixel: %d\n", pixel);
        pixels.clear();
        pixels.setPixelColor(pixel, pixels.Color(255,255,255));
        pixels.show();
        delay(500);
      } else {
        Serial.println("Non-printable character found, skipping");
      }

      pixels.clear();
      pixels.show();
      delay(200);
      
      counter++;
    }
  }
}

void oled_print(const char *msg) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(msg);
  display.display();
}
