// letters.h
#pragma once

byte const CHAR_A = B11101110;
byte const CHAR_C = B10011100;
byte const CHAR_O = B11111100;
byte const CHAR_E = B10011110;
byte const CHAR_r = B00001010;
byte const CHAR_H = B01101110;
byte const CHAR_h = B00101110;
byte const CHAR_b = B00111110;
byte const CHAR_d = B01111010;
byte const CHAR_DOT = B00000001;

byte const CHAR_SPACE = B00000000;

byte const ZERO = B11111100;
byte const ONE = B01100000;
byte const TWO = B11011010;
byte const THREE = B11110010;
byte const FOUR = B01100110;
byte const FIVE = B10110110;
byte const SIX = B10111110;
byte const SEVEN = B11100000;
byte const EIGHT = B11111110;
byte const NINE = B11110110;

struct char_2_mask_map
{
	char c;
	byte mask;
};

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