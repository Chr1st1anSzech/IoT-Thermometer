byte measure_count = 0;
float cumulative_temperature = 0.0;
float temperature = 0.0;


void TemperatureSetup()
{
	pinMode(TEMP_SENSOR_PIN, INPUT);
}

void PrintTemperature(byte refresh_display)
{
	if (refresh_display == REFRESH_ALL)
	{
		ClearDisplay();
		PrintHeader("Akt. Temperatur:");

		PrintAt(temperature, 5, 1);

		WriteAt(byte(0), 9, 1);

		PrintAt("C", 10, 1);
	}
}

float MeasureTemperature()
{
	if (milliseconds_past % MEASURE_INTERVALL == 0)
	{
		float voltage = analogRead(TEMP_SENSOR_PIN) / 1024.0 * 5.0;
		cumulative_temperature += (voltage - 0.5) * 100;
		measure_count++;
	}
	if (measure_count == MEASURE_COUNT)
	{
		temperature = (cumulative_temperature / MEASURE_COUNT);
		measure_count = 0;
		cumulative_temperature = 0;
	}
}
