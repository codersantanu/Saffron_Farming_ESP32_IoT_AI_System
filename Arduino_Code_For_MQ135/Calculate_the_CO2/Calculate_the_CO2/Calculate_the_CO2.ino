// Configuration
const int SENSOR_PIN = A0;
const float R0 = 320.0;      // Your R0 in kohm
const float RL = 10.0;      // Typical Load Resistance in kohm
const float VOLT_RES = 5.0; // Arduino voltage (use 3.3 for ESP32)

// MQ-135 CO2 Curve Parameters (log-log approximation)
// Equation: PPM = a * (Rs/R0)^b
const float CO2_A = 110.47; 
const float CO2_B = -2.862;

void setup() {
  Serial.begin(9600);
  Serial.println("MQ Sensor Warping Up...");
}
 
void loop() {
  // 1. Read Analog Value
  int adcValue = analogRead(SENSOR_PIN);
  
  // 2. Calculate Voltage
  float voltage = (adcValue / 1023.0) * VOLT_RES;
  
  // 3. Calculate Sensor Resistance (Rs)
  // Prevent division by zero if voltage is 0
  if (voltage > 0) {
    float rs = ((VOLT_RES * RL) / voltage) - RL;
    float ratio = rs / R0;
    
    // 4. Calculate PPM using Power Function
    float ppm = CO2_A * pow(ratio, CO2_B);

    // Output results
    Serial.print("Voltage: "); Serial.print(voltage); Serial.print("V | ");
    Serial.print("Rs/R0: "); Serial.print(ratio); Serial.print(" | ");
    Serial.print("CO2 PPM: "); Serial.println(ppm);
  }

  delay(1000); // Wait 2 seconds between readings
}

