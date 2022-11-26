
#include <Servo.h>

#define echopin_s1 A0 // echo pin
#define triggerpin_s1 A1 // Trigger pin

#define echopin_s2  A2 // echo pin
#define triggerpin_s2 A3 // Trigger pin
Servo myservo; 
int buzzer = 7;
int led_R = 11;
int led_G = 12;
long dis_S,dis_M;
long Binheight ;



void ultra_read(int pin_t,int pin_e,long &ultra_distance){
long time;
pinMode(pin_t,OUTPUT);
pinMode(pin_e,INPUT);
digitalWrite(pin_t,LOW);
delayMicroseconds(2);
digitalWrite(pin_t,HIGH);
delayMicroseconds(10);
digitalWrite(pin_t,LOW);
time=pulseIn (pin_e,HIGH);
ultra_distance =  time / 29 / 2; 
}


void setup(){
Serial.begin(9600);// initialize serial communication at 9600 bits per second:
pinMode(led_R, OUTPUT);
pinMode(led_G, OUTPUT);
pinMode(buzzer, OUTPUT); 
//pinMode(Button, INPUT);
myservo.attach(9);
ultra_read(triggerpin_s2,echopin_s2,Binheight);delay(100);//Binheight is distance of bin from the sensor 2
}

void loop()
{ 
  
 delay(50);
  while (true){
    
    delay(800);
    long  garbage_H,percentage;
    ultra_read(triggerpin_s1,echopin_s1,dis_S);delay(200);// dis_S is distance of found object less than 20cm from the sensor 1
    ultra_read(triggerpin_s2,echopin_s2,dis_M);delay(200);//dis_M is distance of found object less than 10cm from the sensor 2
    garbage_H = Binheight - dis_M;
    
    
    Serial.print("Binheight :");
    Serial.println(Binheight); 
    
    
    if ( dis_S < 20 ) {
      myservo.write(180);
      noTone(buzzer);
      delay(50);
      if ( dis_S < 20 &&  dis_M < 10) {
         myservo.write(0);
         tone(buzzer,450);
         delay(50);
          
         }
      }
    
    else {
         myservo.write(0);
         noTone(buzzer);
         delay(50);
      }
    
    if ( dis_M < 10) {
      digitalWrite(led_R,HIGH);
      }
    else {
      digitalWrite(led_R,LOW);//
      }
      delay(50);
    if ( 10 < dis_M < Binheight) {
      digitalWrite(led_G,HIGH);
      }
    if (dis_M < 10) {
      digitalWrite(led_G,LOW);
      
      }
    percentage = map(garbage_H,0,Binheight,0,100);
    
    Serial.print("distance of person from bin is :");
    Serial.println(dis_S);
    Serial.print("distance of garbage from bintop is :");
    Serial.println(dis_M);
    Serial.print("garbage_High :");
    Serial.println(garbage_H);
    Serial.print("percentage of garbage :");
    Serial.println(percentage);
   
    delay(1000);

   if (Serial.available()){
    break;
   }
  }

  int state = Serial.parseInt();
  if (state == 1){
    myservo.write(180);
    
    delay(10000);
  }
  
    
    
  
}
