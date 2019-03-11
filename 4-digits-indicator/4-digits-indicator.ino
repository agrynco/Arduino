#include "charMasks.h"

int pins[] = {9, 13, 4, 6, 7, 10, 3, 5};
int pinDigits[] = {8, 11, 12, 2};

int const DELAY = 1;
int loopsCounter = 0;
int numberToDisplay = 9999;

String textToDisplay = String(numberToDisplay);

void showMask(byte mask)
{
	for (int i = 0; i < 8; i++)
	{
		digitalWrite(pins[i], !bitRead(mask, 7 - i));
	}
}

void setup() 
{
  for(int i = 0; i < 8; i++)
  {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pinDigits[i], LOW);
  }
  
  for(int i = 0; i < 4; i++)
  {
    pinMode(pinDigits[i], OUTPUT);
    digitalWrite(pinDigits[i], LOW);
  }
}

void showMask(byte digitNumber, byte mask)
{
	showMask(mask);
	digitalWrite(pinDigits[digitNumber], HIGH);
	delay(DELAY);
	digitalWrite(pinDigits[digitNumber], LOW);
}

byte getMask(const char c, boolean withDot)
{
	for (auto i = 0; i < sizeof(char_2_mask_maps) / sizeof(*char_2_mask_maps); i++)
	{
		if (c == char_2_mask_maps[i].c)
		{
			byte result = char_2_mask_maps[i].mask;
			if (withDot)
			{
				result |= 1;
			}

			return result;
		}
	}

	return CHAR_SPACE;
}

byte getMask(const char c)
{
	return getMask(c, false);
}

void displayText(String text)
{
	int digitNumber = 0;

	for (byte i = 0; i < text.length(); i++)
	{
		if (i < text.length() -1)
		{
			if (text.charAt(i) != '.' && text.charAt(i + 1) == '.')
			{
				showMask(digitNumber, getMask(text[i], true));
				continue;
			}
		}
		showMask(digitNumber, getMask(text[i]));
		digitNumber++;
	}
}

void loop() 
{
	loopsCounter++;
	if ((loopsCounter % (100 / (textToDisplay.length() + 2))) == 0)
	{
		if (numberToDisplay > 9999)
		{
			numberToDisplay = 0;
		}

		numberToDisplay++;
		textToDisplay = String(numberToDisplay);
		loopsCounter = 0;
	}
	
	displayText(textToDisplay);
}

