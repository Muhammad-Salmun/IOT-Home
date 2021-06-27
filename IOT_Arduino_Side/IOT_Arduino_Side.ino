/*Arduino side code for IOT Home*/
#define frl8 4
#define frfn 5
#define brl8 6
#define brfn 7
#define mtr_pin 8
#define buzz_pin 9
#define mnl8 10

#define dp1 11
#define dp2 12
#define dp3 13

int frl8_ary[3]     = {0,0,0};
int frfn_ary[3]     = {0,0,1};
int brl8_ary[3]     = {0,1,0};
int brfn_ary[3]     = {0,1,1};
int mtr_pin_ary[3]  = {1,0,0};
int buzz_pin_ary[3] = {1,0,1};
int mnl8_ary[3]     = {1,1,0};
int empty_ary[3]    = {1,1,1};
int data[3];

int flag = 0, comnd_dly = 500, prog_dly = 500;
int frl8_state=0 ,frfn_state=0 ,brl8_state=0 ,brfn_state=0;
int mtr_pin_state=0, buzz_pin_state=0, mnl8_state=0;

void setup()
{
  pinMode(frl8,OUTPUT);
  pinMode(frfn,OUTPUT);
  pinMode(brl8,OUTPUT);
  pinMode(brfn,OUTPUT);
  pinMode(mtr_pin,OUTPUT);
  pinMode(buzz_pin,OUTPUT);
  pinMode(mnl8,OUTPUT);

  pinMode(dp1,INPUT);
  pinMode(dp2,INPUT);
  pinMode(dp3,INPUT);
  
  Serial.begin(9600);

  digitalWrite(mnl8,LOW);
  digitalWrite(frl8,LOW);
  digitalWrite(frfn,LOW);
  digitalWrite(brl8,LOW);
  digitalWrite(brfn,LOW);
  digitalWrite(mtr_pin,LOW);
  digitalWrite(buzz_pin,LOW);
}

void loop()
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

if (flag==0)
{
  if(data[0] == mnl8_ary[0] && data[1] == mnl8_ary[1] && data[2] == mnl8_ary[2])
  {
    if(mnl8_state == 0)
    {
    digitalWrite(mnl8,LOW);
    Serial.println("Main Light ON");
    mnl8_state = 1;
    }
    else if (mnl8_state == 1)
    {
    digitalWrite(mnl8,HIGH);
    Serial.println("Main Light OFF"); 
    mnl8_state = 0;    
    }
    flag =1;
    delay(comnd_dly);
  }

   else if(data[0] == frl8_ary[0] && data[1] == frl8_ary[1] && data[2] == frl8_ary[2])
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

    else if(data[0] == mtr_pin_ary[0] && data[1] == mtr_pin_ary[1] && data[2] == mtr_pin_ary[2])
  {
    if(mtr_pin_state == 0)
    {
    digitalWrite(mtr_pin,LOW);
    Serial.println("Motor Pin ON");
    mtr_pin_state = 1;
    }
    else if (mtr_pin_state == 1)
    {
    digitalWrite(mtr_pin,HIGH);
    Serial.println("Motor Pin OFF"); 
    mtr_pin_state = 0;    
    }
    flag =1;
    delay(comnd_dly);
  }

    else if(data[0] == buzz_pin_ary[0] && data[1] == buzz_pin_ary[1] && data[2] == buzz_pin_ary[2])
  {
    if(buzz_pin_state == 0)
    {
    digitalWrite(buzz_pin,LOW);
    Serial.println("Buzzer Alarm ON");
    buzz_pin_state = 1;
    }
    else if (buzz_pin_state == 1)
    {
    digitalWrite(buzz_pin,HIGH);
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
  delay(prog_dly); 
}
