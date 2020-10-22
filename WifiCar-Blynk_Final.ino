#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
//Motor A
const int inputPin1  = 12;    // Pin 12 of L298N IC, D1 Pin of ESP32
const int inputPin2  = 13;    // Pin 12 of L298N IC, D0 Pin of ESP32
//Motor B
const int inputPin3  = 21;    // Pin  21 of L298N IC, D2 Pin of ESP32
const int inputPin4  = 22;    // Pin  22 of L298N IC, D3 Pin of ESP32
int EN1 = 14;                 // Pin 14 of L298N IC, D6 Pin of ESP32
int EN2 = 23;                 // Pin 23 of L298N IC, D5 Pin of ESP32
// Led Light Pin
const int Ledpin = 2;
//---------------

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "<your token>";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Tomato241";
char pass[] = "tomato241";

const int freq = 30000;
const int pwmChannel = 0;
const int pwmChanne2 = 1;
const int resolution = 8;
int dutyCycle = 200;

BLYNK_WRITE(V1)
{
  int x = param[0].asInt();
  int y = param[1].asInt();

  // Do something with x and y
  Serial.print("X = ");
  Serial.print(x);
  Serial.print("; Y = ");
  Serial.println(y);

//  int speed =350;
//  analogWrite(EN1, speed);//sets the motors speed
//  analogWrite(EN2, speed);//sets the motors speed
// Joystick Movement
  if (y>350)
  {
    Serial.print("forward");
    forward();
  }

  if (y<170) 
    {
      Serial.print("backward");
      backward();
    }

   if (x<132)
    {
      Serial.print("left");
      left();
    }
 
  if (x>380) 
    {
      Serial.print("right");
      right();
    }

  if ((y==256) && (x==256))
    {
      Serial.print("stop");
      stop();
     }

}

//----------------------
BLYNK_WRITE(V2)
{
  int speed = param.asInt(); // assigning incoming value from pin V2 to a variable
    //speed =350;
    ledcWrite(pwmChannel, speed);//sets the motors speed
    ledcWrite(pwmChanne2, speed);//sets the motors speed

}
//------------------------




void setup()
{
    pinMode(EN1, OUTPUT);   // where the motor is connected to
    pinMode(EN2, OUTPUT);   // where the motor is connected to
    pinMode(inputPin1, OUTPUT);
    pinMode(inputPin2, OUTPUT);
    pinMode(inputPin3, OUTPUT);
    pinMode(inputPin4, OUTPUT);  
    pinMode(Ledpin, OUTPUT);
  
  
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  ledcSetup(pwmChanne2, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(EN1, pwmChannel);
  ledcAttachPin(EN2, pwmChanne2);
  
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();

}

void left(void)
{
    digitalWrite(inputPin1, HIGH);
    digitalWrite(inputPin2, LOW);
    digitalWrite(inputPin3, HIGH);
    digitalWrite(inputPin4, LOW);  
}

void right(void)
{
    digitalWrite(inputPin1, LOW);
    digitalWrite(inputPin2, HIGH);
    digitalWrite(inputPin3, LOW);
    digitalWrite(inputPin4, HIGH); 
}

void stop(void)
{ 
    digitalWrite(inputPin1, LOW);
    digitalWrite(inputPin2, LOW);
    digitalWrite(inputPin3, LOW);
    digitalWrite(inputPin4, LOW); 
}

void backward(void)
{   
    digitalWrite(inputPin1, LOW);
    digitalWrite(inputPin2, HIGH);
    digitalWrite(inputPin3, HIGH);
    digitalWrite(inputPin4, LOW); 
}

void forward(void)
{ 
    digitalWrite(inputPin1, HIGH);
    digitalWrite(inputPin2, LOW);
    digitalWrite(inputPin3, LOW);
    digitalWrite(inputPin4, HIGH); 
}
