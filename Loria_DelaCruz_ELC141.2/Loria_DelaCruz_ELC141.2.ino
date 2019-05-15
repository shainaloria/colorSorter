#include <Servo.h>
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
Servo topServo;
Servo bottomServo;
int frequency = 0;
int color = 0;

void setup()
{
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  topServo.attach(2);
  bottomServo.attach(3);
  Serial.begin(9600);
}

void loop() 
{
  topServo.write(115);          //brings the skittle from the feeder to the color sensor
  delay(500);

  for (int i = 115; i > 65; i--) 
  {
    topServo.write(i);
    delay(2);
  }
  delay(500);

  color = readColor();
  delay(10);
  switch (color)              //servo with slide attached to it
  {
    case 1:                   
      bottomServo.write(50);    //RED
      break;
    case 2:
      bottomServo.write(80);    //ORANGE
      break;
    case 3:
      bottomServo.write(110);   //GREEN
      break;
    case 4:
      bottomServo.write(140);   //YELLOW
      break;
    case 5:
      bottomServo.write(180);   //VIOLET
      break;
    case 0:
      break;
  }
  delay(300);

  for (int i = 65; i > 29; i--)  //aligns the hole to the slide
  {
    topServo.write(i);
    delay(5);
  }
  delay(1000);

  for (int i = 29; i < 115; i++)
  {
    topServo.write(i);
    delay(5);
  }
  color = 0;
}

// returns color detected
int readColor()
{
  // reading red filtered photodiodes 
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;

  // Printing the value on the serial monitor
  Serial.print("R= ");          //printing name
  Serial.print(frequency);      //printing RED color frequency
  Serial.print("  ");
  delay(50);

  // reading green filtered photodiodes
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;

  // Printing the value on the serial monitor
  Serial.print("G= ");          //printing name
  Serial.print(frequency);      //printing GREEN color frequency
  Serial.print("  ");
  delay(50);

  // reading blue filtered photodiodes
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;

  // Printing the value on the serial monitor
  Serial.print("B= ");        //printing name
  Serial.print(frequency);    //printing BLUE color frequency
  Serial.println("  ");
  delay(50);
  
  // Red
  if (R<101 & R>89 & G<150 & G>120 & B<110 & B>90) 
  {
    color = 1; 
    Serial.println("red");
  }

  // Orange
  else if (R<85 & R>60 & G<130 & G>95 & B<110 & B>85) 
  {
    color = 2; 
    Serial.println("orange");
  }

  // Green
  else if (R<125 & R>100 & G<110 & G>85 & B<105 & B>85) 
  {
    color = 3; 
    Serial.println("green");
  }

  // Yellow
  else if (R<80 & R>55 & G<85 & G>70 & B<90 & B>70) 
  {
    color = 4; 
    Serial.println("yellow");
  }

  // Violet
  else if (R<145 & R>130 & G<150 & G>130 & B<115 & B>95 ) 
  {
    color = 5; 
    Serial.println("violet");
  }
  return color;
}
