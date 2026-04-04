// R0 Calibration Code
const int SENSOR_PIN = A0;
const float RL = 10.0;      // Update this if your board uses 1k (1.0)
const float VOLT_RES = 5.0; 

// The expected Rs/R0 ratio for 400 PPM fresh air
// Calculated from: 400 = 110.47 * (Ratio)^-2.862
const float FRESH_AIR_RATIO = 0.638; 

void setup() {
  Serial.begin(9600);
}

void loop() {
  int adcValue = analogRead(SENSOR_PIN);
  float voltage = (adcValue / 1023.0) * VOLT_RES;
  
  if (voltage > 0) {
    // Calculate current resistance (Rs)
    float rs = ((VOLT_RES * RL) / voltage) - RL;
    
    
    // Calculate what R0 MUST be to equal 400 PPM
    float current_R0 = rs / FRESH_AIR_RATIO;
    
    Serial.print("Voltage: "); Serial.print(voltage);
    Serial.print("V | Calculated True R0: "); Serial.print(current_R0);
    Serial.println(" kohm");
  }
  delay(2000);
}