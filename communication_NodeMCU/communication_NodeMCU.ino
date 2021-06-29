#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <SPI.h>
#include <MFRC522.h>

#define DHTTYPE    DHT11

////////////////////////////////////////////////////////////RFID
constexpr uint8_t RST_PIN = 16;//D0     
constexpr uint8_t SS_PIN = 5;  //D1

//////////////////////////////////////////////////////////////blynk_authentication_code
char auth[] = "E5aL_cWyjc12QG2gASICdegZmdMvSxJk";

///////////////////////////////////////////////////////////// Your WiFi credentials.
///////////////////////////////////////////////////////////// Set password to "" for open networks.
char ssid[] = "KKV-WiFi";
char pass[] = "icecream123";

/////////////////////////////////////////////////////////////pin declaration
uint8_t DHTPin = 4;  //D2
uint8_t IR =  A0;
uint8_t AD1 = 0;  //D3
uint8_t AD2 = 2;  //D4
uint8_t AD3 = 15; //D8


////////////////////////////////////////////////array declaration
int frl8_ary[3]     = {0,0,0};
int frfn_ary[3]     = {0,0,1};
int brl8_ary[3]     = {0,1,0};
int brfn_ary[3]     = {0,1,1};
int mtr_pin_ary[3]  = {1,0,0};
int buzz_pin_ary[3] = {1,0,1};
int mnl8_ary[3]     = {1,1,0};
int empty_ary[3]    = {1,1,1};
int data[3]         = {1,1,1};

String tag ;
int authorised = 1, alarm=0;
float Temperature = 32, Humidity = 68;

/////////////////////////////////////////////////////////////DHT 
DHT dht(DHTPin, DHTTYPE);

/////////////////////////////////////////////////////////////RFID
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

WidgetLED led_auth(V9); // led for authentication

////////////////////////////////////////////////////////////void_Setup
void setup() {
    // Debug console
  Serial.begin(9600);
  
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522.
  
  Blynk.begin(auth, ssid, pass);
  
  led_auth.off();
  pinMode(IR,INPUT);
  pinMode(AD1,OUTPUT);
  pinMode(AD2,OUTPUT);
  pinMode(AD3,OUTPUT);

}

////////////////////////////////////////////////////////////////////void_loop
void loop() 
{
  Blynk.run();
  appliance_controls();
  security_system();
  
  Serial.print("authorised: ");
  Serial.println(authorised);
  Serial.print("alarm: ");
  Serial.println(alarm);
  Serial.print("IR: ");
  Serial.println(analogRead(IR));

}

//////////////////////////////////////////////////////////////////Appliance controls
void appliance_controls()
{
  arduino_data();
  delay(2000);
  ary_cpy(data,empty_ary);
}

////////////////////////////////////////////////////////////////////arduino_data
void arduino_data()
{
  digitalWrite(AD1,data[0]);  
  Serial.print(data[0]);
  digitalWrite(AD2,data[1]);
  Serial.print(data[1]);
  digitalWrite(AD3,data[2]);
  Serial.println(data[2]);  
}

//////////////////////////////////////////////////////////////////Blynk write
BLYNK_WRITE(V2)  //FRL8
{    ary_cpy(data,frl8_ary);}
BLYNK_WRITE(V3)  //FRFN
{    ary_cpy(data,frfn_ary);}
BLYNK_WRITE(V4)  //BRL8
{    ary_cpy(data,brl8_ary);}
BLYNK_WRITE(V5)  //BRFN
{    ary_cpy(data,brfn_ary);}
BLYNK_WRITE(V6)  //MTR PIN
{ ary_cpy(data,mtr_pin_ary);}
BLYNK_WRITE(V7)  //MAIN L8
{    ary_cpy(data,mnl8_ary);}
BLYNK_WRITE(V8) // V8 is the Lock widget 
{ if (param.asInt())authorised = 0; else  authorised =1; }

//////////////////////////////////////////////////////////////////Blynk read
BLYNK_READ(V10)
{
  if (!isnan(Temperature) && Temperature < 90 && Temperature > 23) Blynk.virtualWrite(V10, Temperature);
  Temperature = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.println(Temperature); 
}
BLYNK_READ(V11)
{
  if (!isnan(Humidity) && Humidity < 100 && Humidity > 30 ) Blynk.virtualWrite(V11, Humidity);  
  Humidity = dht.readHumidity();
  Serial.print("Humidity: ");
  Serial.println(Humidity);    
}

//////////////////////////////////////////////////////////////////security system
void security_system()
{
  if (authorised ==0) read_rfid();
  if(authorised==1 && alarm==1) {
    led_auth.off();
    ary_cpy(data,buzz_pin_ary);
    alarm = 0;
    Blynk.virtualWrite(V8,0);   //lock widget       
  }  
}

////////////////////////////////////////////////////////////////////////////RFID Reading
void read_rfid()
{
  if ( ! rfid.PICC_IsNewCardPresent())
  {
    if(alarm==0 && analogRead(IR)< 50){
      ary_cpy(data,buzz_pin_ary);   
      led_auth.on();
      alarm=1;                    //alarm on
      delay(700);              
  }   
  return;
  }
  
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);    
    if(tag == "1175821844"){
        authorised = 1;
        Serial.println("unlocked using RFID");
        Blynk.virtualWrite(V8,0);   //lock widget
    }              
  }         
  
  tag = "";
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

/////////////////////////////////////////////////////////////////////////array_copy
void ary_cpy(int a[3], int b[3])  {  for(int i=0; i<3; i++)     a[i]=b[i];  }
