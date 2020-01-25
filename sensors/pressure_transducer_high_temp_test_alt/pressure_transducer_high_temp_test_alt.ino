#include "max6675.h"

//Define variables
unsigned long time;
float actualtemp_ext = 0;
float actualtemp_int = 0;
float actualtemp_int2 = 0;
float thermocouple1_offset = 0; //+0 deg. C offset
float thermocouple2_offset = 0; //+0 deg. C offset
float thermocouple3_offset = 0; //+0 deg. C offset
float templimit_ext = 500;
float templimit_int = 400;

// Pressure transducer pins
const int analogPin = A0; // input connected to analog pin 0
float inPin;        // variable to store the read value
float val = 0;      // variable to store the read value

//Relay Pin Definitions
int relaytrigger = 2;

//Thermocouple 1 Pin Definitions
int thermoDO1 = 8;            // SO pin on HW-550 board
int thermoCS1 = 6;            // CS pin (PWM)
int thermoCLK1 = 5;           // SCK pin (PWM)
//int vccPin1 = 6;              // choose pin for vcc
//int gndPin1 = 7;              // choose pin for gnd

//Thermocouple 2 Pin Definitions
int thermoDO2 = 9;            // SO pin on HW-550 board
int thermoCS2 = 6;            // CS pin (PWM)
int thermoCLK2 = 5;           // SCK pin (PWM)
////int vccPin2 = 24;              // choose pin for vcc
////int gndPin2 = 22;              // choose pin for gnd

//Thermocouple 3 Pin Definitions
int thermoDO3 = 10;            // SO pin on HW-550 board
int thermoCS3 = 6;            // CS pin (PWM)
int thermoCLK3 = 5;           // SCK pin (PWM)
//int vccPin3 = 6;              // choose pin for vcc
//int gndPin3 = 7;              // choose pin for gnd

MAX6675 thermocouple1(thermoCLK1, thermoCS1, thermoDO1);      //defining MAX6675
MAX6675 thermocouple2(thermoCLK1, thermoCS1, thermoDO2);      //defining MAX6675
MAX6675 thermocouple3(thermoCLK1, thermoCS1, thermoDO3);      //defining MAX6675

void setup() {
  Serial.begin(9600);

  // For Relay
  pinMode(relaytrigger, OUTPUT);  

  // For thermocouple 1
  // pinMode(vccPin1, OUTPUT); digitalWrite(vccPin1, HIGH); //set pin as a 5V vcc
  // pinMode(gndPin1, OUTPUT); digitalWrite(gndPin1, LOW);  //set pin as a gnd
  
  // For thermocouple 2
  // pinMode(vccPin2, OUTPUT); digitalWrite(vccPin2, HIGH); //set pin as a 5V vcc
  // pinMode(gndPin2, OUTPUT); digitalWrite(gndPin2, LOW);  //set pin as a gnd

  // wait for MAX chip to stabilize
  delay(500);

}

void loop() {
  inPin = analogRead(analogPin);   // read the input pin
  val = (((inPin - 101)*30)/(922-101));
  /* 
  1024 bits for arduino input, multiplication factor is 30 as transducer reads 0 to 30 PSI
  0.5 volts is an analog reading of 101  (rounded) for 0 PSI i.e. aprrox. 0.0-0.5v = 0 PSI
  4.5 volts is an analog reading of 922  (rounded) for 30 PSI i.e. aprroX. 4.5-5.0v = 30 PSI
  so the formula is Pressure (PSI) = ( Analog Reading - 101 ) * 30 /  ( 922 - 101 )
  */
  Serial.print("\t");
  Serial.print("Pressure Value (PSI) = "); 
  Serial.println(val);
  Serial.print("\t");

  actualtemp_ext = (thermocouple1.readCelsius()) - thermocouple1_offset;
  Serial.print("External Temp C = ");
  Serial.println(actualtemp_ext);
  Serial.print("\t");
  if (actualtemp_ext < templimit_ext) //Temperature Comparison
  {
    actualtemp_int = (thermocouple2.readCelsius()) - thermocouple2_offset;
    Serial.print("Internal Temp C = ");
    Serial.println(actualtemp_int);
    Serial.print("\t");
    actualtemp_int2 = (thermocouple3.readCelsius()) - thermocouple3_offset;
    Serial.print("Internal Temp2 C = ");
    Serial.println(actualtemp_int2);
    Serial.print("\t");
    if (actualtemp_int < templimit_int) //Temperature Comparison
    {
    digitalWrite(relaytrigger,HIGH);           // Turns ON Relay
    Serial.println("Relay closed");
    Serial.print("\t");
    }
    else
    {
    digitalWrite(relaytrigger,LOW);           // Turns OFF Relay
    Serial.println("Relay open");
    Serial.print("\t");
    }
  }
  else
  {
    actualtemp_int = (thermocouple2.readCelsius()) - thermocouple2_offset;
    Serial.print("Internal Temp C = ");
    Serial.println(actualtemp_int);
    Serial.print("\t");
    actualtemp_int2 = (thermocouple3.readCelsius()) - thermocouple3_offset;
    Serial.print("Internal Temp2 C = ");
    Serial.println(actualtemp_int2);
    Serial.print("\t");
    digitalWrite(relaytrigger,LOW);           // Turns OFF Relay
    Serial.println("Relay open");
    Serial.print("\t");
  }
  Serial.print("Time: ");
  time = millis();
  Serial.println(time);
  Serial.print("\n");
  delay(500);
}