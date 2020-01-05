# ArduinoMotorSSR
Use Arduino Nano to control DC motor speed with SSR
255 steps

Tested with 25A Fotek

Connect SSR input to GND and PIN10
Increase speed button to GND and PIN3
Decrease speed button to GND and PIN4

Timer is set to 60s. After timeout motor stops. Any button will enable it from adjustable speed.

If you the same power supply to motor and Arduino.
Arduino should have i.e. regulated power supply between to get rid of voltage disturbances. 
