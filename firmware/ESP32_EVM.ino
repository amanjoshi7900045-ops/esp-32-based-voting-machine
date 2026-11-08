#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Educational ESP32 EVM prototype.
// Votes are stored in RAM and reset on restart.
LiquidCrystal_I2C lcd(0x27, 16, 2);

const uint8_t BUTTON_C1 = 18;
const uint8_t BUTTON_C2 = 19;
const uint8_t BUTTON_C3 = 23;
const uint8_t BUTTON_RESULTS = 25;

const uint8_t LED_C1 = 26;
const uint8_t LED_C2 = 27;
const uint8_t LED_C3 = 32;

uint32_t votes1 = 0;
uint32_t votes2 = 0;
uint32_t votes3 = 0;

const unsigned long debounceMs = 250;
unsigned long lastPressC1 = 0;
unsigned long lastPressC2 = 0;
unsigned long lastPressC3 = 0;
unsigned long lastPressResults = 0;

void showReady() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ESP32 EVM Ready");
  lcd.setCursor(0, 1);
  lcd.print("Cast Your Vote");
}

void recordVote(uint8_t candidate) {
  if (candidate == 1) votes1++;
  else if (candidate == 2) votes2++;
  else if (candidate == 3) votes3++;

  digitalWrite(LED_C1, candidate == 1 ? HIGH : LOW);
  digitalWrite(LED_C2, candidate == 2 ? HIGH : LOW);
  digitalWrite(LED_C3, candidate == 3 ? HIGH : LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vote Recorded");
  lcd.setCursor(0, 1);
  lcd.print("Candidate ");
  lcd.print(candidate);
  delay(1000);

  digitalWrite(LED_C1, LOW);
  digitalWrite(LED_C2, LOW);
  digitalWrite(LED_C3, LOW);
  showReady();
}

void showResults() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("C1:");
  lcd.print(votes1);
  lcd.print(" C2:");
  lcd.print(votes2);
  lcd.setCursor(0, 1);
  lcd.print("C3:");
  lcd.print(votes3);
  delay(3500);
  showReady();
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  pinMode(BUTTON_C1, INPUT_PULLUP);
  pinMode(BUTTON_C2, INPUT_PULLUP);
  pinMode(BUTTON_C3, INPUT_PULLUP);
  pinMode(BUTTON_RESULTS, INPUT_PULLUP);

  pinMode(LED_C1, OUTPUT);
  pinMode(LED_C2, OUTPUT);
  pinMode(LED_C3, OUTPUT);

  digitalWrite(LED_C1, LOW);
  digitalWrite(LED_C2, LOW);
  digitalWrite(LED_C3, LOW);

  lcd.init();
  lcd.backlight();
  showReady();
}

void loop() {
  unsigned long now = millis();

  if (digitalRead(BUTTON_C1) == LOW && now - lastPressC1 > debounceMs) {
    lastPressC1 = now;
    recordVote(1);
  }

  if (digitalRead(BUTTON_C2) == LOW && now - lastPressC2 > debounceMs) {
    lastPressC2 = now;
    recordVote(2);
  }

  if (digitalRead(BUTTON_C3) == LOW && now - lastPressC3 > debounceMs) {
    lastPressC3 = now;
    recordVote(3);
  }

  if (digitalRead(BUTTON_RESULTS) == LOW && now - lastPressResults > debounceMs) {
    lastPressResults = now;
    showResults();
  }
}
