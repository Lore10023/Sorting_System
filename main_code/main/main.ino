#include <Servo.h>

const int S0 = 4; // PINI SENZOR CULOARE  
const int  S1 = 5;
const int  S2 = 6;
const int  S3 = 7;
const int  sensorOut = 9; //PWM

const int ir_red = 2; // PIN IR
int SensorState = 0;
int LastSensorState = 0;

Servo servo_red; // PIN SERVO

const int motor_pin1 =8;// PINI MOTOR
const int motor_pin2 = 12;
const int motor_enable = 3;  //PWM  

bool red_aprins = false;
bool green_aprins = false;
bool blue_aprins = false;

int red = 0;
int green = 0;
int blue = 0;

int color = 0;

int counter = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  pinMode(motor_enable, OUTPUT);
  pinMode(motor_pin1, OUTPUT);
  pinMode(motor_pin2, OUTPUT);

  pinMode(ir_red, INPUT);
  
  servo_red.attach(11);


  Serial.begin(9600);
}

void loop() {
  digitalWrite(motor_pin1, HIGH);
  digitalWrite(motor_pin2, LOW);
  analogWrite(motor_enable, 125);

  readColor();


  
  switch(color){
    case 1: {   //actionare servo-motor pentru cubul rosu
      SensorState = digitalRead(ir_red);
      if(SensorState != LastSensorState){
        if(SensorState == LOW){
          digitalWrite(motor_pin1, HIGH);
          digitalWrite(motor_pin2, HIGH);
          delay(200);
          servo_red.write(180);
          delay(2000);
          servo_red.write(0);
          color = 0;
        }
        delay(50);
      }
      LastSensorState = SensorState;
    }
    break;
    case 2:  {    //actionare servo-motor pentru cubul verde
      SensorState = digitalRead(ir_red);
      if(SensorState != LastSensorState){
        if(SensorState == LOW){
          digitalWrite(motor_pin1, HIGH);
          digitalWrite(motor_pin2, HIGH);
          delay(200);
          servo_red.write(0);
          delay(2000);
          servo_red.write(180);
          color = 0;
        }
        delay(50);
      }
      LastSensorState = SensorState;
    }

    case 0: break;
  }
 
}

  //Setting RED
int readColor() {
  
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  red = pulseIn(sensorOut, LOW);


  //Setting GREEN
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  green = pulseIn(sensorOut, LOW);


  
  //Setting BLUE
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blue = pulseIn(sensorOut, LOW);

  Serial.print(" R = ");
  Serial.print(red);

  Serial.print(" G = ");
  Serial.print(green);

  Serial.print(" B = ");
  Serial.print(blue);
  Serial.print("\n");


  if(red>100 && blue>130 && green > 125){
    red_aprins = false;
    green_aprins = false;
    blue_aprins = false;
    Serial.print("UNDETECTED");
  }
  else if(red < blue && red < green){ //detectare rosu red > 0 && red < 36 && green > 180 && green < 215 && blue > 36 && blue <55
    Serial.print("RED");
    color = 1;
    if(!red_aprins){ //controleaza sa nu se opreasca la culoarea constanta, si sa se opreasca doar odata;
      digitalWrite(motor_pin1, HIGH); //oprire motor
      digitalWrite(motor_pin2, HIGH);
      red_aprins = true;
      delay(1000);
      servo_red.write(0);
      delay(1000); // asteapta 2 secunde sub senzor
      digitalWrite(motor_pin1, HIGH);
      digitalWrite(motor_pin2, LOW);
      analogWrite(motor_enable, 125);
    }
  }
   else if(green < red && green < blue){ //detectare verde red > 117 && red < 139 && green > 74 && green < 95 && blue > 28 && blue <40
    Serial.print("GREEN");
    color = 2;
    if(!green_aprins){
      digitalWrite(motor_pin1, HIGH);
      digitalWrite(motor_pin2, HIGH);
      green_aprins = true;
      delay(1000);
      servo_red.write(180);
      delay(1000);
      digitalWrite(motor_pin1, HIGH);
      digitalWrite(motor_pin2, LOW);
      analogWrite(motor_enable, 125);
    }
  }
  else if(blue < red && blue < green){ //detectare albastru red > 50 && red < 60 && green > 25 && green < 40 && blue > 15 && blue <35
    Serial.print("BLUE");
    if(!blue_aprins){
      digitalWrite(motor_pin1, HIGH);
      digitalWrite(motor_pin2, HIGH);
      blue_aprins = true;
      delay(2000);
      digitalWrite(motor_pin1, HIGH);
      digitalWrite(motor_pin2, LOW);
      analogWrite(motor_enable, 125);
    }

  }else{
    Serial.print("UNDETECTED");
  }

  return color;
}


