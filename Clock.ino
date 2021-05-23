#define OFF 0
#define ON 1

volatile byte hours = 0;
volatile byte minutes = 0;

volatile byte alarm_hours = 0;
volatile byte alarm_minutes = 0;
volatile byte is_alarm_on = 0;

void PrintAlarmActive()
{
	ClearDisplay();
	PrintHeader("Wecker aktiv?");
	PrintValue();
}

bool ToggleAlarm()
{
	return (is_alarm_on == ON && hours == alarm_hours && minutes == alarm_minutes);
}

void MakeAlarm()
{
	if (ToggleAlarm() || light_sensor_value > LIGHT_IS_ON )
	{
		digitalWrite(LED_PIN, HIGH);
	}
	else
	{
		digitalWrite(LED_PIN, LOW);
	}
}

void AlarmSetup()
{
	is_alarm_on = GetValue(IS_ALARM_ON_ADDR) % 2;
	alarm_hours = GetValue(ALARM_HOUR_ADDR) % 24;
	alarm_minutes = GetValue(ALARM_MINUTE_ADDR) % 60;
}

void PrintValue()
{
	Serial.println(is_alarm_on);
	switch (is_alarm_on)
	{
	case OFF:
	{
		PrintAt("Aus", 7, 1);
		break;
	}
	case ON:
	{
		PrintAt("An", 7, 1);
		break;
	}
	}
}

void ChangeAlarm()
{
	is_alarm_on = (is_alarm_on + 1) % 2;
}

void SaveSettings()
{
	SaveValue(IS_ALARM_ON_ADDR, is_alarm_on);
	SaveValue(ALARM_HOUR_ADDR, alarm_hours);
	SaveValue(ALARM_MINUTE_ADDR, alarm_minutes);
}

void PrintClock(byte refresh_mode)
{
	if (refresh_mode == REFRESH_ALL)
	{
		ClearDisplay();
		PrintHeader("Akt. Uhrzeit:");
	}
	PrintTime();
	PrintColon();
}

void PrintTime()
{
	PrintHour(NORMAL_MODE);
	PrintMinute(NORMAL_MODE);
}

void PrintEditClock(byte refresh_mode, byte mode)
{
	if (refresh_mode == REFRESH_ALL)
	{
		ClearDisplay();
		if (mode == EDIT_HOUR_MODE || mode == EDIT_MINUTE_MODE)
		{
			PrintHeader("Uhrzeit einst.");
		}
		else if (mode == SET_ALARM_HOUR_MODE || mode == SET_ALARM_MINUTE_MODE)
		{
			PrintHeader("Alarm einst.");
		}
		PrintColon();
	}
	PrintEditTime(mode);
}

void PrintEditTime(byte mode)
{
	if (mode == EDIT_HOUR_MODE || mode == SET_ALARM_HOUR_MODE)
	{
		PrintEditHour(mode);
	}
	else if (mode == EDIT_MINUTE_MODE || mode == SET_ALARM_MINUTE_MODE)
	{
		PrintEditMinute(mode);
	}
}

void PrintEditHour(byte mode)
{
	PrintMinute(mode);
	if (milliseconds_past % 1000 == 500)
	{
		PrintHour(mode);
	}
	else
	{
		PrintAt("  ", 5, 1);
	}
	
}

void PrintEditMinute(byte mode)
{
	PrintHour(mode);
	if (milliseconds_past % 1000 == 500)
	{
		Serial.println("PrintMinute");
		PrintMinute(mode);
	}
	else
	{
		PrintAt("  ", 8, 1);
	}
}

void PrintHour(byte mode)
{
	char outStr[2];
	if (mode < SET_ALARM_HOUR_MODE)
	{
		sprintf(outStr, "%02d", hours);
	}
	else if (mode == SET_ALARM_HOUR_MODE || mode == SET_ALARM_MINUTE_MODE)
	{
		sprintf(outStr, "%02d", alarm_hours);
	}
	PrintAt(outStr, 5, 1);
}

void PrintMinute(byte mode)
{
	char outStr[2];
	if (mode < SET_ALARM_HOUR_MODE)
	{
		sprintf(outStr, "%02d", minutes);
	}
	else if (mode == SET_ALARM_HOUR_MODE || mode == SET_ALARM_MINUTE_MODE)
	{
		sprintf(outStr, "%02d", alarm_minutes);
	}
	PrintAt(outStr, 8, 1);
}

void PrintColon()
{
	if (GetMode() > 0 || milliseconds_past % 1000 == 500)
	{
		PrintAt(":", 7, 1);
	}
	else
	{
		PrintAt(" ", 7, 1);
	}
}

void UpdateTime()
{
	if ((milliseconds_past % 60000) == 0)
	{
		UpdateMinutes();
	}
}

void UpdateMinutes()
{
	if (minutes == 59)
	{
		UpdateHours();
	}
	minutes = (minutes + 1) % 60;
}

void UpdateHours()
{
	hours = (hours + 1) % 24;
}

void UpdateAlarmMinutes()
{
	if (alarm_minutes == 59)
	{
		UpdateAlarmHours();
	}
	alarm_minutes = (alarm_minutes + 1) % 60;
}

void UpdateAlarmHours()
{
	alarm_hours = (alarm_hours + 1) % 24;
}
