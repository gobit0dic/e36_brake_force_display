# E36 Brake Force Display (BFD) (Not for road use)
Small arduino project to retrofit a BFD function (as known from E90) to the old E-Series. Please note that you will only use this function on closed tracks and not on road vehicles. In most countries it is illegal to modify safety equipment such as the circuit of the brake lights in road traffic.


## Idea
Modern vehicles indicate the force of braking via the brake lights. A two-stage approach is often followed: First, the brake lights illuminate normally and in the event of an emergency stop, the brake lights start flashing to indicate an emergency stop to the vehicle behind. It has been established, for example, in the E85 and E92 at BMW. To be able to retrofit this function, I wrote a script for the Arduino Uno and built a small circuit which allows to be built into the existing circuit.

## Installation & Fallback 
The module is designed that it can be integrated into the existing vehicle wiring. Since the Arduino needs less voltage than the on-board power supply, I use a step-down regulator to feed the Arduino. More about this in the Circuit section. 

Must be connected: 
* Brake pedal switch
* Potentiometer / Accelerometer
* 12V on-board voltage
* Brake lights

Basically the board can be used with a potentiometer on the brake pedal, which detects the brake pedal position, or with an acceleration sensor. The advantage of the sensor is that nothing needs to be added to the pedal. You can also switch the BFD function on and off with a dip switch. The changes will be used after restart.

I used two fallback methods during design to ensure the brake light works: 
1. The original brake light switch is integrated in the design. This means that this switch has a higher priority and if e.g. the sensors of the Arduino do not detect brake pedal pressure, but the original switch reports one, the brake lights will still go on. In the other direction, the brake lights only come on if the original switch detects pressure, so there is no false positive/negative caused by the accelerometer/potentiometer.
2. The Arduino sends a signal on a pin when it is ready. This can be used to switch a relay. This way you can, for example, let the normal signal take the LSZ to the brake lights, so that you still have working brake lights if the Arduino fails. Only when the Arduino signals ready, a relay can switch to another circuit controlled by the Arduino. 

## Software Setup
At the beginning of the code you will find some setting options. Basically, you can define the threshold values from which braking or emergency braking is detected (pedal position and time). Furthermore you can define the blinking frequency per second and the distribution between ON and OFF times per blinking cycle. Of course you can also define the output pins if you have a different setup. Please let me know if you are missing any settings or you find any mistakes.

## Hardware Setup (Circuit)

## Release Notes
* 0.1 - Initial Release Pre-Alpha (23.08.2020)

## Disclaimer
