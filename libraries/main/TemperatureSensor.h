#ifndef __TEMPERATURE_SENSOR_H__
#define __TEMPERATURE_SENSOR_H__

#include <Arduino.h>

#include "DataSource.h"

typedef struct {
    float temp = 0; // temperature (C)
} temp_state_t;

/*
 * TemperatureSensor class keeps track of the robot's temperature,
 * based on the thermistor circuit
 */
class TemperatureSensor : public DataSource
{
public:
  TemperatureSensor(void);

  // init
  void init(void);

  // State Access
  temp_state_t state;

  void updateState(int temperature_signal);
  String printState(void);

  // from DataSource
  size_t writeDataBytes(unsigned char * buffer, size_t idx);

  int lastExecutionTime = -1;

private:
  // set pressure sensor calibration slope and incercept below
  // const float R0 = 100000;
  // const float B = 4250;
  // const float T0 = 298.15;

  const float A1 = -0.002043;
  const float vB1 = 0.002806;
  const float C1 = -0.0005099;
  const float D1 = 0.00003378;
  
  const float depthCal_slope = -1.1468;
  const float depthCal_intercept = 3.2988;

};

#endif
