import { AxiosPromise } from "axios";

import { AXIOS } from "../api/endpoints";
import { AlarmsState, LightMqttSettings, LightState } from "./types";

export function readAlarmsState(): AxiosPromise<AlarmsState> {
  return AXIOS.get("/alarmsState");
}

export function updateAlarmsState(alarmsState: AlarmsState): AxiosPromise<AlarmsState> {
  return AXIOS.post("/alarmsState", alarmsState);
}

export function readLightState(): AxiosPromise<LightState> {
  return AXIOS.get("/lightState");
}

export function updateLightState(lightState: LightState): AxiosPromise<LightState> {
  return AXIOS.post("/lightState", lightState);
}

export function readBrokerSettings(): AxiosPromise<LightMqttSettings> {
  return AXIOS.get("/brokerSettings");
}

export function updateBrokerSettings(
  lightMqttSettings: LightMqttSettings
): AxiosPromise<LightMqttSettings> {
  return AXIOS.post("/brokerSettings", lightMqttSettings);
}
