#ifndef MPU6050_CUSTOM_H
#define MPU6050_CUSTOM_H

#include <Wire.h>


class MPU6050Helper {
public:
  MPU6050Helper(bool _DEBUG);
  void MPU_Init();
  void MPU_Update();
  void set_Essential_Tremor_treshold_Percentage(float _treshold);
  void MPU_Detect_Essential_Tremor();
  double acceleration_magnitude;
  bool status;
  bool Essential_Tremor;
  int sample_count;
private:
  float treshold;
  bool DEBUG;
};

#endif
