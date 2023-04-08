export interface LightState {
  led_on: boolean;
}

export interface Alarm {
  title: string;
  time: string;
  days: string[];
  enabled: boolean;
}

export interface AlarmsState {
  alarms: Alarm[];
}

export interface LightMqttSettings {
  unique_id: string;
  name: string;
  mqtt_path: string;
}
