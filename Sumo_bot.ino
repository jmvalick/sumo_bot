#include <NewPing.h>

int IRSensor = 2;
int LED = 13;

int mot1F = 9;
int mot1B = 8;
int mot1E = 10;
int mot2F = 7;
int mot2B = 6;
int mot2E = 5;

int sonarTrig = 11;
int sonarEcho = 12;
NewPing sonarSensor(sonarTrig, sonarEcho, 1000);

void forward(){               //fucntion to move forwards
   digitalWrite(mot1F,HIGH);
   digitalWrite(mot1B,LOW);
   digitalWrite(mot2F,HIGH);
   digitalWrite(mot2B,LOW);
  }
void backward(){             //fucntion to move backwards
  digitalWrite(mot1F,LOW);
  digitalWrite(mot1B,HIGH);
  digitalWrite(mot2F,LOW);
  digitalWrite(mot2B,HIGH);
  }
void turn(String direction){ //function to turn right or left
  if(direction == "right"){
    digitalWrite(mot1F,HIGH);
    digitalWrite(mot1B,LOW);
    digitalWrite(mot2F,LOW);
    digitalWrite(mot2B,HIGH);
  }
  if(direction == "left"){
    digitalWrite(mot1F,HIGH);
    digitalWrite(mot1B,LOW);
    digitalWrite(mot2F,LOW);
    digitalWrite(mot2B,HIGH);
  }
}

void setup(){

  Serial.begin(9600);
  
  pinMode (IRSensor, INPUT);
  pinMode (LED, OUTPUT);
  digitalWrite(mot1E, HIGH);
  digitalWrite(mot2E, HIGH);

}

void loop(){
  Serial.print("refresh:   ");
  int IRout = digitalRead(IRSensor); //Creates a variable that will constantly hold the value of IR sensor ( 1 or 0)
  Serial.print(IRout);
  int distance = sonarSensor.ping_cm();      //variable to hold distance
  Serial.print("    ");
  Serial.println(distance);
  
  if (IRout == 0){//IR Sensor detects ring
    Serial.println("ring detected");
    digitalWrite(LED, HIGH);
    backward();      //back up
    delay(1000);
    turn("right");   //turn around
    delay(2000);
  }

  digitalWrite(LED, LOW);
  turn("right");               //scan the field                     
  while(distance < 80){       //if robaot is detected move forward
    Serial.println("robot detected");
    Serial.println(distance);
    forward(); 
    distance = sonarSensor.ping_cm();
    delay(100);
    }
    delay(100);
}
