
#include <Arduino.h>
#include "HX711.h"
#include <EEPROM.h>
#include <TimeLib.h>
int address=0; //EEPROM addr
float ThresholdMin = 200; //only record and print weight if valid sized bird between 200 and 800 grams
float ThresholdMax = 800;
//float Weights[50]; //array of weights to simulate reading from scale
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setTime(0, 0, 0, 1, 1, 2023); //using default for demo puporses
  //for (int j=0; j<10;j++){
  //  Weights[j]=float(rand(0,1000)); //array of random weights as if scale read them
 // }

 String data[10]; //array of processed data
 int val;
 for (int i = 0; i < 10; i++){ 
   data[i] = "mass: "+String(float(random(ThresholdMin,ThresholdMax)))+ " time: "+day()+"-"+month()+"-"+year()+"--"+hour()+":"+minute()+":"+second();
   val=data[i].toInt();
   EEPROM.write(i,i);
   //Serial.println(data[i].toInt());
 }
 int val2;
 for (int i=0;i<10;i++){
   val2=EEPROM.read(i);
   Serial.println(val2);} //read stored value
 //for (int i = 0 ; i < EEPROM.length() ; i++) { //clear and repeat process
 //   EEPROM.write(i, 0);
 // }

}

//to test behaviour we're assuming no invalid weights are being measured by the scale
void loop() {
  // put your main code here, to run repeatedly:
 
 
}
