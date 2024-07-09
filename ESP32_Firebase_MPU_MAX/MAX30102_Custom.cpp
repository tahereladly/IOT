#include "MAX30102_Custom.h"

MAX30102Controller::MAX30102Controller() {}

MAX30102Controller::~MAX30102Controller() {}

void MAX30102Controller::configureMAX30100() {
    // Initialize sensor
    status = particleSensor.begin(Wire, I2C_SPEED_FAST);

    if(!status)
      return;

    particleSensor.setup(); // Configure sensor with default settings
    particleSensor.setPulseAmplitudeRed(0x0A); // Turn Red LED to low to indicate sensor is running
    particleSensor.setPulseAmplitudeGreen(0); // Turn off Green LED
}
long _time_4 = 0;
void MAX30102Controller::readRegister() {
    long irValue = particleSensor.getIR();

    if (checkForBeat(irValue) == true) {
        long delta = millis() - lastBeat;
        lastBeat = millis();

        beatsPerMinute = 60 / (delta / 1000.0);

        if (beatsPerMinute < 255 && beatsPerMinute > 20) {
            rates[rateSpot++] = (byte)beatsPerMinute;
            rateSpot %= RATE_SIZE;

            beatAvg = 0;
            for (byte x = 0 ; x < RATE_SIZE ; x++)
                beatAvg += rates[x];
            beatAvg /= RATE_SIZE;
        }
    }
    BPM = beatAvg;
    if (millis() - _time_4 > 1000){
      if(irValue >= 50000)
        Essential_Tremor = 1;
      else
        Essential_Tremor = 0;
    }
}
