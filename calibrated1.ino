/**
 * Complete project details at https://RandomNerdTutorials.com/arduino-load-cell-hx711/
 *
 * HX711 library for Arduino - example file
 * https://github.com/bogde/HX711
 *
 * MIT License
 * (c) 2018 Bogdan Necula
 *
**/
//modified by Group 3 @ UCT EEE4113F 2023 design team
//Bina Mukyamba
//19/05/2023

#include <Arduino.h>
#include "HX711.h"
#include <SD.h>
#include <EEPROM.h>
#include <TimeLib.h>
//uncomment if writing to an SD card
//const int chipSelect = 10; // Change this to match your SD card module's chip select pin

//uncomment if writing to EEPROM
int address=0;

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 7;
const int LOADCELL_SCK_PIN = 4;

HX711 scale;

//gloabal vars
float ThresholdMin = 200; //only record and print weight if valid sized bird between 200 and 800 grams
float ThresholdMax = 800;
void Send2file(String Filename);
void Send2EEP(int Address); //Send data to EEPROM, then externally send to file via eeprom, maybe another script


void setup() {
  Serial.begin(57600); // uncomment if using an SD-card on the arduino set it up
  // if (!SD.begin(chipSelect)) {
  //  Serial.println("SD card initialization failed!");
 //   return;
 // }

 // Serial.println("SD card initialized successfully!");
  setTime(0, 0, 0, 1, 1, 2023); // Set the time to desired day 00:00:00 on January 1, 2023
  Serial.println("HX711 Demo");
  Serial.println("Initializing the scale");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());      // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
            // by the SCALE parameter (not set yet)
            
  scale.set_scale(-1167.975);
  //scale.set_scale(-471.497);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
            // by the SCALE parameter set with set_scale

  Serial.println("Readings:");
  
}

void Send2EEP(int Address){

 String data[50]; //array of timed weight data
 for (int i = 0; i < 50; i++){ 
   data[i] = "mass: "+String(scale.get_units(10))+ "time: "+day()+"-"+month()+"-"+year()+"--"+hour()+":"+minute()+":"+second();

 }
 EEPROM.write(Address,data);
 //float received[50] = EEPROM.read(Address); //to check if it worked


}

void Send2file(String Filename){
    File myfile;
    myfile = SD.open(Filename, FILE_WRITE);

  if (!myfile) {
    Serial.println("Error opening data file!");
    return;
  }

  Serial.println("Data file opened successfully!"); //file reader works writes 50 values to csv file
  for (int i = 0; i < 50; i++) { //number of items to store in file
    // Write each value to csv file
    myfile.print(scale.get_units(10));

    // Add comma between values (except for the last value)
    if (i < 50 - 1) {
      myfile.print(",");
    }
  }
  return;

  // Start a new line in the CSV file
  myfile.println();


  // Close the file
  myfile.close();
}

  


void loop() {

  if (scale.get_units()>ThresholdMin && scale.get_units()<ThresholdMax){
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 5);
  //Send2file("weightdata.csv"); //comment depending on how to store data
  Send2EEP(address);
  }

  else{
  Serial.print("invalid weight, won't record");} //for debug purposes, in actual implementation it would do nothing if weight is wrong

  delay(5000);}//repeat every 5 seconds
  