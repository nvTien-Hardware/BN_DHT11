#include "BN_DHT11.h"

BN_DHT11::BN_DHT11(uint8_t pin)
{
    _pin = pin;
    _lastreadtime = millis() - 2000;
}

void BN_DHT11::begin(void)
{
    pinMode(_pin, INPUT_PULLUP);
}

float BN_DHT11::readHumidity(void)
{
    if (read())
        return _lasthumidity;
    return NAN;
}

float BN_DHT11::readTemperature(bool S)
{
    if (read())
        return _lasttemperature;
    return NAN;
}

bool BN_DHT11::read(bool force)
{
    uint32_t currenttime = millis();
    if (!force && ((currenttime - _lastreadtime) < 2000))
        return true;
    _lastreadtime = currenttime;

    _lasthumidity = _lasttemperature = NAN;

    uint8_t laststate = HIGH;
    uint32_t counter = 0;
    uint8_t j = 0, i;

    data[0] = data[1] = data[2] = data[3] = data[4] = 0;

    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    delay(20);
    digitalWrite(_pin, HIGH);
    delayMicroseconds(40);
    pinMode(_pin, INPUT_PULLUP);

    for (i = 0; i < 85; i++)
    {
        counter = 0;
        while (digitalRead(_pin) == laststate)
        {
            counter++;
            delayMicroseconds(1);
            if (counter == 100)
                break;
        }
        laststate = digitalRead(_pin);
        if (counter == 100)
            break;

        if ((i >= 4) && (i % 2 == 0))
        {
            data[j / 8] <<= 1;
            if (counter > 30)
                data[j / 8] |= 1;
            j++;
        }
    }

    if ((j >= 40) && (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)))
    {
        _lasthumidity = data[0];
        _lasttemperature = data[2];
        return true;
    }
    return false;
}