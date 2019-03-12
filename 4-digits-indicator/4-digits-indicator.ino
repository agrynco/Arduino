#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor 
#define DHTTYPE    DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

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

int pins[] = { 9, 13, 4, 6, 7, 10, 3, 5 };
int pinDigits[] = { 8, 11, 12, A4 };

int const DELAY = 1;
int loopsCounter = 0;
int numberToDisplay = 9999;

String textToDisplay = String(numberToDisplay);

String temperature = " ";
String humidity = " ";

enum DisplayMode { Temperature, Humidity };
DisplayMode displayMode = Temperature;

unsigned long previousMillis = 0;

void showMask(byte mask)
{
	for (int i = 0; i < 8; i++)
	{
		digitalWrite(pins[i], !bitRead(mask, 7 - i));
	}
}

void setup()
{
	Serial.begin(9600);
	// Initialize device.
	dht.begin();
	Serial.println(F("DHTxx Unified Sensor Example"));
	// Print temperature sensor details.
	sensor_t sensor;
	dht.temperature().getSensor(&sensor);
	Serial.println(F("------------------------------------"));
	Serial.println(F("Temperature Sensor"));
	Serial.print(F("Sensor Type: ")); Serial.println(sensor.name);
	Serial.print(F("Driver Ver:  ")); Serial.println(sensor.version);
	Serial.print(F("Unique ID:   ")); Serial.println(sensor.sensor_id);
	Serial.print(F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
	Serial.print(F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
	Serial.print(F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
	Serial.println(F("------------------------------------"));
	// Print humidity sensor details.
	dht.humidity().getSensor(&sensor);
	Serial.println(F("Humidity Sensor"));
	Serial.print(F("Sensor Type: ")); Serial.println(sensor.name);
	Serial.print(F("Driver Ver:  ")); Serial.println(sensor.version);
	Serial.print(F("Unique ID:   ")); Serial.println(sensor.sensor_id);
	Serial.print(F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
	Serial.print(F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
	Serial.print(F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
	Serial.println(F("------------------------------------"));
	// Set delay between sensor readings based on sensor details.
	delayMS = sensor.min_delay / 1000;

	for (int i = 0; i < 8; i++)
	{
		pinMode(pins[i], OUTPUT);
		digitalWrite(pinDigits[i], LOW);
	}

	for (int i = 0; i < 4; i++)
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
		if (i < text.length() - 1)
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

String replsceLastZerro(const String s, const char c)
{
	if (s.length() < 6)
	{
		if (s.endsWith("0"))
		{
			s.setCharAt(s.length() - 1, c);
		}
	}

	return s;
}

void loop()
{
	loopsCounter++;
	if ((loopsCounter % 250) == 0)
	{
		// Get temperature event and print its value.
		sensors_event_t event;
		dht.temperature().getEvent(&event);
		if (isnan(event.temperature)) {
			//Serial.println(F("Error reading temperature!"));
			displayText("Err.C");
		}
		else {
			Serial.print(F("Temperature: "));
			Serial.print(event.temperature);
			Serial.print("°C");
			temperature = String(event.temperature);
		}
		dht.humidity().getEvent(&event);
		if (isnan(event.relative_humidity)) {
			//Serial.println(F("Error reading humidity!"));
			displayText("Err.H");
		}
		else
		{
			Serial.print(F("    Humidity: "));
			Serial.print(event.relative_humidity);
			Serial.print("%");
			humidity = String(event.relative_humidity);
		}

		loopsCounter = 0;
	}

	unsigned long currentMillis = millis();
	if (currentMillis - previousMillis >= 10000)
	{
		displayMode = (displayMode == Temperature ? Humidity : Temperature);

		previousMillis = currentMillis;
	}

	switch (displayMode)
	{
	case Temperature:
		displayText(replsceLastZerro(temperature, 'C'));
		break;
	case Humidity:
		displayText(replsceLastZerro(humidity, 'H'));
	default:;
	}
}

