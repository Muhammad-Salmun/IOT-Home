#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>


#define DHTTYPE    DHT11 


///////////////////////////RFID/////////////
constexpr uint8_t RST_PIN = 16;//D0     
constexpr uint8_t SS_PIN = 5;  //D1

uint8_t motor_in1 = 2; //D2
uint8_t motor_in2 = 0; //D3
uint8_t AD1 = 14;  //D5
uint8_t AD2 = 13;  //D7
uint8_t AD3 = 15; //D8
uint8_t IR =  12;  //D6
uint8_t DHTPin = 2; //D4
uint8_t MQ = A0;

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

BlynkTimer timer;
WidgetLED led_auth(V10); // led for authentication

DHT dht(DHTPin, DHTTYPE); 

char auth[] = "E5aL_cWyjc12QG2gASICdegZmdMvSxJk", //for blynk app
//wifi usernamw and password
    ssid[] = "KKV-WiFi",
    pass[] = "icecream123";
// RFID Tag
String tag ;
float Temperature=0,Humidity = 0;
int authorised = 0,closed = 0,mq_value;

void setup() {

  pinMode(IR,INPUT);
  pinMode(MQ,INPUT);
  pinMode(motor_in1,INPUT);
  pinMode(motor_in2,INPUT);
  pinMode(AD1,OUTPUT);
  pinMode(AD2,OUTPUT);
  pinMode(AD3,OUTPUT);
  
  Serial.begin(9600);
  
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
  
}

void loop() {
  
   read_rfid();
   if(closed == 1 && motion()== 1) alarm();
   mq_value = analogRead(MQ);
   if(mq_value>100) alarm();   
   //Serial.println(tag);   
   Blynk.run();
   timer.run(); // running timer every second
   
}
//////////////////////////////////////////////////////////////

void read_rfid(){

  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);
    if(tag == "1175821844"){
      authorised = 1;
      myTimerEvent();
    }
    else
      authorised = 0;
      
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    }
  
  }

void myTimerEvent()
{
  if(authorised == 1){
      Blynk.virtualWrite(V1,0);
      led_auth.off();
      authorised = 0;
     }
}

BLYNK_WRITE(V1) // V1 is the Lock widget 
{
  if (param.asInt()){
    led_auth.on();
    closed = 1;
  }
  else{
    led_auth.off();
    closed = 0;
  }
}

int motion(){
  int ir_value = digitalRead(IR);
  if(ir_value == 1)  return 1;        
  else return 0;    
}

void alarm(){
  arduino_data(1,0,1);
  delay(500);
  }

///////////////////////////////////////////////////////////////////////
// V21 is temp guage, V22 is humidity
BLYNK_READ(V5) 
{
  Temperature = dht.readTemperature();
  Humidity = dht.readHumidity();
  Serial.println(Temperature);
  Serial.println(Humidity);
  Blynk.virtualWrite(V21, Temperature); 
  Blynk.virtualWrite(V22, Humidity);
}

////////////////////////////////////////

BLYNK_WRITE(V2)  //FRL8
{
  if(param.asInt())  arduino_data(0,0,0);
  //arduino_data(0,0,0);
}
BLYNK_WRITE(V3)  //FRFN
{
  if(param.asInt()) arduino_data(0,0,1);
  //arduino_data(1,1,1);
}
BLYNK_WRITE(V4)  //BRL8
{
 if(param.asInt())  arduino_data(0,1,0);
 
 //arduino_data(1,1,1);
}
BLYNK_WRITE(V5)  //BRFN
{
  if(param.asInt())   arduino_data(0,1,1);
  //arduino_data(1,1,1);
}
BLYNK_WRITE(V6)  //MTR PIN
{
  if(param.asInt()) {  arduino_data(1,0,0);
  Serial.println("led on");}
  //arduino_data(1,1,1);
}
BLYNK_WRITE(V7)  //MAIN L8
{
  if(param.asInt())   arduino_data(1,1,0);
  //arduino_data(1,1,1);
}

void arduino_data(int i,int j, int k){
  digitalWrite(AD1,i);
  Serial.print(i);
  digitalWrite(AD2,j);
  Serial.print(j);
  digitalWrite(AD3,k);
  Serial.println(k);
}
