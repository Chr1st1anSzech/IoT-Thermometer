#include <EEPROM.h>
#include <LiquidCrystal.h>

#define LED_PIN 8
#define TEMP_SENSOR_PIN A0
#define LIGHT_SENSOR_PIN A1

#define LIGHT_IS_ON 150

#define MEASURE_COUNT 5
#define MEASURE_INTERVALL 5000

#define ROWS 2
#define COLUMNS 16

#define REFRESH_ALL 1
#define REFRESH_TIME_ONLY 2

#define DISPLAY_SWITCH_INTERVALL 15000
#define DEBOUNCE_TIME 100

#define CHANGE_BUTTON_PIN 2
#define MODE_BUTTON_PIN 3

#define MODI_COUNT 6
#define NORMAL_MODE 0
#define EDIT_HOUR_MODE 1
#define EDIT_MINUTE_MODE 2
#define SET_ALARM_ON_MODE 3
#define SET_ALARM_HOUR_MODE 4
#define SET_ALARM_MINUTE_MODE 5

#define IS_ALARM_ON_ADDR 0
#define ALARM_HOUR_ADDR 1
#define ALARM_MINUTE_ADDR 2

byte prev_switch_state = LOW;
unsigned long milliseconds_past = 0;
unsigned long current_time = 0l;
unsigned long previous_time = 0l;
int light_sensor_value;

void setup()
{
	/* add setup code here */
	//EepromSetup();
	TemperatureSetup();
	LcdSeteup();
	AlarmSetup();
	Serial.begin(9600);
	pinMode(CHANGE_BUTTON_PIN, INPUT);
	pinMode(MODE_BUTTON_PIN, INPUT);
	pinMode(LED_PIN, OUTPUT);
	attachInterrupt(digitalPinToInterrupt(MODE_BUTTON_PIN), SwitchMode, RISING);
	attachInterrupt(digitalPinToInterrupt(CHANGE_BUTTON_PIN), ChangeClock, RISING);
}

void loop()
{
	/* add main program code here */
	current_time = millis();
	long delta_time = current_time - previous_time;
	MakeAlarm();
	if (delta_time >= 500)
	{
		light_sensor_value = analogRead(LIGHT_SENSOR_PIN);
		Serial.print("Value=");
		Serial.println(light_sensor_value);

		milliseconds_past = (milliseconds_past + 500) % 60000;
		UpdateTime();
		MeasureTemperature();
		SelectMode();
		previous_time = current_time;
	}
}

