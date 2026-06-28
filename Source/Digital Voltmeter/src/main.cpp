#include <Arduino.h>
#include "HT16K33.h"
#include <Wire.h>
#include <math.h>
#define INPUT_VOLTAGE A0
#define REFFERENDCE_VOLTAGE 5
#define DIVISION_FACTOR 4
HT16K33 display(0X70);
float filtered_voltage = 0;

void setup() {
  Wire.begin();
  display.begin();
  display.setBrightness(9);
}

void loop() {
  long sum = 0;
  for(int i=0; i<50; i++){
    int ADC_value = analogRead(INPUT_VOLTAGE);
    sum += ADC_value;
  }
  float average_ADC_value = sum / 50.0;
  float real_voltage = (float)average_ADC_value / 1023.0 * REFFERENDCE_VOLTAGE * DIVISION_FACTOR;
  filtered_voltage = 0.1 * real_voltage + 0.9 * filtered_voltage;
  display.displayFixedPoint2(filtered_voltage);
}
