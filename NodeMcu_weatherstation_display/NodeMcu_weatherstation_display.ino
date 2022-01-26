#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <OneWire.h> 
const int btnwhite = D0; 
const int btnblack = D5; 
int temp=0;
char c;
String DATA;
String  str;
String strs[20];
int StringCount = 0;
String data,h,t,hic,a,tempp,Light;
bool switchwhite=true;
int state=0;
bool switchblack=true;
bool switched=true;
bool found=false;
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS); 
LiquidCrystal_I2C lcd(0x27, 16, 2);
  float hum= 0;
  float tee= 0;
  float aaa= 0;
  float lll=0;
  float pres=0;
  float ppp=0;
  int posy=1;
  float hicc=0;
  int buttonStateon = 0; 
  int buttonState = 0; 
  int btnwhitestate=0;
  int btnblackstate=0;
  unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 2000;           // interval at which to blink (milliseconds)



void setup()
{
  Serial.begin(9600);
   Wire.begin(2,0);
/*Wire.begin(D1, D2);*/
 lcd.init();                      // initialize the lcd 
 lcd.backlight();
  
 pinMode(btnwhite, INPUT);
 pinMode(btnblack, INPUT);
}



void loop()
{
 
  
    while(state==1)
    { 
      
    lcd.backlight();
    getdata();
   /*//datafresh();  */
    Serial.println("WHITE");
    lcd.clear();
    lcd.setCursor(0,0); // Sets the cursor to col 0 and row 0
    lcd.print(F("Humidity: ")); Serial.println("Humidity ");
    lcd.setCursor(0,1);
    lcd.print(hum);
    lcd.print(F(" %"));
    

    advanceddelay();
      lcd.clear();
     // Sets the cursor to col 1 and row 0
    lcd.setCursor(0,0);
    lcd.print(F("Temperature:"));Serial.println("temp ");
    lcd.setCursor(0,1);
    lcd.print(tee);
    lcd.print(F(" Celsius "));
      advanceddelay();
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("HeatIndex: "));Serial.println("heat ");
    lcd.setCursor(0,1);
    lcd.print(hicc);
    lcd.print(F(" Celsius "));
    advanceddelay();
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Altitude: "));Serial.println("alt ");
    lcd.setCursor(0,1);
    lcd.print(aaa);
    lcd.print(F(" M "));
      advanceddelay();
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Light intesity: "));Serial.println("light ");
    lcd.setCursor(0,1);

      if(lll>=0&&lll<350)
       {
        lcd.print("Low"); 
       }
       else
       {
         if(lll>=0&&lll<700)
         {
         lcd.print("Moderate"); 
         }
         else
         {
         lcd.print("High"); 
         }
        }

    advanceddelay();
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Pressure: "));Serial.println("pres ");
    lcd.setCursor(0,1);
    lcd.print(pres);
    lcd.print(F(" PSI "));
    advanceddelay();
    
      found=false;
    }
  while(state==2)
  {
  /*//datafresh();*/
    
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Will it rain?: "));Serial.println("rain ");
    lcd.setCursor(0,1);

if(hum  > 70.0)
      if(tee >= -4.0 && tee < 10)
        if(lll < 500) posy = 3;
        else if(lll < 700) posy = 2;
        else if(lll < 800) posy = 1;
        else if(lll < 1000) posy = 0;
        else posy = -1;
      else if(tee >= 10 && tee < 23)
        if(lll < 500) posy = 4;
        else if(lll < 700) posy = 3;
        else if(lll < 800) posy = 2;
        else if(lll < 1000) posy = 1;
        else posy = 0;
      else if(tee >=23 && tee < 30)
        if(lll < 500) posy = 5;
        else if(lll < 700) posy = 4;
        else if(lll < 800) posy = 3;
        else if(lll < 1000) posy = 1;
        else posy = 0;
      else if(tee >=30)
        if(lll < 500) posy = 5;
        else if(lll < 700) posy = 4;
        else if(lll < 800) posy = 3;
        else if(lll < 1000) posy = 1;
        else posy = 0;
    else if(hum <= 65.0) posy = 0;

    switch (posy)
    {
        case -1:
          Serial.print("There is no possibility of rain \n");
          lcd.print("No chance");
        break;
        case 0:
          Serial.print("There is a very low possibility of rain \n");
          lcd.print("Very low chance");
          break;
        case 1:
          Serial.print("There is a low possibility of rain \n");
          lcd.print("Low chance");
          break;
        case 2:
          Serial.print("There is a slight chance of rain \n");
          lcd.print("Slight chance");
          break;
        case 3:
          Serial.print("There is moderate chance of rain \n");
         lcd.print("Moderate chance");
          break;
        case 4:
          Serial.print("There is a high possibility of rain \n");
         lcd.print("High chance ");
          break;
        case 5:
          Serial.print("There is a very high possibility of rain \n");
          lcd.print("Very high chance");
      }
      advanceddelay();
    found=false;
   }
  
  while(state==0){
/* //datafresh();*/
  Serial.print("Device is offline \n turn on with black button");
  lcd.noBacklight();
  advanceddelay();
  found=false;
  
 }
}

