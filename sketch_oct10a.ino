

#include <Wire.h>
#include "SparkFun_VEML6030_Ambient_Light_Sensor.h"

#define AL_ADDR 0x48

SparkFun_Ambient_Light light(AL_ADDR);

// Possible values: .125, .25, 1, 2
// Both .125 and .25 should be used in most cases except darker rooms.
// A gain of 2 should only be used if the sensor will be covered by a dark
// glass.
float gain = .125;

// Possible integration times in milliseconds: 800, 400, 200, 100, 50, 25
// Higher times give higher resolutions and should be used in darker light.
int time = 25;
long luxVal = 0;
long lux1=0,lux2=0,lux3=0,lux4=0,lux5=0;



void darkcheck(long luxVal){
 
 if (luxVal<50){

Serial.println("Not bright enough to take a picture");
  
 }


 
}



void brightcheck(long luxVal){

if (luxVal>50){
  Serial.println("Bright enough to take a picture");
}
}




long smoothlux(long luxVal){

lux5=lux4;
lux4=lux3;
lux3=lux2;
lux2=lux1;
lux1=luxVal;

return((lux5+lux4+lux3+lux2+lux1)/5);
  
}





void setup(){

  Wire.begin();
  Serial.begin(115200);

  if(light.begin())
    Serial.println("Ready to sense some light!");
  else
    Serial.println("Could not communicate with the sensor!");

  // Again the gain and integration times determine the resolution of the lux
  // value, and give different ranges of possible light readings. Check out
  // hoookup guide for more info.
  light.setGain(gain);
  light.setIntegTime(time);

  Serial.println("Reading settings...");
  Serial.print("Gain: ");
  float gainVal = light.readGain();
  Serial.print(gainVal, 3);
  Serial.print(" Integration Time: ");
  int timeVal = light.readIntegTime();
  Serial.println(timeVal);

}

void loop(){

  luxVal = light.readLight();

  luxVal=smoothlux(luxVal);
 // Serial.print("Ambient Light Reading: ");
  Serial.println(luxVal);
 // Serial.println(" Lux");  
  darkcheck(luxVal);
  brightcheck(luxVal);
  delay(100);
  
 



}
