byte grad[8] = {
	B11100,
	B10100,
	B11100,
	B00000,
	B00000,
	B00000,
	B00000,
};

bool is_on = true;

LiquidCrystal lcd(12, 11, 5, 4, 6, 7);

void LcdSeteup()
{
	lcd.begin(COLUMNS, ROWS);
	lcd.createChar(0, grad);
}

void PrintHeader(const char* word)
{
	lcd.setCursor(0, 0);
	lcd.print(word);
}

void PrintAt(char* word, int x, int y)
{
	lcd.setCursor(x, y);
	lcd.print(word);
}

void PrintAt(float number, int x, int y)
{
	lcd.setCursor(x, y);
	lcd.print(number);
}

void PrintAt(String word, int x, int y)
{
	lcd.setCursor(x, y);
	lcd.print(word);
}

void WriteAt(byte b, int x, int y)
{
	lcd.setCursor(x, y);
	lcd.write(b);
}

void ClearDisplay()
{
	lcd.clear();
}
