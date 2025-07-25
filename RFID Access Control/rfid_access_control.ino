#include <SPI.h>
#include <MFRC522.h>

// --- Pin Definitions ---
#define SS_PIN 10         // RFID SS (SDA)
#define RST_PIN 9         // RFID Reset
#define BUZZER_PIN 6      // Buzzer output
#define RED_PIN 3         // RGB LED Red (PWM)
#define GREEN_PIN 5       // RGB LED Green (PWM)
#define BLUE_PIN 4        // RGB LED Blue (PWM)

// --- RFID Reader Setup ---
MFRC522 rfid(SS_PIN, RST_PIN);

// --- Authorized RFID UIDs (in uppercase hex) ---
const String authorizedUIDs[] = {
  "A1B2C3D4",  // Replace with your tag's UID
  "12345678"   // Add more UIDs as needed
};

// --- Setup ---
void setup() {
  Serial.begin(9600);
  SPI.begin();            // Init SPI bus
  rfid.PCD_Init();        // Init RFID reader
  Serial.println("RFID Access Control System Initialized.");

  // Set pin modes
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  setRGB(0, 0, 255); // Blue = Ready
}

// --- Main Loop ---
void loop() {
  // Check for new RFID card
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Read UID and convert to string
  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) uid += "0";  // Leading zero
    uid += String(rfid.uid.uidByte[i], HEX);
  }
  uid.toUpperCase();  // Normalize to uppercase

  Serial.print("Card UID: ");
  Serial.println(uid);

  // Check authorization
  if (isAuthorized(uid)) {
    Serial.println("Access Granted");
    accessGrantedFeedback();
  } else {
    Serial.println("Access Denied");
    accessDeniedFeedback();
  }

  // Halt card and stop encryption
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  delay(1000);
}

// --- Check if UID is Authorized ---
bool isAuthorized(String uid) {
  for (unsigned int i = 0; i < sizeof(authorizedUIDs) / sizeof(authorizedUIDs[0]); i++) {
    if (uid == authorizedUIDs[i]) {
      return true;
    }
  }
  return false;
}

// --- Feedback: Access Granted ---
void accessGrantedFeedback() {
  setRGB(0, 255, 0);               // Green
  tone(BUZZER_PIN, 1000, 200);     // Short beep
  delay(500);
  setRGB(0, 0, 255);               // Back to blue
}

// --- Feedback: Access Denied ---
void accessDeniedFeedback() {
  setRGB(255, 0, 0);               // Red
  tone(BUZZER_PIN, 1000, 200);     // Beep 1
  delay(250);
  tone(BUZZER_PIN, 1000, 200);     // Beep 2
  delay(500);
  setRGB(0, 0, 255);               // Back to blue
}

// --- Control RGB LED (Common Anode assumed) ---
void setRGB(int r, int g, int b) {
  analogWrite(RED_PIN, 255 - r);     // Invert for common anode
  analogWrite(GREEN_PIN, 255 - g);
  analogWrite(BLUE_PIN, 255 - b);
}