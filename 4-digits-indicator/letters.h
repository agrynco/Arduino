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

struct char_2_mask_map
{
	char c;
	byte mask;
};