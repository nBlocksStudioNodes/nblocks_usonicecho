# USonicEcho

<p align="center">
<img
src="img/01.PNG"
width = 400
/>
</p>

Ultrasonic distance sensor Node for the Parallax Ping
 
 *  Category: Sensor
 *  HAL: mbed
 *  Tested: with LPC1768
 *  Author: N. Chalikias

## Output data types
 *  uint32_t: Echo time in micro-seconds for coefficient =1, or divided by the coefficient parameter 

## Inputs / Outputs

 *  (Schematic pin 2) uint32_t: Echo time in micro-seconds
 *  (Schematic pin 1) Trigger Input

## Parameters:
  *  PinName: EchoPin: Pin to be used for the signal from/to the board
  *  uint32_t: coefficient: Value to divide the 2 ways echo time measured:
     * 1 for raw 2 ways travel value in us
     * 2 for one way travel in us
     * 58 for one way in centimeters
     * Any other value that suits a use case


## Example:
[Ticker]-->[USonicEcho]-->[StringFormat]-->[StringSerial]

