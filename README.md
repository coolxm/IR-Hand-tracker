This project was adapted from a circuit diagram from https://www.instructables.com/IR-Proximity-Sensor-1/  
Using IR LEDS and IR Photodiodes it is possible to make a proximity sensor (and even a distance sensor with some more coding)  
The array to assign the LEDs to each other felt like a good idea but is very slow in Arduino in hindsight  
The size of the sensor array is theoretically only limited to the size of your Arduino  
This old version of the code uses bitwise operators to make a bit vector of the array, this is because I wanted to reuse an FSM I had used in an older line follower project, however since C does not utilize chars the same as VHDL does bivectors this failed and the newer version of the code will be uploaded shortly.  


## Possible improvements
This circuit could probably be rebuilt for cheaper using op amps and maybe 555 timers for the motor PWM but this felt easier  
Using a transistor to turn on and off the LEDs makes them able to calibrate to ambient IR light and be more precise due to being able to set a lower threshold, however, I am happy with the result. Pulsing the LEDs too fast will also make capacitive/PWM effects come into play and the lights will be less bright, as such, the pulse width should be long but then the refresh rate cannot be fast  
