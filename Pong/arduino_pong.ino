#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

// --- LCD Setup (adjust I2C address if needed) ---
LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- Pin Definitions ---
const int BUTTON_UP = 2;
const int BUTTON_DOWN = 3;

// --- Game State Variables ---
int ballX = 8;
int ballY = 0;
int ballDirX = 1;  // Ball moving right
int ballDirY = 1;  // Ball moving down

int paddleLeftY = 0;
int paddleRightY = 0;

unsigned long lastUpdate = 0;
int score = 0;
int highScore = 0;

// --- Constants ---
const int paddleHeight = 1;
const int fieldWidth = 16;
const int fieldHeight = 2;
const int updateInterval = 400; // ms between updates

void setup() {
  Serial.begin(9600);

  // LCD setup
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Button setup
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);

  // Read high score from EEPROM
  highScore = EEPROM.read(0);

  lcd.setCursor(0, 0);
  lcd.print("Arduino Pong");
  delay(1000);
  lcd.clear();
}

void loop() {
  // Read buttons
  if (digitalRead(BUTTON_UP) == LOW) {
    if (paddleLeftY > 0) paddleLeftY--;
    delay(150); // debounce
  }

  if (digitalRead(BUTTON_DOWN) == LOW) {
    if (paddleLeftY < fieldHeight - paddleHeight) paddleLeftY++;
    delay(150); // debounce
  }

  // Update game state
  if (millis() - lastUpdate >= updateInterval) {
    updateGame();
    lastUpdate = millis();
  }
}

void updateGame() {
  // Move the ball
  ballX += ballDirX;
  ballY += ballDirY;

  // Bounce off top/bottom
  if (ballY < 0 || ballY >= fieldHeight) {
    ballDirY *= -1;
    ballY += ballDirY;
  }

  // Check for paddle collisions
  if (ballX == 1 && ballY == paddleLeftY) {
    ballDirX = 1;
    score++;
  } else if (ballX == fieldWidth - 2 && ballY == paddleRightY) {
    ballDirX = -1;
    score++;
  }

  // AI movement (basic logic)
  if (ballDirX == 1 && ballX >= 12) { // ball approaching right paddle
    if (paddleRightY < ballY) paddleRightY++;
    else if (paddleRightY > ballY) paddleRightY--;
  }

  // Game over if ball escapes
  if (ballX < 0 || ballX >= fieldWidth) {
    gameOver();
    return;
  }

  drawGame();
}

void drawGame() {
  lcd.clear();

  // Left paddle
  lcd.setCursor(0, paddleLeftY);
  lcd.print("|");

  // Right paddle (AI)
  lcd.setCursor(fieldWidth - 1, paddleRightY);
  lcd.print("|");

  // Ball
  lcd.setCursor(ballX, ballY);
  lcd.print("o");

  // Score
  lcd.setCursor(4, 1);
  lcd.print("S:");
  lcd.print(score);

  lcd.setCursor(10, 1);
  lcd.print("H:");
  lcd.print(highScore);
}

void gameOver() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Game Over!");

  lcd.setCursor(2, 1);
  lcd.print("Score: ");
  lcd.print(score);
  delay(2000);

  // Save high score
  if (score > highScore) {
    highScore = score;
    EEPROM.write(0, highScore);
  }

  // Reset game
  score = 0;
  ballX = 8;
  ballY = 0;
  ballDirX = 1;
  ballDirY = 1;
  paddleLeftY = 0;
  paddleRightY = 0;

  lcd.clear();
}