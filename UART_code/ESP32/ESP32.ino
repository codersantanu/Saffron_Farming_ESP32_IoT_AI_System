#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define RXD2 16
#define TXD2 17

int pwmValue = 120; // Example value (can come from app)

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial2.setTimeout(50); // 🔹 Stop ESP32 from freezing on bad reads

  // OLED init
  display.begin(0x3C, true);
  display.clearDisplay();
}

void loop() {

  // 🔹 Send PWM to Arduino
  Serial2.println(pwmValue);

  // 🔹 Receive M Q135 value
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    data.trim(); // 🔹 REMOVES invisible \r characters! This is crucial for OLEDs.

    if (data.length() > 0) { // Only update if real data came through
      Serial.println("MQ135: " + data);

      // 🔹 Display on OLED
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SH110X_WHITE);

      display.setCursor(0, 10);
      display.println("Air:");
      display.setCursor(0, 35);
      display.println(data);

      display.display();  
    }
  }

  delay(500); // 🔹 Matched with Arduino timing to prevent buffer overflow
}