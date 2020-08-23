# E36 Brake Force Display (BFD) (Not for road use)
Small arduino project to retrofit a BFD function (as known from E90) to the old E-Series. Please note that you will only use this function on closed tracks and not on road vehicles. In most countries it is illegal to modify safety equipment such as the circuit of the brake lights in road traffic.


## Idea
Modern vehicles indicate the force of braking via the brake lights. A two-stage approach is often followed: First, the brake lights illuminate normally and in the event of an emergency stop, the brake lights start flashing to indicate an emergency stop to the vehicle behind. It has been established, for example, in the E85 and E92 at BMW. To be able to retrofit this function, I wrote a script for the Arduino Uno and built a small circuit which allows to be built into the existing circuit.

## Installation & Fallback 
The module is designed that it can be integrated into the existing vehicle wiring. Since the Arduino needs less voltage than the on-board power supply, I use a step-down regulator to feed the Arduino. More about this in the Circuit section. 

![alt text](https://github.com/gobit0dic/e36_brake_force_display/blob/master/static/img/circuit_pretty.png?raw=true)

Must be connected: 
* Brake pedal switch (Blue-Red) - Please note some switches connecting to B- others to B+, depending on year and model. Please check yours first and modify the software settings! 
* 12V on-board voltage (Kl.R with Fuse)
* Brake lights (e.g. Black-Green (54L), Black-Grey(54M), Black-White(54R))

Nice to connect: 
* Relay to switch between LSZ signal to brake lights and Arduino signal to brake lights

Basically the board can be used with a potentiometer on the brake pedal, which detects the brake pedal position, or with an acceleration sensor. The advantage of the sensor is that nothing needs to be added to the pedal. You can also switch the BFD function on and off with a dip switch. The changes will be used after restart.

I used two fallback methods during design to ensure the brake light works: 
1. The original brake light switch is integrated in the design. This means that this switch has a higher priority and if e.g. the sensors of the Arduino do not detect brake pedal pressure, but the original switch reports one, the brake lights will still go on. In the other direction, the brake lights only come on if the original switch detects pressure, so there is no false positive/negative caused by the accelerometer/potentiometer.
2. The Arduino sends a signal on a pin when it is ready. This can be used to switch a relay. This way you can, for example, let the normal signal take the LSZ to the brake lights, so that you still have working brake lights if the Arduino fails. Only when the Arduino signals ready, a relay can switch to another circuit controlled by the Arduino. 

## Software Setup
At the beginning of the code you will find some setting options. Basically, you can define the threshold values from which braking or emergency braking is detected (pedal position and time). Furthermore you can define the blinking frequency per second and the distribution between ON and OFF times per blinking cycle. Of course you can also define the output pins if you have a different setup. Please let me know if you are missing any settings or you find any mistakes.

## Hardware Setup (Circuit)
I wanted to keep the hardware setup as simple as possible and in a form so that it could be placed on a board in the next version or even be used with a simple ATMEGA chip. 
Basically I only use a few pulldown resistors at the inputs, a few switches to realize the functions and a variable resistor (potentiometer or accelerometer). 
The brake lights are classic bulbs on the old cars, so I cannot control them directly via the Arduino. Therefore I decided to use a NPN transistor and a P-Mosfet to switch to the bulbs via the signal of the Arduino 12V.

![alt text](https://github.com/gobit0dic/e36_brake_force_display/blob/master/static/img/circuit.png?raw=true)

## Release Notes
* v0.1 - Initial Release (23.08.2020)

## Disclaimer
Please note that you will only use this function on closed tracks and not on road vehicles. In most countries it is illegal to modify safety equipment such as the circuit of the brake lights in road traffic. Please let me know if you are missing any settings or you find any mistakes.
