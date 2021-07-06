/*Arduino side code for IOT Home*/
#define frl8 4
#define frfn 5
#define brl8 6
#define brfn 7
#define buzz_pin 9
#define mtr_pin 10

#define dp1 11
#define dp2 12
#define dp3 13

#define MQ A0
#define Flame_snsr A2
#define alarm_led A7
#define half A4
#define full A5

int frl8_ary[3]     = {0,0,0};
int frfn_ary[3]     = {0,0,1};
int brl8_ary[3]     = {0,1,0};
int brfn_ary[3]     = {0,1,1};
int mtr_pin_ary[3]  = {1,0,0};
int buzz_pin_ary[3] = {1,0,1};
int mnl8_ary[3]     = {1,1,0};
int empty_ary[3]    = {1,1,1};
int data[3];

int flag = 0, comnd_dly = 500, prog_dly = 500, MQ_thrshld = 400;
int frl8_state=0 ,frfn_state=0 ,brl8_state=0 ,brfn_state=0;
int mtr_pin_state=0, buzz_pin_state=0, mnl8_state=0;

void setup()    /////////////////////////////////////////////////////////////////void_setup
{
  pinMode(frl8,OUTPUT);
  pinMode(frfn,OUTPUT);
  pinMode(brl8,OUTPUT);
  pinMode(brfn,OUTPUT);
  pinMode(mtr_pin,OUTPUT);
  pinMode(buzz_pin,OUTPUT);

  pinMode(dp1,INPUT);
  pinMode(dp2,INPUT);
  pinMode(dp3,INPUT);
  pinMode(MQ,INPUT);
  pinMode(Flame_snsr,INPUT);
  
  Serial.begin(9600);

  delay(300);
  digitalWrite(frl8,HIGH);
  digitalWrite(frfn,HIGH);
  digitalWrite(brl8,HIGH);
  digitalWrite(brfn,HIGH);
  digitalWrite(mtr_pin,HIGH);
  digitalWrite(buzz_pin,LOW);
}

void loop() /////////////////////////////////////////////////////////////////void_loop
{
  data[0]=digitalRead(dp1);
  data[1]=digitalRead(dp2);
  data[2]=digitalRead(dp3);
  Serial.print("data array = {");
  Serial.print(data[0]);
  Serial.print(',');
  Serial.print(data[1]);
  Serial.print(',');
  Serial.print(data[2]);
  Serial.println('}');

  appliance_control();
  safety();
  water_refill();
  
  delay(prog_dly); 
}

void safety()   /////////////////////////////////////////////////////////////////safety
{
  if (analogRead(MQ) > MQ_thrshld && analogRead(Flame_snsr) > 550)  digitalWrite(alarm_led,HIGH);
  else digitalWrite(alarm_led,LOW);

  Serial.print("MQ: ");
  Serial.println(analogRead(MQ));
  Serial.print("Flame: ");
  Serial.println(analogRead(Flame_snsr));
  Serial.print("Half: ");
  Serial.println(analogRead(half));
  Serial.print("Full: ");
  Serial.println(analogRead(full));
}

void water_refill()   /////////////////////////////////////////////////////////////////water_system
{  
  if (analogRead(half) > 500) 
  {
    digitalWrite(mtr_pin,LOW);
    Serial.println("Motor Pin ON");
  }
  if (analogRead(full) < 380)
  {
    digitalWrite(mtr_pin,HIGH);
    Serial.println("Motor Pin OFF");
  }
}

void appliance_control()    /////////////////////////////////////////////////////////////////appliance_control
{
  if (flag==0)
{
  if(data[0] == frl8_ary[0] && data[1] == frl8_ary[1] && data[2] == frl8_ary[2])
  {
    if(frl8_state == 0)
    {
    digitalWrite(frl8,LOW);
    Serial.println("Front Room Light ON");
    frl8_state = 1;
    }
    else if (frl8_state == 1)
    {
    digitalWrite(frl8,HIGH);
    Serial.println("Front Room Light OFF"); 
    frl8_state = 0;    
    }
    flag =1;
    delay(comnd_dly);
  }

    else if(data[0] == frfn_ary[0] && data[1] == frfn_ary[1] && data[2] == frfn_ary[2])
  {
    if(frfn_state == 0)
    {
    digitalWrite(frfn,LOW);
    Serial.println("Front Room Fan ON");
    frfn_state = 1;
    }
    else if (frfn_state == 1)
    {
    digitalWrite(frfn,HIGH);
    Serial.println("Front Room Fan OFF"); 
    frfn_state = 0;    
    }
    flag =1;
    delay(comnd_dly);
  }

    else if(data[0] == brl8_ary[0] && data[1] == brl8_ary[1] && data[2] == brl8_ary[2])
  {
    if(brl8_state == 0)
    {
    digitalWrite(brl8,LOW);
    Serial.println("Back Room Light ON");
    brl8_state = 1;
    }
    else if (brl8_state == 1)
    {
    digitalWrite(brl8,HIGH);
    Serial.println("Back Room Light OFF"); 
    brl8_state = 0;    
    }
    flag =1;
    delay(comnd_dly);
  }

    else if(data[0] == brfn_ary[0] && data[1] == brfn_ary[1] && data[2] == brfn_ary[2])
  {
    if(brfn_state == 0)
    {
    digitalWrite(brfn,LOW);
    Serial.println("Back Room Fan ON");
    brfn_state = 1;
    }
    else if (brfn_state == 1)
    {
    digitalWrite(brfn,HIGH);
    Serial.println("Back Room Fan OFF"); 
    brfn_state = 0;    
    }
    flag =1;
    delay(comnd_dly);
  }

    else if(data[0] == buzz_pin_ary[0] && data[1] == buzz_pin_ary[1] && data[2] == buzz_pin_ary[2])
  {
    if(buzz_pin_state == 0)
    {
    digitalWrite(buzz_pin,HIGH);
    Serial.println("Buzzer Alarm ON");
    buzz_pin_state = 1;
    }
    else if (buzz_pin_state == 1)
    {
    digitalWrite(buzz_pin,LOW);
    Serial.println("Buzzer Alarm OFF"); 
    buzz_pin_state = 0;    
    }
    delay(comnd_dly);
    flag =1;
  }
}

else if(data[0] == empty_ary[0] && data[1] == empty_ary[1] && data[2] == empty_ary[2])
  {
    flag = 0;
    Serial.println(flag);
  }
}
