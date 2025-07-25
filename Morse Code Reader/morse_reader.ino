#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize 16x2 I2C LCD at address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin Definitions
const int morseButtonPin = 2;     // Button for Morse input
const int submitButtonPin = 3;    // Button to submit and translate
const int dotThreshold = 300;     // Max ms for a dot press
const int debounceDelay = 50;

String morseInput = "";
String translatedText = "";

unsigned long pressStartTime = 0;
bool morseButtonState = HIGH;
bool prevMorseButtonState = HIGH;
bool translated = false;

// Morse code map
const int morseCount = 36;
const String morseAlphabet[morseCount][2] = {
  {".-", "A"},   {"-...", "B"}, {"-.-.", "C"}, {"-..", "D"},
  {".", "E"},    {"..-.", "F"}, {"--.", "G"},  {"....", "H"},
  {"..", "I"},   {".---", "J"}, {"-.-", "K"},  {".-..", "L"},
  {"--", "M"},   {"-.", "N"},   {"---", "O"},  {".--.", "P"},
  {"--.-", "Q"}, {".-.", "R"},  {"...", "S"},  {"-", "T"},
  {"..-", "U"},  {"...-", "V"}, {".--", "W"},  {"-..-", "X"},
  {"-.--", "Y"}, {"--..", "Z"},
  {"-----", "0"},{".----", "1"},{"..---", "2"},{"...--", "3"},
  {"....-", "4"},{".....", "5"},{"-....", "6"},{"--...", "7"},
  {"---..", "8"},{"----.", "9"}
};

// Function to split Morse input by spaces and translate to text
String translateMorse(String morse) {
  String result = "";
  int start = 0;
  while (start < morse.length()) {
    int spaceIdx = morse.indexOf(' ', start);
    if (spaceIdx == -1) spaceIdx = morse.length();
    String symbol = morse.substring(start, spaceIdx);
    bool found = false;

    for (int i = 0; i < morseCount; i++) {
      if (symbol == morseAlphabet[i][0]) {
        result += morseAlphabet[i][1];
        found = true;
        break;
      }
    }

    if (!found && symbol != "") result += "?";  // Unknown symbol

    start = spaceIdx + 1;
  }
  return result;
}

// Scroll text if too long for LCD
void displayScrollingText(String text) {
  int len = text.length();
  if (len <= 16) {
    lcd.setCursor(0, 1);
    lcd.print(text);
    return;
  }

  for (int i = 0; i <= len - 16; i++) {
    lcd.setCursor(0, 1);
    lcd.print(text.substring(i, i + 16));
    delay(300);
  }
}

void setup() {
  pinMode(morseButtonPin, INPUT_PULLUP);
  pinMode(submitButtonPin, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Morse Input:");
  Serial.begin(9600);
}

void loop() {
  // Read button states
  bool currentMorse = digitalRead(morseButtonPin);
  bool submitPressed = digitalRead(submitButtonPin) == LOW;

  // Handle Morse button
  if (prevMorseButtonState == HIGH && currentMorse == LOW) {
    pressStartTime = millis();
  }
  else if (prevMorseButtonState == LOW && currentMorse == HIGH) {
    unsigned long pressDuration = millis() - pressStartTime;
    if (pressDuration >= debounceDelay) {
      if (pressDuration < dotThreshold) {
        morseInput += ".";
      } else {
        morseInput += "-";
      }

      // Display input live
      lcd.setCursor(0, 1);
      if (morseInput.length() <= 16) {
        lcd.print(morseInput);
      } else {
        lcd.print(morseInput.substring(morseInput.length() - 16));
      }

      Serial.print("Morse: ");
      Serial.println(morseInput);
    }
  }

  // Handle Submit button
  if (submitPressed) {
    delay(200); // Basic debounce
    while (digitalRead(submitButtonPin) == LOW); // Wait for release

    if (!translated) {
      // Add space separator between symbols
      morseInput += " ";
      translatedText = translateMorse(morseInput);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Translated:");
      displayScrollingText(translatedText);
      translated = true;
    } else {
      // Reset state for new input
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Morse Input:");
      morseInput = "";
      translatedText = "";
      translated = false;
    }
  }

  prevMorseButtonState = currentMorse;
}