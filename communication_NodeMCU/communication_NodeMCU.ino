#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
<<<<<<< HEAD
#include <DHT.h>

#define DHTTYPE    DHT11
=======
>>>>>>> feature-communication

//////////////////////////////////////////////////////////////blynk_authentication_code
char auth[] = "E5aL_cWyjc12QG2gASICdegZmdMvSxJk";

///////////////////////////////////////////////////////////// Your WiFi credentials.
///////////////////////////////////////////////////////////// Set password to "" for open networks.
char ssid[] = "KKV-WiFi";
char pass[] = "icecream123";

/////////////////////////////////////////////////////////////pin declaration
<<<<<<< HEAD
uint8_t DHTPin = 2; //D4
=======
>>>>>>> feature-communication
uint8_t AD1 = 12;  //D6
uint8_t AD2 =  13;  //D7
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

int authorised = 1;
<<<<<<< HEAD
float Temperature=0,Humidity = 0;

/////////////////////////////////////////////////////////////DHT 
DHT dht(DHTPin, DHTTYPE);

////////////////////////////////////////////////////////////void_Setup
=======

>>>>>>> feature-communication
void setup() {
    // Debug console
  Serial.begin(9600);
  
  Blynk.begin(auth, ssid, pass);
  
  pinMode(AD1,OUTPUT);
  pinMode(AD2,OUTPUT);
  pinMode(AD3,OUTPUT);

}

////////////////////////////////////////////////////////////////////void_loop
void loop() {
  Blynk.run();
  appliance_controls();

  Serial.print("authorised: ");
  Serial.println(authorised);
}

//////////////////////////////////////////////////////////////////Appliance controls
void appliance_controls(){
  arduino_data();
  delay(2000);
  ary_cpy(data,empty_ary);
}

////////////////////////////////////////////////////////////////////arduino_data
void arduino_data(){
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

<<<<<<< HEAD
//////////////////////////////////////////////////////////////////Blynk read
BLYNK_READ(V10){
  if (!isnan(Temperature)) Blynk.virtualWrite(V10, Temperature);
  Temperature = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.println(Temperature); 
}
BLYNK_READ(V11){
  if (!isnan(Humidity)) Blynk.virtualWrite(V11, Humidity);  
  Humidity = dht.readHumidity();
  Serial.print("Humidity: ");
  Serial.println(Humidity);    
}

=======
>>>>>>> feature-communication
/////////////////////////////////////////////////////////////////////////array_copy
void ary_cpy(int a[3], int b[3])  {  for(int i=0; i<3; i++)     a[i]=b[i];  }
