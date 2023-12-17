int valve_control_relay = 8;
int pump_control_relay = 12;

//int tilt_switch_position = 0;
int man_backflush_switch_position = 0;
int man_control_switch_position = 0;

int man_backflush_switch = 2;
int man_control_switch = 13;
//int tilt_switch = 4;

void setup() {
  //pinMode(tilt_switch, INPUT);
  pinMode(man_backflush_switch, INPUT);
  pinMode(man_control_switch, INPUT);
  pinMode(valve_control_relay, OUTPUT);
  pinMode(pump_control_relay, OUTPUT);

  digitalWrite(valve_control_relay, HIGH);
  digitalWrite(pump_control_relay, HIGH);
}

void loop() {
  //tilt_switch_position = digitalRead(tilt_switch);
  man_control_switch_position = digitalRead(man_control_switch);


  if (man_control_switch_position == LOW) {
    man_backflush_switch_position = digitalRead(man_backflush_switch);

    if (man_backflush_switch_position == LOW) {
      valve_open();
      pump_on();
      pump_off();
      valve_close();
    }
  }
}

void valve_open() {
  digitalWrite(valve_control_relay, LOW);
  delay(15000);
}

void valve_close() {
  digitalWrite(valve_control_relay, HIGH);
  delay(15000);
}

void pump_on() {
  digitalWrite(pump_control_relay, LOW);
  delay(15000);
}

void pump_off() {
  digitalWrite(pump_control_relay, HIGH);
  delay(5000);
}