# EEE4113F-Project
Code repo for weighing subsystem and associated docs
code obtained and modified from https://github.com/bogde/HX711/tree/master and https://randomnerdtutorials.com/arduino-load-cell-hx711/ by Rui Santos

## Pre-requisites and setup
Must have any arduino board or compatible board that uses arduino IDE

Must have arduino IDE installed on PC

Must have the arduino HX711 libraries from [1] and [2] installed in library manager

Must have the HX711 amplifier or equivalent and a 4 wire load cell (any mass)

Instructions to setup the circuit can be found at [1] or [2]


## Calibrater program (Calibrater.ino)
Calibrates the load cell scale that is interfaced to an arduino by using a known weight to obtain the calibration factor of the scale. 

## Weighing program (Calibrated1.ino)
Uses the calibration factor calculated by the calibrater program (Calibrator.ino) to continously record the mass of an object on the load cell(scale), and outputs a single measurement and the average reading of 20 measurements  every 5 seconds to the serial monitor. This code was modified for our project by formatting the otutput to have timestamp information and weight information and output redirection was used to write to files. This program was used in the RFID module to only activate when a bird with a valid RFID lands on the scale.

## References
[1] Florita et al., “Arduino with load cell and HX711 amplifier (Digital Scale),” Random Nerd Tutorials, https://randomnerdtutorials.com/arduino-load-cell-hx711/ (accessed May 18, 2023). 

[2] I. Lukuk, “4-wire load cell (1/5/10/20/200kg) with HX711 and Arduino,” 4-Wire Load Cell (1/5/10/20/200kg) with HX711 and Arduino - Circuit Journal, https://circuitjournal.com/four-wire-load-cell-with-HX711 (accessed May 18, 2023). 
