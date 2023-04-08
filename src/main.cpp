#include <ESP8266React.h>

#define SERIAL_BAUD_RATE 115200

bool ledState = false;

AsyncWebServer server(80);
ESP8266React esp8266React(&server);

void setup() {
  // get filesystem ready
  FS* fs = esp8266React.getFS();

  // start serial and filesystem
  Serial.begin(SERIAL_BAUD_RATE);

  // start the framework and demo project
  esp8266React.begin();

  // body parser for POST requests

  server.on(
      "/rest/alarmsState",
      HTTP_POST,
      [](AsyncWebServerRequest* request) {},
      NULL,
      [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {
        // Concatenate the body
        if (request->_tempObject == NULL) {
          request->_tempObject = new String();
        }

        for (size_t i = 0; i < len; i++) {
          ((String*)request->_tempObject)->concat((char)data[i]);
        }

        // check if the body is complete
        if (index + len == total) {
          Serial.println("Body received.");

          // get the body
          String* body = (String*)request->_tempObject;

          // print the body
          Serial.println(*body);

          // parse the body
          DynamicJsonDocument doc(2048);
          DeserializationError error = deserializeJson(doc, *body);

          if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.c_str());
            request->send(400);
            return;
          }

          JsonArray alarms = doc["alarms"];

          for (JsonObject alarm : alarms) {
            Serial.print("Alarm title: ");
            Serial.println(alarm["title"].as<String>());
            Serial.print("Alarm enabled: ");
            Serial.println(alarm["enabled"].as<bool>());
          }
        }

        request->send(200);
      });

  // start the server
  server.begin();
}

void loop() {
  // run the framework's loop function
  esp8266React.loop();
}
