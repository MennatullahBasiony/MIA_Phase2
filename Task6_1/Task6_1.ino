#include <Wire.h>

//define needed variables
#define MPU_ADDRESS 0x68
#define PWR_MGMT_1 0x6B
#define GYRO_CONFIG 0x1B
#define REGISTER_ADDRESS 0x47
#define LSB_Sensitivity 16.4

float GyroZ, GyroErrorZ, yaw;
float elapsedTime, currTime, prevTime;
int c = 0;

void setup() 
{
  Serial.begin(19200);
  MPU_init(); //to start MPU
  MPU_GyroConfig(); //configure the mpu gyroscope
  calc_MPU_error(); //calculate the error/offset
  delay(20);
}

void loop() 
{
  prevTime = currTime;
  currTime = millis();
  elapsedTime = (currTime - prevTime) / 1000; // calculating elapsed time in seconds

  GyroZ = MPU_reading() / LSB_Sensitivity;
  //adding error/offset
  GyroZ += GyroErrorZ;

  //calculating the yaw
  yaw = yaw + GyroZ * elapsedTime; 
  Serial.print("yaw: ");
  Serial.println(yaw);

}

void MPU_init()
{
  Wire.begin();
  Wire.beginTransmission(MPU_ADDRESS);    //Start communication with mpu6050
  Wire.write(PWR_MGMT_1);               //Communicate with register 6B
  Wire.write(0x00);               //Write 0 into 6B register (reset)
  Wire.endTransmission(true);     //end Transmission
}

void MPU_GyroConfig()
{
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(GYRO_CONFIG);
  Wire.write(0x18); // set full range = +- 2000 deg/sec
  Wire.endTransmission();
}

int16_t MPU_reading()
{
  int16_t data = 0;
  
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(REGISTER_ADDRESS);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDRESS, 2);   //read 2 bytes

  while(Wire.available()<2);  //wait untill receiving 2 bytes
  data = Wire.read() << 8 | Wire.read();

  return data;
}

void calc_MPU_error()
{
  while (c < 3000)
  {
    GyroZ = MPU_reading();
    
    GyroErrorZ += GyroZ / LSB_Sensitivity;

    c ++;
  }

  GyroErrorZ /= 3000;
  
  Serial.print("gyro error z: ");
  Serial.println(GyroErrorZ);
}
