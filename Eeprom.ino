void EepromSetup()
{
	Clear();
}

void SaveValue(byte addr, byte value)
{
	EEPROM.update(addr, value);
}

byte GetValue(byte addr)
{
	return EEPROM.read(addr);
}

void Clear()
{
	for (int i = 0; i < EEPROM.length(); i++) {
		EEPROM.write(i, 0);
	}
}