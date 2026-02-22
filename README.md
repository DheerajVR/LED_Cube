# LED Cube
## Description
This project aims to make and control a 4x4x4 LED cube using Arduino UNO. On completion, the aim was further modified to using a joystick module to control the LEDs and using a sound sensor to make a sound visualizer.


## Table of Contents
  1. [Hardware Materials](#hardware)
  2. [Aim](#aim)
  3. [Circuit Diagram](#circuit-diagram)
  4. [Contributors](#contributors)


## [Hardware Materials](#hardware)
- **Arduino UNO** - As the microcontroller
- **74HC595 Shift registers** - For shifting out the data into the cube
- **64 LEDs** - For the cube itself
- **4 NPN Transistors (BC548)** - For handling the high current
- **Resistors** - For the LEDs
- **HW-504 Joystick Module** - For controling the individual LEDs
- **2 Push Buttons** - Aiding the joystick
- **SY-M213 Sound Sensor** - For the sound visualizer
- **Others** - Jumper wires, breadboard, perfboard, etc


## [Aim](#aim)
  Here we have daisy-chained two shift registers, having a common latch pin and clock pin for both the registers, writing data into the data pin of the first shift register and connecting the pin 9 to the data pin of the second register. The LEDs are soldered in a way that for each horizontal layer, all the LEDs have a common ground and the anode of each vertical column of LEDs is connected to the 16 output pins (2 x 8 pins) of the shift registers.
  
  The basic idea is that you write a 16 bit value (or two 8 bit value) to the shift registers, and these 16 bits corresponds to the state of each LED in a layer. Then you multiplex each layer fast enough so that the naked eye perceive it as a solid object.

  The Output Enable pin (OE) and Master Reset pin (MR) of both the shift registers should be connected to ground and Vcc respectively for normal operation.
  The shift register should be powered using the Vcc and Ground pin (that is pin 16 and 8 respectively) from an external power source of 5 volts.

  Proper care is taken with the amount of power used to run the cube as 64 LEDs draw a huge amount of current. Resistors should be used to avoid over heating or damaging the components. Also transistors are used to connect each layer to ground as the Arduino board can't handle that much current. Emitter of the transistor is conneccted to the ground and collector iss connected to the cathode of a layer, then base is connected to Arduino (protect base with a resistor).


## [Circuit Diagram](#circuit-diagram)
   ### 74HC595 Shift Register Pinout
   <div align = "center">
       <img width="366" height="300" alt="image" src="https://github.com/user-attachments/assets/b65285ea-6ece-4eee-944e-27efe87b49a2">
       <p><em>74HC595 Shift Register</em></p>
   </div>

   ### Circuit Diagram for Shift Register
   <div align = "center">
       <img width="412" height="252" alt="image" src="https://github.com/user-attachments/assets/4b576fb9-4777-47fd-b5b9-641f91cb811d" />
       <p><em>Daisy-chained shift registers</em></p>
   </div>

## [Contributors](#contributors) :
   - **[Ayush R Mishra](https://github.com/aayayayu)**
   - **[Patel Archana Jashvantbhai](https://github.com/archanapatel1508)**
   - **[Harshal Karanje](https://github.com/HARSHAL-KARANJE)**
   - **[Dheeraj V R](https://github.com/DheerajVR)**

