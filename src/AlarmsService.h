#ifndef AlarmsService_h
#define AlarmsService_h

#include <ESP8266React.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

class AlarmsService {
 public:
  AlarmsService(AsyncWebServer* server, FS* fs);
  void begin();
  void loop();

 private:
  void alarmsPostBodyHandler(AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total);
  void writeAlarmsState(DynamicJsonDocument& doc);
  // void alarmsGetHandler(AsyncWebServerRequest* request);
  // void readAlarmsState();
  // void onAlarmsStateUpdate();

  AsyncWebServer* _server;
  FS* _fs;
};

#endif
