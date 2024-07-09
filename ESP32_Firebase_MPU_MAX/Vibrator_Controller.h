#ifndef VIBRATOR_CONTROLLER_H
#define VIBRATOR_CONTROLLER_H

class VibratorController {
public:
    VibratorController();
    ~VibratorController();
    void init(); // Initialize the vibrators
    void openAll(); // Open all vibrators
    void closeAll(); // Close all vibrators
    void pulseVibrators(); // Open for 5 seconds and then close

private:
    const int numVibrators = 10; // Number of vibrators
    // int vibratorPins[10] = {12, 13, 14, 25, 26, 27, 32, 33, 34, 35}; // Example pin numbers
    int vibratorPins[10] = {12, 13, 14, 25, 26, 27, 32, 33, 33, 33}; // Example pin numbers
};

#endif
