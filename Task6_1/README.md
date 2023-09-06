# Using MPU-6050 to Calculate Yaw

### Define Macros:
    . MPU_ADDRESS 0x68
    . PWR_MGMT_1 0x6B
    . GYRO_CONFIG 0x1B
    . REGISTER_ADDRESS 0x47
    . LSB_Sensitivity 16.4

### MPU_init Function:

    . Parameters: void
    . Return: void
    . Function: It starts the communication with MPU using I2C

### MPU_GyroConfig Function:

    . Parameters: void
    . Return: void
    . Function: Set full range of Gyroscope to 2000 deg/sec

### MPU_reading Function:

    . Parameters: void
    . Return: int16_t (16 bit)
    . Function: read 2 bytes from sensor starting from REGISTER_ADDRESS (which is the address of GYRO_ZOUT_H)

### calc_MPU_error Function:

    . Parameters: void
    . Return: void
    . Function: calculate the error/offset in reading Gyroz

### Setup Function:

    . Function: 
        . Start Serial Communication
        . Call MPU_init Function
        . Call MPU_GyroConfig Function
        . Call calc_MPU_error Function

### Loop Function:

    . Function:
        . Calculated Elapsed time
        . Get MPU reading
        . Calculate Yaw and print it

