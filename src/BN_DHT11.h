#ifndef BN_DHT11_H
#define BN_DHT11_H

#include <Arduino.h>
#include <stdint.h>

class BN_DHT11
{
public:
  BN_DHT11(uint8_t pin);
  void begin(void);
  float readTemperature(bool S = false);
  float readHumidity(void);

private:
  uint8_t _pin;
  uint32_t _lastreadtime;
  float _lasthumidity, _lasttemperature;
  uint8_t data[5];
  bool read(bool force = false);
};

#endif