#include <Arduino.h>
#include "WiFi_Helper.h"
#include "Firebase_Helper.h"
#include "MPU6050_Custom.h"
#include "Vibrator_Controller.h"
#include "MAX30102_Custom.h"

const char* _SSID = "Bondok eladly";
const char* _PASSWORD = "Bondok1234";
const char* FIREBASE_ID = "hardware-project-d020c-default-rtdb.firebaseio.com";

WiFiHelper wifiHelper(_SSID, _PASSWORD, 1);
FirebaseHelper firebaseHelper(FIREBASE_ID, 1);
VibratorController vibratorController;
MAX30102Controller max30102Controller;
MPU6050Helper mpuHelper(1);


void setup() {
  Serial.begin(115200); 
  vibratorController.init();
  wifiHelper.wifiInit();
  mpuHelper.MPU_Init();
  mpuHelper.set_Essential_Tremor_treshold_Percentage(20);
  max30102Controller.configureMAX30100(); 

  // firebaseHelper.sendToFirebase("MALAK", "TAHER:4.0;");
}
bool Tremor_Detected = 0, MPU_Tremor = 0, MAX_Tremor = 0, vibrate = 0;
float Vibration = 0;
float BPM = 0;
void loop() {
  if(mpuHelper.status){
    mpuHelper.MPU_Update();
    mpuHelper.MPU_Detect_Essential_Tremor();
    if(mpuHelper.Essential_Tremor && !MPU_Tremor){
      MPU_Tremor = 1;

      firebaseHelper.sendToFirebase("Essential_Tremor", "MPU:1.0;");
    }else if(!mpuHelper.Essential_Tremor && MPU_Tremor){
      MPU_Tremor = 0;
      firebaseHelper.sendToFirebase("Essential_Tremor", "MPU:0.0;");
    }
  }

  if(max30102Controller.status){
    max30102Controller.readRegister();
    if(max30102Controller.Essential_Tremor && !MAX_Tremor){
      MAX_Tremor = 1;

      firebaseHelper.sendToFirebase("Essential_Tremor", "MAX:1.0;");
    }else if(!max30102Controller.Essential_Tremor && MAX_Tremor){
      MAX_Tremor = 0;
      firebaseHelper.sendToFirebase("Essential_Tremor", "MAX:0.0;");
    }
  }


  if((MPU_Tremor || MAX_Tremor) && !Tremor_Detected){
    Tremor_Detected = 1;
    vibratorController.pulseVibrators();
    firebaseHelper.sendToFirebase("Essential_Tremor", "DETECTED:1.0;");
  }else  if(!(MPU_Tremor || MAX_Tremor) && Tremor_Detected){
    Tremor_Detected = 0;
    vibratorController.closeAll();
    firebaseHelper.sendToFirebase("Essential_Tremor", "DETECTED:0.0;");
  }
  if(Vibration != ((mpuHelper.acceleration_magnitude / mpuHelper.sample_count) - 1)){
    Vibration = (mpuHelper.acceleration_magnitude / mpuHelper.sample_count) - 1;
    firebaseHelper.sendToFirebase("Drawing", "Vibration:" + String(Vibration)+";");
  }
  if(BPM != max30102Controller.BPM ){
    BPM = max30102Controller.BPM;
    firebaseHelper.sendToFirebase("Drawing", "BPM:" + String(BPM)+";");
  }
}
