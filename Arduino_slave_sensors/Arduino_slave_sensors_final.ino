#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <SPI.h>

#include "DHT.h"

#define DHTPIN 4     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
#include <SFE_BMP180.h>
SFE_BMP180 pressure;
#define ALTITUDE 943.7 // Altitude of Electropeak Co. in meters
 float h,t,hic,Light,a,p,pres;
 char result[31];
 char data[31];
 String DATA;
 double T,P,  p0;
 int possibility;
 
void setup()
{Serial.begin(9600);
 Wire.begin(8); /* join i2c bus with address 8 */
 Wire.onReceive(receiveEvent); /* register receive event */
 Wire.onRequest(requestEvent);
if (pressure.begin())
Serial.println("BMP180 init success");
else
{
Serial.println("BMP180 init fail\n\n");
Serial.println("Check connection");
while (1);
}

  dht.begin();

}

void loop()
{char status;

status = pressure.startTemperature();
if (status != 0)
{
delay(status);
status = pressure.getTemperature(T);
if (status != 0)
{
Serial.print("temperature: ");
Serial.print(T, 2);
Serial.println(" deg C ");
status = pressure.startPressure(3);
if (status != 0)
{
delay(status);
status = pressure.getPressure(P, T);

if (status != 0)
{
Serial.print("absolute pressure: ");
Serial.print(P, 2);
Serial.print(" hpa = ");
Serial.print(P * 100, 2);
Serial.print(" pa = ");
Serial.print(P * 0.000986923, 2);
Serial.print(" atm = ");
Serial.print(P * 0.750063755, 2);
Serial.print(" mmHg = ");
Serial.print(P * 0.750061683, 2);
Serial.print(" torr = ");
Serial.print(P * 0.014503774, 2);
Serial.println(" psi");
p0 = pressure.sealevel(P, ALTITUDE); // we're at 943.7 meters
Serial.print("relative (sea-level) pressure: ");
Serial.print(p0, 2);
Serial.println(" hpa ");;
a = pressure.altitude(P, p0);
Serial.print("your altitude: ");
Serial.print(a, 0);
Serial.println(" meters ");
}
else Serial.println("error retrieving pressure measurement\n");
}
else Serial.println("error starting pressure measurement\n");
}
else Serial.println("error retrieving temperature measurement\n");
}
else Serial.println("error starting temperature measurement\n");
float value = analogRead(A0);
  Serial.print("Analog value : ");
  Serial.println(value);
float Humidity = dht.readHumidity();
    float Temperature = dht.readTemperature();
    Light =value;

    if(Humidity  > 70.0)
      if(Temperature >= -4.0 && Temperature < 10)
        if(Light < 500) possibility = 3;
        else if(Light < 700) possibility = 2;
        else if(Light < 800) possibility = 1;
        else if(Light < 1000) possibility = 0;
        else possibility = -1;
      else if(Temperature >= 10 && Temperature < 23)
        if(Light < 500) possibility = 4;
        else if(Light < 700) possibility = 3;
        else if(Light < 800) possibility = 2;
        else if(Light < 1000) possibility = 1;
        else possibility = 0;
      else if(Temperature >=23 && Temperature < 30)
        if(Light < 500) possibility = 5;
        else if(Light < 700) possibility = 4;
        else if(Light < 800) possibility = 3;
        else if(Light < 1000) possibility = 1;
        else possibility = 0;
      else if(Temperature >=30)
        if(Light < 500) possibility = 5;
        else if(Light < 700) possibility = 4;
        else if(Light < 800) possibility = 3;
        else if(Light < 1000) possibility = 1;
        else possibility = 0;
    else if(Humidity <= 65.0) possibility = 0;
    //lcd.autoscroll();
    switch (possibility){
      case -1:
        Serial.print("There is no possibility of rain \n");
        //lcd.print("no chance");
      break;
      case 0:
        Serial.print("There is a very low possibility of rain \n");
        //lcd.print("very low chance");
        break;
      case 1:
        Serial.print("There is a low possibility of rain \n");
        //lcd.print("low chance");
        break;
      case 2:
        Serial.print("There is a slight chance of rain \n");
        //lcd.print("slight chance");
        break;
      case 3:
        Serial.print("There is moderate chance of rain \n");
       // lcd.print("moderate chance");
        break;
      case 4:
        Serial.print("There is a high possibility of rain \n");
       // lcd.print("high chance ");
        break;
      case 5:
        Serial.print("There is a very high possibility of rain \n");
        //lcd.print("very high chance");
    }

Serial.println("==========================================================================");
delay(5000);
  
 // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  h = dht.readHumidity();
  p=(float)possibility;
  t = dht.readTemperature();
  pres=P;
  hic = dht.computeHeatIndex(t, h, false);
  
delay(5000);

 Serial.println(pres);

  Serial.print(F("Humidity"));
  Serial.print(h);
  Serial.print(F("%"));
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
 
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
 

}
void receiveEvent(int howMany) {
 while (0 <Wire.available()) {
    char c = Wire.read();      /* receive byte as a character */
    Serial.print(c);           /* print the character */
  }
 Serial.println();             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {

  dtostrf(h,2,1,result) ;
  DATA=DATA+result+" ";
  dtostrf(t,2,1,result);
  DATA=DATA+result+" ";
  dtostrf(hic,2,1,result);
  DATA=DATA+result+" ";
  dtostrf(a,2,1,result);
  DATA=DATA+result+" ";
  dtostrf(pres,4,0,result);
  DATA=DATA+result+" ";
  dtostrf(Light,2,1,result);
  DATA=DATA+result;
  
  DATA.toCharArray(data,128);
  Wire.write(data);
  DATA="";
  
 
}
String chartoString(char arr[], String ss){
  for(int i=0; i<sizeof(arr);i++){
    ss.concat(arr[i]);
  }
  return ss;
}
