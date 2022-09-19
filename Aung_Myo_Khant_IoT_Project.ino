//import all require libraries
#include <Servo.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 4
LiquidCrystal_I2C lcd(0x27, 16, 2); 

//declaration for pinout
Servo myservo;
#define ir_enter 2
#define ir_back  4

#define ir_car1 5
#define ir_car2 6

int S1=0, S2=0;
int flag1=0, flag2=0; 
int slot = 2;
long c1startTime=0;
long c2startTime=0;  


//this part will setup all pin setup and lcd initial message
void setup(){
Serial.begin(9600);

pinMode(ir_car1, INPUT);
pinMode(ir_car2, INPUT);

pinMode(ir_enter, INPUT);
pinMode(ir_back, INPUT);
  
myservo.attach(3);
myservo.write(90);

//initialize printing message on LCD with 2 second delay
lcd.begin();  
lcd.setCursor (0,1);
lcd.print("    Car  parking  ");
lcd.setCursor (0,2);
lcd.print("       System     ");
delay (2000);
lcd.clear();   

int total = S1+S2;
slot = slot-total; 
}



void loop(){
Read_Sensor();
lcd.setCursor (0,0);
lcd.print("   Have Slot: "); 
lcd.print(slot); 

/*this part will check the object status on slot 1 by using ir_car1 and printing message according to result */
lcd.setCursor (0,1);   
if(digitalRead(ir_car1) == 0){
  lcd.print("S1:Fill "); 
  }
     else{
      lcd.print("S1:Empty");
      }

/*this part will check the object status on slot 1 by using ir_car2 and printing message according to result */
lcd.setCursor (10,1);
if(digitalRead(ir_car2) == 0){
      lcd.print("S2:Fill ");}
     else{
      lcd.print("S2:Empty");}    


/*if one car enters, the  total available slot is subtracted by 1*/
if(digitalRead (ir_enter) == 0 && flag1==0){
if(slot>0){flag1=1;
if(flag2==0){myservo.write(180); slot = slot-1;}
}else{
lcd.setCursor (0,0);
lcd.print(" Sorry Parking Full ");  
delay(1500);
}   
}

if(digitalRead (ir_back) == 0 && flag2==0){flag2=1;
if(flag1==0){myservo.write(180); slot = slot+1;}
}

if(flag1==1 && flag2==1){
delay (1000);
myservo.write(90);
flag1=0, flag2=0;
}

delay(1);
}

void Read_Sensor(){
S1=0, S2=0;

/*this coding will print the charges of car in slot 1 by calculating duration*/
lcd.setCursor (0,0);
if(digitalRead(ir_car1) == 1){
  c1startTime = millis();
  }
  else{
    long c1duration = ( millis() -c1startTime ) /1000 ;
      if(c1duration >30 && c1duration < 60){
     lcd.clear(); 
    lcd.setCursor (0,0);
    lcd.print("C1: 1000");
    delay(1000);
  }
  else if(c1duration > 60 && c1duration < 120){
    lcd.clear(); 
    lcd.setCursor (0,0);
    lcd.print("C1: 2000");
    delay(1000);
  }
  else if(c1duration > 120) {
    lcd.clear(); 
    lcd.setCursor (0,0);
    lcd.print("C1: 2500");
    delay(1000);
  }
  else{
    lcd.clear(); 
    lcd.setCursor (0,0);
    lcd.print("C1: 0");
    delay(1000);
 }
}

/*this coding will print the charges of car in slot 2 by calculating duration*/
lcd.setCursor (0,1);
if(digitalRead(ir_car2) == 1){
  c2startTime = millis();
  }
  else{
    long c2duration = ( millis() -c2startTime ) /1000 ;
      if(c2duration >30 && c2duration < 60){
    lcd.clear(); 
    lcd.setCursor (0,1);
    lcd.print("C2: 1000");
    delay(1000);
  }
  else if(c2duration > 60 && c2duration < 120){
    lcd.clear(); 
    lcd.setCursor (0,1);
    lcd.print("C2: 2000");
    delay(1000);
  }
  else if(c2duration > 120) {
    lcd.clear(); 
    lcd.setCursor (0,1);
    lcd.print("C2: 2500");
    delay(1000);
  }
  else{
    lcd.clear(); 
    lcd.setCursor (0,1);
    lcd.print("C2: 0");
    delay(1000);
 }
}  
}
