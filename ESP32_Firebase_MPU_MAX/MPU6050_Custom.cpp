#include "MPU6050_Custom.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
long _time_1, _time_2 = 0;
MPU6050Helper::MPU6050Helper(bool _DEBUG) : DEBUG(_DEBUG){
  // Constructor implementation remains unchanged
}
void MPU6050Helper::MPU_Init() {
    Wire.begin();
  
    status = !mpu.begin();
    if(DEBUG){
      Serial.print(F("[INFO] MPU6050 status: "));
      Serial.println(status);
    }
    if(!status){
      Serial.println("############");
      Serial.println("[ERROR] Can't See MPU6050");
    }
    if(DEBUG){
      Serial.println("[INFO] Calculating offsets, do not move MPU6050");
    }
    delay(1000);
    mpu.calcOffsets(true, true); // gyro and accelerometer
    if(DEBUG){
      Serial.println("[Success] Done!");
    }
}
void MPU6050Helper::MPU_Update() {
  mpu.update();
  acceleration_magnitude += sqrt(mpu.getAccX() * mpu.getAccX() + mpu.getAccY() * mpu.getAccY() + mpu.getAccZ() * mpu.getAccZ());
  ++sample_count;
  if(DEBUG && millis() - _time_1 > 1000){
    Serial.println("[INFO] MPU6050 [ Acceleration Magnitude ] = " + String(acceleration_magnitude / sample_count));
    // acceleration_magnitude = 0;
    _time_1 = millis();
  }
}
void MPU6050Helper::set_Essential_Tremor_treshold_Percentage(float _treshold){
  treshold = _treshold;
}
void MPU6050Helper::MPU_Detect_Essential_Tremor() {
  if(millis() - _time_2 > 100){
    _time_2 = millis();
    if (((acceleration_magnitude / sample_count) - 1) * 100.0 > treshold) {
      if(DEBUG){
        Serial.println("Tremor detected!");
      }
      Essential_Tremor = 1;
    }else{
      Essential_Tremor = 0;
    }
    acceleration_magnitude = 0;
    sample_count = 0;
  }
}