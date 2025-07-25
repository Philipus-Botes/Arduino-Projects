// --- Motion Alarm System with Reset and Exit Delay ---
// Description: Triggers a buzzer when motion is detected.
// Press the reset button to stop the alarm and rearm after a 20s exit delay.

const int pirPin = 2;        // PIR motion sensor digital output
const int buzzerPin = 3;     // Buzzer pin (active buzzer)
const int resetPin = 4;      // Button pin to reset and rearm the system

bool systemArmed = true;     // Alarm system starts armed
bool alarmTriggered = false;

unsigned long delayStart = 0;
const unsigned long exitDelay = 20000; // 20 seconds in milliseconds

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(resetPin, INPUT_PULLUP); // Button connected to GND
  digitalWrite(buzzerPin, LOW);    // Ensure buzzer is off

  Serial.begin(9600);
  Serial.println("Motion Alarm System Initialized.");
  Serial.println("System is armed.");
}

void loop() {
  // If system is armed and motion is detected, trigger the alarm
  if (systemArmed && digitalRead(pirPin) == HIGH) {
    alarmTriggered = true;
    digitalWrite(buzzerPin, HIGH);
    Serial.println("Motion Detected! Alarm Triggered!");
  }

  // If reset button is pressed (LOW because of INPUT_PULLUP)
  if (digitalRead(resetPin) == LOW) {
    Serial.println("Reset button pressed.");
    resetAlarm();
  }
}

// Function to reset the alarm and re-arm system after exit delay
void resetAlarm() {
  // Stop buzzer
  digitalWrite(buzzerPin, LOW);
  alarmTriggered = false;
  systemArmed = false;

  Serial.println("Alarm stopped.");
  Serial.println("Exit delay started (20 seconds to leave area)...");

  delayStart = millis();

  // Wait for 20 seconds before rearming
  while (millis() - delayStart < exitDelay) {
    // Allow button bounce handling or later upgrades
  }

  systemArmed = true;
  Serial.println("System rearmed.");
}