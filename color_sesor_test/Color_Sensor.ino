const int S0 = 4;
const int  S1 = 5;
const int  S2 = 6;
const int  S3 = 7;
const int  sensorOut = 9;

int red = 0;
int green = 0;
int blue = 0;
int clear = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);
}

void loop() {
  //CLEAR
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  clear = pulseIn(sensorOut, LOW);


  //Setting RED
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



//  red = map(red,200,0,0,255);
//  green = map(green,200,0,0,255);
//  blue = map(blue,200,0,0,255);


  Serial.print(" R = ");
  Serial.print(red);
  delay(100);
  Serial.print(" G = ");
  Serial.print(green);
  delay(100);
  Serial.print(" B = ");
  Serial.print(blue);
  delay(100);
  Serial.print("\n");

  if(red>100 && blue>130 && green > 125){
      Serial.print("UNDETECT");
  }
  else if(red < blue && red < green){ //detectare rosu red > 0 && red < 36 && green > 180 && green < 215 && blue > 36 && blue <55
    Serial.print("RED");
    delay(100);
  }
   else if(green < red && green < blue){ //detectare verdred > 117 && red < 139 && green > 74 && green < 95 && blue > 28 && blue <40
    Serial.print("GREEN");
        delay(100);
  }
  else if(blue < red && blue < green){ //detectare albastru red > 50 && red < 60 && green > 25 && green < 40 && blue > 15 && blue <35
    Serial.print("BLUE");
        delay(100);

  }else{
    Serial.print("UNDETECT");
  }
}
