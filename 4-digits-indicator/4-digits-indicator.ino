int pins[8] = {9, 13, 4, 6, 7, 10, 3, 5};

byte numbers[10] = 
{
  B11111100,
  B01100000,
  B11011010,
  B11110010,
  B01100110,
  B10110110,
  B10111110,
  B11100000,
  B11111110,
  B11110110
};

int number = 0;

int pinDigits[4] = {8, 11, 12, 2};

int digit = 0;

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
    digitalWrite(pinDigits[i], HIGH);
  }
}

void loop() 
{
  number = (number + 1) % 10;
  // number = 8;
  
  showNumber(number);
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(pinDigits[i], HIGH);
    digit = random(0, 4);
    digitalWrite(pinDigits[digit], LOW);
    delay(1000);
  }
}

void showNumber(int num)
{
  for(int i = 0; i < 8; i++)
  {
    if (bitRead(numbers[num], 7 - i) == HIGH)
    {
      digitalWrite(pins[i], LOW);
    }
    else
    {
      digitalWrite(pins[i], HIGH);
    }
  }
}
