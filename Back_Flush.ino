int valve_control_relay = 8;
int pump_control_relay = 12;

//int tilt_switch_position = 0;
int man_backflush_switch_position = 0;
int manual_auto_switch_position = 0;

int man_backflush_switch = 2;
int manual_auto_control_switch = 13;
//int tilt_switch = 4;

unsigned long previous_time = 0;
unsigned long prev_time = 0;
unsigned long weekly_timer;

long time_interval = 1000;
long weekly_interval = 604800000;// one week in Milliseconds

void setup() {
  //pinMode(tilt_switch, INPUT);
  pinMode(man_backflush_switch, INPUT);
  pinMode(manual_auto_control_switch, INPUT);
  pinMode(valve_control_relay, OUTPUT);
  pinMode(pump_control_relay, OUTPUT);

  Serial.begin(9600);

  digitalWrite(valve_control_relay, HIGH);
  digitalWrite(pump_control_relay, HIGH);
}

void loop() {
  weekly_timer = millis();

  //tilt_switch_position = digitalRead(tilt_switch);
  manual_auto_switch_position = digitalRead(manual_auto_control_switch);

  if (manual_auto_switch_position == LOW) {
    man_backflush_switch_position = digitalRead(man_backflush_switch);

    if (man_backflush_switch_position == LOW) {
      valve_open();
      pump_on();
      pump_off();
      valve_close();
    }
  } 
  else if (manual_auto_switch_position == HIGH) {
    if (weekly_timer - prev_time >= weekly_interval) {
      prev_time = weekly_timer;
      Serial.println(prev_time);
      valve_open();
      pump_on();
      pump_off();
      valve_close();
    }
  }
}

void valve_open() {
  digitalWrite(valve_control_relay, LOW);
  count_down_timer(15);
}

void valve_close() {
  digitalWrite(valve_control_relay, HIGH);
  count_down_timer(15);
}

void pump_on() {
  digitalWrite(pump_control_relay, LOW);
  count_down_timer(15);
}

void pump_off() {
  digitalWrite(pump_control_relay, HIGH);
  count_down_timer(5);
}

void count_down_timer(int timer) {
  int time_count = 0;
  while (time_count < timer) {
    unsigned long count_timer = millis();
    if (count_timer - previous_time >= time_interval) {
      previous_time = count_timer;
      time_count += 1;
      Serial.println(time_count);
    }
  }
}