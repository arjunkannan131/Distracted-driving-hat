# Distracted-driving-hat
ELEC 327 Final Project - Distracted driving hat. 

Group 2 - Arjun Kannan, Caio Skornicki, Liam Waite, and Joshua Williams. 

The shareable link to our video that we uploaded to the Box folder:

Report Tasks:
 - (Finshed?) Block Diagram
 - (Finshed?) Code Architecture
 - (Finshed?) Hardware Design

References:
 - User's Guide for the MSP430G2553 LaunchPad™ Development Kit

Hardware Parts List: 
 - Component Name (Quantity)
 1. MSP430G2553 Launchpad (1)
 2. MPU6050 Sensor (1)
 3. FIT0774 Vibration Motors (12)
 4. HD44780 LCD (1)
 5. 1 kΩ Resistors (2)
 6. Standard Issue Breadboards (2)

Hardware Design:
 - The hardware setup for the project divides into 4 distinct "islands" or electronic component groupings:
   a. Island 1 --> Launchpad
   b. Island 2 --> LCD (plus potentiometer)
   c. Island 3 --> Intermediary Nodes
   d. Island 4 --> Sensor

Launchpad:
  Note: "a --> b" is equivalent to "a is directly connected to b by a physical wire"
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
  - The LCD is powered by a 5V power supply and is set to 4-bit mode such that only D4-D7 receive the most significant information regarding the bit representation of the incoming message.
b. Sensor


