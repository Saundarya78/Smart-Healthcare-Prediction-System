#include <Arduino.h>

// --- PhysioNet Ground Truth (Simulated Input) ---
float base_hr   = 72.0;
float base_spo2 = 98.5;
float base_temp = 36.6;

// --- Sensor Noise (Realistic Hardware Limits) ---
float hr_noise   = 2.0;
float spo2_noise = 0.5;
float temp_noise = 0.1;

void setup() {
  Serial.begin(115200);
  delay(1000); // stabilize serial (important in Wokwi)

  randomSeed(analogRead(0));

  Serial.println("timestamp,heart_rate,spo2,temperature,profile");
}

void loop() {
  // --- Simulate Sensor Readings with Noise ---
  float hr = base_hr + random(-hr_noise * 10, hr_noise * 10) / 10.0;
  float spo2 = base_spo2 + random(-spo2_noise * 10, spo2_noise * 10) / 10.0;
  float temp = base_temp + random(-temp_noise * 10, temp_noise * 10) / 10.0;

  // --- Clamp Values to Physical Limits ---
  hr = constrain(hr, 40, 200);
  spo2 = constrain(spo2, 70, 100);
  temp = constrain(temp, 34, 43);

  // --- Output CSV (Cloud-ready format) ---
  Serial.print(millis());
  Serial.print(",");
  Serial.print(hr, 1);
  Serial.print(",");
  Serial.print(spo2, 1);
  Serial.print(",");
  Serial.print(temp, 2);
  Serial.println(",healthy");

  delay(1000); // keep 1 reading/sec (real smartwatch behavior)
}