#include "TemperatureSensor.h"
#include <math.h>
#include "Printer.h"
extern Printer printer;

TemperatureSensor::TemperatureSensor(void)
  : DataSource("temp","float") // from DataSource
{}

void TemperatureSensor::init(void) {
  state.temp = 0;
}

void TemperatureSensor::updateState(int temp_signal) {
  // get z (depth)
  float temp_voltage = (double)temp_signal;
  temp_voltage *= (3.3/1023);  // convert from Teensy units to Volts
  float divider_voltage = (9.46 - temp_voltage) / 3.92;
  float thermistor_R = 500000 / divider_voltage - 100000;
  float temp_inverse = 1/T0 - log(R0)/B + log(thermistor_R) / B;
  state.temp = 1/temp_inverse - 273.15; // convert from Volts to celcius [deg C]

  // uncomment the following print statement to calibrate your pressure sensor with the Teensy using the Serial Monitor
  String calibrationMessage = "Temperature Sensor Voltage: " + String(temp_voltage);
  printer.printMessage(calibrationMessage,20);
}

String TemperatureSensor::printState(void) {
  String currentState = "";
  int decimals = 2;
  currentState += "Temperature: temp: ";
  currentState += String(state.temp,decimals);
  currentState += "[deg C]";
  return currentState;
}

size_t TemperatureSensor::writeDataBytes(unsigned char * buffer, size_t idx) {
    float * data_slot = (float *) &buffer[idx];
    data_slot[0] = state.temp;
    return idx + sizeof(float);
}
