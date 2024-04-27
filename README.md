# Distracted-driving-hat
ELEC 327 Final Project - Distracted driving hat. 

Group 2 - Arjun Kannan, Caio Skornicki, Liam Waite, and Joshua Williams. 

The shareable link to our video that we uploaded to the Box folder: https://rice.box.com/s/g2vxw5zba0gppa39t4a6o9qrpegb65ov

References:
 - User's Guide for the MSP430G2553 LaunchPad™ Development Kit

Hardware Parts List: 
 - Component Name (Quantity)
 1. MSP430G2553 Launchpad (1)
 2. MPU6050 Sensor (1)
 3. FIT0774 Vibration Motors (12) - Only 4 being used
 4. HD44780 LCD (1)
 5. 1 kΩ Resistors (2)
 6. Standard Issue Breadboards (2)
    a. "Sensor's Breadboard" or "SB" <--> Breadboard with smallest dimesions.
    b. "LCD's Breadboard" or "LB" <--> Breadboard with largest dimesions.



Hardware Design:
 - The hardware setup for the project divides into 4 distinct "islands" or electronic component groupings:
   a. Island 1 --> Launchpad
   b. Island 2 --> LCD (plus potentiometer)
   c. Island 3 --> Intermediary Nodes
   d. Island 4 --> Sensor and Motors

Launchpad:
  Note: "a --> b" or "a <-- b" is equivalent to "a is directly connected to b by a physical wire".
  Note: All references to a port labeled "GND" are describing distinct "GND" or ground ports on the launchpad (with the exception of one "GND" port on the sensor).
  Note: All references to a port labeled "5V" are describing distinct "5V" or 5-Volt power supply ports on the launchpad.
 - Ports Utilized:
 Section: 20-Pin BoosterPack Plug-In Module Connector
  1. 5V
  2. GND (2 distinct "GND" ports were used in addition to least 2 additional ones outside of this section)
  3. Port 1 Pins: 1,2,3,6 and 7
  4. Port 2 Pins: 0,1,2,3,4,5,6,7
  5. PWM

- Connections:
  Note: "NC" is equivalent to "the following port(s)/pin(s) are isolated."
  Note: " a -- b // c --> d" is equivalent to "the path between a & b is separate from the path between c & d".
a. LCD 
  1. "VDD" Port --> 5V (of Launchpad)
  2. "VSS" Port --> GND (of Launchpad)
  3. "V0" Port --> Trimpot Contact (Leftmost) // Trimpot Contact (Middle) --> GND (of Launchpad)
  5. "RS" Port --> P2.0
  6. "RW" Port --> P2.1
  7. "E" --> P2.2
  8. "D4" Port --> P2.4
  9. "D5" Port --> P2.5
  10. "D6" Port --> P2.6
  11. "D7" Port --> P2.7
  12. "A" --> 3V3 (of Launchpad)
  13. "K" --> GND (of Launchpad)
  14. NC: D0,D1,D2,D3
  - The LCD is powered by a 5V power supply and is set to 4-bit mode such that only D4-D7 receive the most significant information regarding the bit representation of the incoming message. ;;
b. Sensor
  1. "GND" Port --> SB's Negative Power Rail  // SB's Negative Power Rail --> "GND" Port (of Launchpad)
  2. "VCC" Port --> SB's Positive Power Rail // SB's Positive Power Rail --> 5V (of Launchpad)
  3. "SCL" Port --> 1st end of 1st 1kΩ Resistor <-- P1.6 // 2nd end of 1st 1kΩ Resistor --> SB's Positive Power Rail
  4. "SDA" Port --> 1st end of 2nd 1kΩ Resistor <-- P1.6 // 2nd end of 2nd 1kΩ Resistor --> SB's Positive Power Rail
  5. NC: XDA,XCL,ADO,INT
  - The sensor is powered by a 5V power supply. It utilizes the I2C communication protocol. Given that the sesnosr's internal pull-up resistors alone were unable to fully inerface with the project's other electronic components, the team found it imperative to connect the "SDA" and "SCL" ports of the sensor to additional pull-up resistors.
  - Due to the limited length of the wires available, several Male-to-Female wires were connected end-to-end in order to create a path between the sensor's ports and other ports on relevant electronic components.
c. Button
  1. "1st Side of Push Button" --> LB's Negative Power Rail // LB's Negative Power Rail --> "GND" Port (of Launchpad)
  2. "2nd Side of Push Button" --> P1.3
d. Motors
  - There are two level of motors that are turned on depending on the level of vibration required by level of head tilt
  - Two motors are connected to ground and P1.4
  - Two motors are connected to ground and P1.1

Schematic of hardware design:

![ELEC327_Final_Block_Diagram](https://github.com/arjunkannan131/Distracted-driving-hat/assets/143037412/d6ba68f7-16ad-4c56-91c8-846528c64a84)
