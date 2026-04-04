// 🔧 Configuration
const int mq135Pin = A0;
int ledPin = 9;

const float R0 = 320.0;      
const float RL = 10.0;      
const float VOLT_RES = 5.0; 

const float CO2_A = 110.47; 
const float CO2_B = -2.862;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
  pinMode(ledPin, OUTPUT);

  Serial.println("System Ready...");
}

void loop() {

  // 🔹 1. Receive PWM from ESP32
  if (Serial.available() > 0) {
    int pwmValue = Serial.parseInt();

    while (Serial.available() > 0) {
      Serial.read(); // clear buffer
    }

    pwmValue = constrain(pwmValue, 0, 255);
    analogWrite(ledPin, pwmValue);
  }

  // 🔹 2. Read MQ135
  int adcValue = analogRead(mq135Pin);

  // 🔹 3. Convert to Voltage
  float voltage = (adcValue / 1023.0) * VOLT_RES;

  if (voltage > 0) {

    // 🔹 4. Calculate Rs
    float rs = ((VOLT_RES * RL) / voltage) - RL;

    // 🔹 5. Calculate Ratio
    float ratio = rs / R0;

    // 🔹 6. Calculate CO2 PPM
    float ppm = CO2_A * pow(ratio, CO2_B);

    // 🔹 7. Send Data to ESP32
    Serial.print("CO2:");
    Serial.println(ppm);
  }

  delay(1000);
}