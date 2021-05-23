volatile unsigned long prev_button_time = 0;
bool is_visible = true;
volatile byte mode = 0;
volatile int refresh_mode = REFRESH_ALL;
byte display_info = 0;

void SwitchMode()
{
	if ((current_time - prev_button_time) > DEBOUNCE_TIME)
	{
		switch (mode)
		{
		case SET_ALARM_ON_MODE:
		{
			SaveSettings();
			break;
		}
		}
		mode = (mode + 1) % MODI_COUNT;
		refresh_mode = REFRESH_ALL;
		prev_button_time = current_time;
	}
}

void SelectMode()
{
	switch (mode)
	{
	case NORMAL_MODE:
	{
		PrintNormal();
		break;
	}
	case EDIT_HOUR_MODE:
	{
		PrintEdit(EDIT_HOUR_MODE);
		break;
	}
	case EDIT_MINUTE_MODE:
	{
		PrintEdit(EDIT_MINUTE_MODE);
		break;
	}
	case SET_ALARM_ON_MODE:
	{
		PrintAlarmActive();
		break;
	}
	case SET_ALARM_HOUR_MODE:
	{
		PrintEdit(SET_ALARM_HOUR_MODE);
		break;
	}
	case SET_ALARM_MINUTE_MODE:
	{
		PrintEdit(SET_ALARM_MINUTE_MODE);
		break;
	}
	}
}

void PrintNormal()
{
	if ((milliseconds_past % DISPLAY_SWITCH_INTERVALL) == 0)
	{
		display_info = (display_info + 1) % 2;
		refresh_mode = REFRESH_ALL;
	}
	if (display_info == 0)
	{
		PrintClock(refresh_mode);
	}
	else if (display_info == 1)
	{
		PrintTemperature(refresh_mode);
	}
	refresh_mode = REFRESH_TIME_ONLY;
}
void PrintEdit(byte mode)
{
	PrintEditClock(refresh_mode, mode);
	refresh_mode = REFRESH_TIME_ONLY;
}

void ChangeClock()
{
	if ((current_time - prev_button_time) > DEBOUNCE_TIME)
	{
		switch (mode)
		{
			case EDIT_HOUR_MODE:
			{
				UpdateHours();
				break;
			}
			case EDIT_MINUTE_MODE:
			{
				UpdateMinutes();
				break;
			}
			case SET_ALARM_ON_MODE:
			{
				ChangeAlarm();
				break;
			}
			case SET_ALARM_HOUR_MODE:
			{
				UpdateAlarmHours();
				break;
			}
			case SET_ALARM_MINUTE_MODE:
			{
				UpdateAlarmMinutes();
				break;
			}
		}
		prev_button_time = current_time;
	}
}

byte GetMode()
{
	return mode;
}
