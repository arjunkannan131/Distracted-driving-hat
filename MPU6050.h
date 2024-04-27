

#ifndef MPU6050_H_
#define MPU6050_H_

#include <msp430.h>
#include <stdint.h>

void mpu_init(void);
short get_x_accel(void); // Function to get accelerometer x value
short get_y_accel(void); // Function to get accelerometer y value
short get_z_accel(void); // Function to get accelerometer z value


#endif /* MPU6050_H_ */
