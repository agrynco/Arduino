#include "letters.h"
#include "numbers.h"

int pins[] = {9, 13, 4, 6, 7, 10, 3, 5};
int pinDigits[] = {8, 11, 12, 2};

char_2_mask_map char_2_mask_maps[] =
{
	{'A', CHAR_A},
	{'C', CHAR_C},
	{'O', CHAR_O},
	{'E', CHAR_E},
	{'r', CHAR_r},
	{'H', CHAR_H},
	{'h', CHAR_h},
	{'d', CHAR_d},
	{'b', CHAR_b},
	{'.', CHAR_DOT},
	{' ', CHAR_SPACE},

	{'0', ZERO},
	{'1', ONE},
	{'2', TWO},
	{'3', THREE},
	{'4', FOUR},
	{'5', FIVE},
	{'6', SIX},
	{'7', SEVEN},
	{'8', EIGHT},
	{'9', NINE}
};

int const DELAY = 1;

int loopsCounter = 0;

int numberToDisplay = 0;

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

void loop() 
{
	loopsCounter++;
	if ((loopsCounter % (100 / (textToDisplay.length() + 2))) == 0)
	{
		numberToDisplay++;
		textToDisplay = String(numberToDisplay);
		loopsCounter = 0;
	}
	
	int digitNumber = 0;

	for (byte i = 0; i < textToDisplay.length(); i++)
	{
		if (i < textToDisplay.length() -1)
		{
			if (textToDisplay.charAt(i) != '.' && textToDisplay.charAt(i + 1) == '.')
			{
				showMask(digitNumber, getMask(textToDisplay[i], true));
				continue;
			}
		}
		showMask(digitNumber, getMask(textToDisplay[i]));
		digitNumber++;
	}
}

