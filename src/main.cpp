#include <ESP8266React.h>
#include <LightMqttSettingsService.h>
#include <LightStateService.h>

#define SERIAL_BAUD_RATE 115200

bool ledState = false;

AsyncWebServer server(80);
ESP8266React esp8266React(&server);
LightMqttSettingsService lightMqttSettingsService =
    LightMqttSettingsService(&server, esp8266React.getFS(), esp8266React.getSecurityManager());
LightStateService lightStateService = LightStateService(&server,
                                                        esp8266React.getSecurityManager(),
                                                        esp8266React.getMqttClient(),
                                                        &lightMqttSettingsService,
                                                        esp8266React.getFS());

void setup() {
  // start serial and filesystem
  Serial.begin(SERIAL_BAUD_RATE);

  // start the framework and demo project
  esp8266React.begin();

  // load the initial light settings
  lightStateService.begin();

  // start the light service
  lightMqttSettingsService.begin();

  // start the server
  server.begin();
}

void loop() {
  // run the framework's loop function
  esp8266React.loop();
}

void handleBody(AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {
  if (!index) {
    Serial.printf("BodyStart: %u B\n", total);
  }
  for (size_t i = 0; i < len; i++) {
    Serial.write(data[i]);
  }
  if (index + len == total) {
    Serial.printf("BodyEnd: %u B\n", total);
  }
}
