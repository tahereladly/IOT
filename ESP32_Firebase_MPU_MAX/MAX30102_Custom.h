#ifndef MAX30102_CUSTOM_H
#define MAX30102_CUSTOM_H

#include <Wire.h>
#include <MAX30105.h>
#include <heartRate.h>

class MAX30102Controller {
public:
    MAX30102Controller();
    ~MAX30102Controller();
    void configureMAX30100();
    void readRegister();
    bool status;
    bool Essential_Tremor;
    float BPM;
private:
    const byte RATE_SIZE = 4; // Increase this for more averaging. 4 is good.
    byte rates[4]; // Array of heart rates
    byte rateSpot = 0;
    long lastBeat = 0; // Time at which the last beat occurred
    float beatsPerMinute;
    int beatAvg;
    MAX30105 particleSensor;
    int x = 3;
};

#endif
