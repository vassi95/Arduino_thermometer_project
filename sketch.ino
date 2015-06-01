#include "DHT.h"
#include <BitVoicer11.h>

#define DHTPIN 13    
#define DHTTYPE DHT11 
#define COMMON_ANODE

DHT dht(DHTPIN, DHTTYPE);
int redPin = 12;
int greenPin = 10;
int bluePin = 11;
int fanPin= 5;
int lightLevel = 0;

 
BitVoicerSerial bvSerial = BitVoicerSerial();

void setup() {
  setColor(0, 0, 0);
  digitalWrite(fanPin, LOW);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(fanPin, OUTPUT); 
  Serial.begin(9600);
  dht.begin();
  }

void loop() {
  bvSerial.getData();

  if (bvSerial.strData == "")
  {
    return;
  }

  if (bvSerial.strData == "wake")
  {
    digitalWrite(fanPin, LOW);
    digitalWrite(redPin, HIGH);
    delay(200);
    digitalWrite(redPin, LOW);
    delay(200);
    digitalWrite(redPin, HIGH);
    delay(200);
    digitalWrite(redPin, LOW);
    delay(200);
    digitalWrite(redPin, HIGH);
    delay(200);
    digitalWrite(redPin, LOW);
    bvSerial.strData = "";
    lightLevel = 0;
  }

   else if (bvSerial.strData == "sleep")
  {
    setColor(0, 0, 0);
    digitalWrite(fanPin, LOW);
    bvSerial.strData = "";
    lightLevel = 0;
  }
  
  
  else if (bvSerial.strData == "temp"){
    digitalWrite(fanPin, LOW);
    float t = dht.readTemperature();

    if (t>0 && t<21)
	setColor(255, 0, 0);  // blue

    if (t>19&& t<27)
	setColor(0, 0, 255);  // green

    if (t>26 && t<34)
	setColor(0, 255, 255); //yellow

    if(t>33 &&t<41)
	setColor(3, 255, 15); //orange

    if (t>40 && t<50){
	setColor(0, 255, 0); //red
	digitalWrite(fanPin, HIGH); 
    }

    bvSerial.strData = "";
    lightLevel = 0;
  }

  else if (bvSerial.strData == "first"){
    digitalWrite(fanPin, LOW);
    setColor(255, 0, 0);  // blue
    bvSerial.strData = "";
    lightLevel = 0;
  }
  
  else if (bvSerial.strData == "second")
  {
    digitalWrite(fanPin, LOW);
    setColor(0, 0,255);  // green
    bvSerial.strData = "";
    lightLevel = 0;
  }
  
  else if (bvSerial.strData == "third")
  {
    setColor(0, 255, 255);  // yellow
    digitalWrite(fanPin, LOW);
    bvSerial.strData = "";
    lightLevel = 0;
  }
  
  else if (bvSerial.strData == "fourth")
  {
    setColor(3, 255, 15);  // orange
    digitalWrite(fanPin, LOW);
    bvSerial.strData = "";
    lightLevel = 0;
  }
  
  else if (bvSerial.strData == "fifth")
  {
    setColor(0, 255, 0);  // red
    digitalWrite(fanPin, HIGH);
    Serial.println("#S|GO6U|[]#"); 
    bvSerial.strData = "";
    lightLevel = 0;
  }
  
  
  else if (bvSerial.strData == "fON")
  {
    digitalWrite(fanPin, HIGH);
    bvSerial.strData = "";
    lightLevel = 0;
  }
  
  else if (bvSerial.strData == "fOFF")
  {
    digitalWrite(fanPin, LOW);
    bvSerial.strData = "";
    lightLevel = 0;
  }
  
  else
  {
   bvSerial.startStopListening();
   bvSerial.sendToBV("ERROR:" + bvSerial.strData);
   bvSerial.startStopListening();
  }

}

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif

  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue); 

}


  