void advanceddelay(){
  switched=true;
  if(!found){
    for(int i=0; i<2000; i++){
      milisec();
      if(found){
        break;
        }
      }
    }
  }
void milisec(){
  
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    btnwhitestate = digitalRead(btnwhite);
    btnblackstate=digitalRead(btnblack);

    
    if(state==1 && btnwhitestate==HIGH&&switched==true){
    state=2;
    Serial.println("switch state to 2");
    switched=false;
    found=true;
    }
    if(state==2 && btnwhitestate==HIGH&switched==true){
    state=1;
    Serial.println("switch stateto 1");
    switched=false;
    found=true;
    }

    if(state==0 && btnblackstate==HIGH&&switched==true){
    state=1;Serial.println("Turn on");switched=false;found=true;
    }
    if(state!=0 && btnblackstate==HIGH&&switched==true){
    state=0;
    Serial.println("Turn off");
    switched=false;
    found=true;
    }

    Serial.print("switched: ");
    Serial.println(switched);
    Serial.print("state: ");
    Serial.println(state);
    Serial.print("buttonstate black: ");
    Serial.println(btnblackstate);
    Serial.print("buttonstate WHITE: ");
    Serial.println(btnwhitestate);
    Serial.print("switch WHITE: ");
    Serial.println(switchwhite);
    Serial.print("buttonstate black: ");
    Serial.println(switchblack);
    // set the LED with the ledState of the variable:
   
  }
  delay(1);
}


 void split(){
  StringCount = 0;
  strs[20];
  for (int i = 0; i < 20; i++)
  {strs[i]="";
  }
  
 str = DATA;
 Serial.println();
  // Split the string into substrings
  while (str.length() > 0)
  {
    int index = str.indexOf(' ');
    if (index == -1) // No space found
    {
      strs[StringCount++] = str;
      break;
    }
    else
    {
      strs[StringCount++] = str.substring(0, index);
      str = str.substring(index+1);
    }
  }
  
  // Show the resulting substrings
  for (int i = 0; i < StringCount; i++)
  {
    
    Serial.print(i);
    Serial.print(": \"");
    Serial.print(strs[i]);
    Serial.println("\"");
  }
  hum=strs[0].toFloat();
  tee=strs[1].toFloat();
  hicc=strs[2].toFloat();
  aaa=strs[3].toFloat();
  pres=strs[4].toFloat();
  lll=strs[5].toFloat();

  
}

void getdata(){

 Wire.begin(D1, D2);
 Wire.beginTransmission(8); /* begin with device address 8 */
 Wire.write("Hello Arduino");  /* sends hello string */
 Wire.endTransmission();    /* stop transmitting */

 Wire.requestFrom(8, 31); /* request & read data of size 13 from slave */
 while(Wire.available()){
    c = Wire.read();
    DATA=DATA+c;

 }
 Serial.println();
 Serial.println(DATA);
 split();
 DATA="";
 
 
 delay(500);
  Wire.begin(2,0);
  
  }
  
  
