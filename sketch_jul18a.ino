#include<Servo.h>

Servo myservo;
int pos = 0;

#define ServoPin 2

#define Treshold 100

const int SensorPins[5][2] = {
    {14, 12}, //leftmost
    {15, 11}, //left
    {16, 10}, //center
    {17, 9}, //right
    {18, 8} //righmost
  };
 // analogpins A0 - A4

#define PREPROLEFT(a)  pos += a; myservo.write(pos); Serial.println("left");
#define PREPRORIGHT(a)  pos -= a; myservo.write(pos); Serial.println("right");

int i;
char sensorTriggered = '00000';
bool follow_mode = 0;
bool dir = 0;

void setup() {
  myservo.attach(ServoPin);  // put your setup code here, to run once:
  for(i = 0; i <= 4; i += 1){
    pinMode(SensorPins[1][i], OUTPUT);
    Serial.begin(9600);
    
  }
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1){
    myservo.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1){
    myservo.write(pos);
    delay(15);
  }
  // put your main code here, to run repeatedly:

  update_sensors();
  if(follow_mode == 1){
    following();
  } else{
    sentry_mode();
  }


}

void sentry_mode(){
  if(dir == 1){
    if(pos >= 180){
      pos -= 1;
      myservo.write(pos);
      dir = 0;
    } else{
      pos += 1;
      myservo.write(pos);
    }
  } else {
    if(pos <= 0){
      pos += 1;
      myservo.write(pos);
      dir = 1;
    } else{
      pos -= 1;
      myservo.write(pos);
    }

  }
}

void following(){


  
  switch(sensorTriggered) {
    //target gone
    case '00000':
        myservo.write(pos);
        follow_mode = 0;
      break;

    // target in front
    case '00100':
        myservo.write(pos);
        Serial.println("front");
      break;
    case '01110':
        myservo.write(pos);
        Serial.println("front");
      break;
    case '11111':
        myservo.write(pos);
        Serial.println("front");
      break;

    //target left
    case '01100':
      PREPROLEFT(1)
      break;
    case '11100':
      PREPROLEFT(1)
      break;
    case '11000':
      PREPROLEFT(1)
      break;
    case '10000':
      PREPROLEFT(2)
      break;

    //target right
    case '00110':
      PREPRORIGHT(1)
      break;
    case '00111':
      PREPRORIGHT(1)
      break;
    case '00011':
      PREPRORIGHT(1)
      break;
    case '00001':
      PREPRORIGHT(2)
      break;

    default:
        myservo.write(pos);
        follow_mode = 0;
      break;
  }

}


int update_sensors(){
  int SensorData_off[5];
  int SensorData_on[5];
  for(i = 0; i <= 4; i += 1){
    SensorData_off[i] = analogRead(SensorPins[1][i]);
  }
  for(i = 0; i <= 4; i += 1){
    digitalWrite(SensorPins[1][i], HIGH);
    SensorData_on[i] = analogRead(SensorPins[0][i]);
    digitalWrite(SensorPins[1][i], LOW);
  }
  for(i = 0; i <= 4; i += 1){
    if((SensorData_on[i]-SensorData_off[i]) >= Treshold){
      sensorTriggered |  (00001 << i);
    }
  }
}
