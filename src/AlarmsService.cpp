#include <AlarmsService.h>
#include <ESP8266React.h>

// void AlarmsService::begin() {
//   // read the initial state of the alarms
//   readAlarmsState();
// }

// void AlarmsService::loop() {
//   // nothing to do here
// }

void AlarmsService::writeAlarmsState(DynamicJsonDocument& doc) {
  File file = _fs->open("/alarms.json", "w");

  if (!file) {
    Serial.println("Failed to open alarms.json for writing");
    return;
  }

  serializeJson(doc, file);
  file.close();
}

void AlarmsService::alarmsPostBodyHandler(AsyncWebServerRequest* request,
                                          uint8_t* data,
                                          size_t len,
                                          size_t index,
                                          size_t total) {
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

    writeAlarmsState(doc);

    // write the alarms state to the filesystem
    // writeAlarmsState(doc, AlarmsService::_fs);

    // save the body to the filesystem
    // File file = SPIFFS.open("/alarms.json", "w");

    // if (!file) {
    //   Serial.println("Failed to open alarms.json for writing");
    //   request->send(500);
    //   return;
    // }

    // serializeJson(doc, file);
    // file.close();

    // send response
    request->send(200);
  }
}

AlarmsService::AlarmsService(AsyncWebServer* server, FS* fs) {
  _fs = fs;
  _server = server;

  // register the handler for the alarms state endpoint
  server->on(
      "/rest/alarmsState",
      HTTP_POST,
      [this](AsyncWebServerRequest* request) {},
      NULL,
      [this](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {
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
}