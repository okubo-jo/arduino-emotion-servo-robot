#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define BUTTON_PIN 2
#define SERVO_PIN 9

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Servo myServo;

int emotion = 0;
int lastButtonState = HIGH;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  myServo.attach(SERVO_PIN);
  myServo.write(90);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  // ボタンで感情切り替え
  if (lastButtonState == HIGH && buttonState == LOW) {
    emotion++;
    if (emotion > 2) emotion = 0;
    delay(200);
  }
  lastButtonState = buttonState;

  display.clearDisplay();

  if (emotion == 0) {
    happyFace();
    happyMove();
  } else if (emotion == 1) {
    angryFace();
    angryMove();
  } else {
    sleepyFace();
    sleepyMove();
  }

  display.display();
}

// ---------- 表情 ----------
void happyFace() {
  display.fillCircle(40, 30, 10, WHITE);
  display.fillCircle(88, 30, 10, WHITE);
}

void angryFace() {
  display.drawLine(30, 20, 50, 30, WHITE);
  display.drawLine(78, 30, 98, 20, WHITE);
}

void sleepyFace() {
  display.drawLine(30, 30, 50, 30, WHITE);
  display.drawLine(78, 30, 98, 30, WHITE);
}

// ---------- 動き ----------
void happyMove() {
  for (int i = 70; i <= 110; i++) {
    myServo.write(i);
    delay(10);
  }
  for (int i = 110; i >= 70; i--) {
    myServo.write(i);
    delay(10);
  }
}

void angryMove() {
  myServo.write(60);
  delay(100);
  myServo.write(120);
  delay(100);
}

void sleepyMove() {
  myServo.write(120);
  delay(500);
}