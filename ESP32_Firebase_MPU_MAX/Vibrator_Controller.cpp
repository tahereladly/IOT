#include "Vibrator_Controller.h"
#include <Arduino.h>
long _time_3 = 0;
bool opened = 0;
VibratorController::VibratorController() {
    // Constructor
}

VibratorController::~VibratorController() {
    // Destructor
}

void VibratorController::init() {
    for (int i = 0; i < numVibrators; i++) {
        pinMode(vibratorPins[i], OUTPUT);
    }
}

void VibratorController::openAll() {
    for (int i = 0; i < numVibrators; i++) {
        digitalWrite(vibratorPins[i], HIGH);
    }
}

void VibratorController::closeAll() {
    for (int i = 0; i < numVibrators; i++) {
        digitalWrite(vibratorPins[i], LOW);
    }
}

void VibratorController::pulseVibrators() {
    if(!opened || millis() - _time_3 > 1000){
      openAll(); // Open all vibrators
      opened = 1;
      _time_3 = millis();
    }
    if(millis() - _time_3 > 20000){
      closeAll(); // Close all vibrators
      opened = 0;
      _time_3 = millis();
    }
}
