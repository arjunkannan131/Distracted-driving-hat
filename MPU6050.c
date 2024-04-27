
#include "MPU6050.h"

short x_accel;
short y_accel;
short z_accel;

short get_x_accel(void)
{
    unsigned char ACCEL_XOUT_H; 
    unsigned char ACCEL_XOUT_L;

    i2c_read_addr8_data8(0x3B, &ACCEL_XOUT_H); // Reading higher register for accelerometer x value

    i2c_read_addr8_data8(0x3C, &ACCEL_XOUT_L); // Reading higher register for accelerometer x value

    x_accel = (ACCEL_XOUT_H << 8) + ACCEL_XOUT_L; // Calculating accelerometer x value

    return x_accel;
}


short get_y_accel(void){
    unsigned char ACCEL_YOUT_H;
    unsigned char ACCEL_YOUT_L;
    unsigned char reg_data16;

    i2c_read_addr8_data8(0x3D, &ACCEL_YOUT_H); // Reading higher register for accelerometer y value

    i2c_read_addr8_data8(0x3E, &ACCEL_YOUT_L); // Reading higher register for accelerometer y value

    y_accel = (ACCEL_YOUT_H << 8) + ACCEL_YOUT_L; // Calculating accelerometer y value

    return y_accel;
}

short get_z_accel(void){
    unsigned char ACCEL_ZOUT_H;
    unsigned char ACCEL_ZOUT_L;
    unsigned char reg_data16;

    i2c_read_addr8_data8(0x3F, &ACCEL_ZOUT_H); // Reading higher register for accelerometer z value

    i2c_read_addr8_data8(0x40, &ACCEL_ZOUT_L); // Reading higher register for accelerometer z value

    z_accel = (ACCEL_ZOUT_H << 8) + ACCEL_ZOUT_L; // Calculating accelerometer y value

    return z_accel;
}

void mpu_init(void)
{
    i2c_write_addr8_data8(0x6B,0x80);       // reset mpu
    __delay_cycles(1000);
    i2c_write_addr8_data8(0x6B,0x00);       // wake up mpu

    i2c_write_addr8_data8(0x68,0x07);       // reset signal paths
    __delay_cycles(1000);
    i2c_write_addr8_data8(0x6A,0x00);       // set i2c mode and disable fifo
    i2c_write_addr8_data8(0x6B,0x00);       // set clock source Internal 8MHz oscillator
    i2c_write_addr8_data8(0x19,0x07);       // set clock divider as 8
    i2c_write_addr8_data8(0x1A,0x00);       // set DLP 260Hz
    i2c_write_addr8_data8(0x1B,0x00);       // set Gyroscope Config 250 d/s
    i2c_write_addr8_data8(0x1C,0x08);       // set Accelerometer Config 2g
}
