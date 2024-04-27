#include <msp430.h>
#include "stdint.h"
#include "I2C.h"
#include "MPU6050.h"
#include <stdlib.h>
#include <stdio.h>

short x_accel; // accelerometer x value
short y_accel; // accelerometer y value
short z_accel; // accelerometer z value
short x_calib; // benchmark accelerometer x value
short y_calib; // benchmark accelerometer y value
short z_calib; // benchmark accelerometer z value
int seconds_count = 0; // count of distracted seconds
long int count = 0; // count of distracted cycles
int state = 0; // State = 0 if not started yet

short absolute(num){ // Functio to return the absolute value of a number
    if(num<0){
        return -num;
    }else{
        return num;
    }
}

void buttons_init() { // Initializing button (Connected to P.13)
    P1SEL &= ~(BIT3); // Setting P1.3 as GPIO
    P1SEL2 &= ~(BIT3); // Setting P1.3 as GPIO

    P1DIR &= ~(BIT3); // Setting P1.3 as input
    P1REN &= ~(BIT3); // Configuring P1.3 pull up/down resistor
    P1OUT |= BIT3; // Configuring P1.3 pull up/down resistor

    P1IES &= ~(BIT3); // Enabling P1.3 interrupt
    P1IFG &= ~(BIT3); // Clearing  P1.3 interrupt flag
    P1IE |= BIT3; // Setting from low to high transition
}

int main()
{

    WDTCTL = WDTHOLD | WDTPW; // Turning off watchdog timer
    DCOCTL = CALDCO_16MHZ; 
    BCSCTL1 = CALBC1_16MHZ;
    BCSCTL2 = DIVS_1;  

    // P1.0 (Green LED) used for status checking
    P1DIR |= BIT0 + BIT1 + BIT4; // Setting P1.0,P1.1 and P1.4 as output             
    P1OUT &= ~(BIT0 + BIT1 + BIT4); // Clearing output

    P2SEL &= ~(BIT0 + BIT1 + BIT2 + BIT4 + BIT5 + BIT6 + BIT7); // Setting LCD pins as GPIO
    P2SEL2 &= ~(BIT0 + BIT1 + BIT2 + BIT4 + BIT5 + BIT6 + BIT7); // Setting LCD pins as GPIO
    P2REN &= ~(BIT0 + BIT1 + BIT2 + BIT4 + BIT5 + BIT6 + BIT7); // Configuring LCD pins pull up/down resistor

    lcd_init(); // Initializing LCD
    display_starting_message(); // Displaying start message
    i2c_init(); // Initializing I2C communication
    mpu_init(); // Initializing MPU-6050 sensor
    buttons_init(); // Initializing buttons

    _enable_interrupts(); // Enabling interrupts
   // P1OUT |= BIT0;

    while(1){
        if(state == 2){ // State == 2 means that distraction is being measured
                    z_accel = get_z_accel(); // Getting the current z accelerometer value

                    bool distracted_1 =  (absolute(z_accel - z_calib) > 2000); // Checking threshold for first level of vibration
                    bool distracted_2 =  (absolute(z_accel - z_calib) > 3500); // Checking threshold for second level of vibration

                    if(distracted_2){ // If current tilt above threshold for second level fo vibration
                        P1OUT |= BIT1 + BIT4; // Turn on both levels of motors
                        while(distracted_1){ // While distracted
                            if(!distracted_2){ // If not in level 2 anymore
                                P1OUT &= ~BIT4; // Then turn off second level of motors
                            }
                                         count += 1; // Increment counter for iterations
                                         if(count > seconds_count*130000){
                                             seconds_count += 1; // Increment seconds counter
                                             if(seconds_count%10 == 0){ //Each ten seconds the LCD updates
                                                 lcd_init(); // Re-initializing LCD
                                                 display_time_distracted(seconds_count); // Displaying current amount of distracted time
                                                 break;
                                             }
                                         }
                                   }
                    } else if(distracted_1){
                        P1OUT &= ~BIT4; // If distracted only at level 1, then turn on only first level of motors
                        while(distracted_1){ 
                              count += 1; // Incrementing counter for iterations
                              if(distracted_2){
                                break; // If went up to next level of distraction, then break so it goes to the loop above for level 2
                              }
                              if(count > seconds_count*130000){
                                   seconds_count += 1; // Increment seconds counter
                                   if(seconds_count%10 == 0){
                                       lcd_init(); // Re-initializing LCD
                                       display_time_distracted(seconds_count); // Displaying current amount of distracted time
                                       break;
                                   }
                              }
                        }
                  }else{
                      P1OUT &= ~(BIT1 + BIT4); // If not distracted, then turn off both level of motors
                  }
        }else{
            seconds_count = 0; // If state != 2, then distraction is not measured and seconds_count and count should be 0
            count = 0;
        }
    }
    return 0;
}

// Button 1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT1_VECTOR
__interrupt void button1(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT1_VECTOR))) button (void)
#else
#error Compiler not supported!
#endif
{
    if(state == 0){ // Initialized state
        lcd_init();
        display_calibration_message(); // Display calibration message
        state = 1; // Change to calibration state
    }
    else if(state == 1){ // Calibration state
        z_calib = get_z_accel(); // Get benchmark z acceleration value
        lcd_init();
        display_time_distracted(seconds_count); // Start displaying distracted time 
        state = 2; // Change to distraction measuring state
    }else if(state == 2){ // Distraction measuring state
        lcd_init();
        display_end_message(seconds_count); // Display message showing total amount of distracted time during state 2
        state = 3; // Change to a state that waits until pressing to start again
        seconds_count = 0;
        count = 0;
    }else{
        lcd_init();
        display_starting_message(); // Display starting message again
        state=0; // Change to starting state
        seconds_count = 0;
        count = 0;
    }

    P1IFG &= ~BIT3; // Clear interrupt flag
}

