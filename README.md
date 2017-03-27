Stranger Things Wall
--------------------

This is ESP8266 Arduino code to write out messages from an MQTT feed on string of Neopixels, in the style of the Stranger Things series on Netflix.

You will need to create a config.h file with the following options:

```
#define IO_USERNAME    "your user name on Adafruit.IO"
#define IO_KEY         "your key from Adafruit.IO"

#define WIFI_SSID      "your wifi SSID"
#define WIFI_PASS      "your wifi Password"
```

To deploy a connector script on Digital Ocean to transfer Slack messages to your MQTT feed, see the `ansible` folder. You can also use message data from IFTTT as an alternative source.
