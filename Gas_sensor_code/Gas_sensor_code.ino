/* MQ-8 Hydrogen Gas Sensor Circuit with Arduino */

const int AOUTpin = 0; //the AOUT pin of the hydrogen sensor goes into analog pin A0 of the arduino
const int DOUTpin = 8; //the DOUT pin of the hydrogen sensor goes into digital pin D8 of the arduino
//const int ledPin = 13; //the anode of the LED connects to digital pin D13 of the arduino

int limit;
int value;

void setup() {
  Serial.begin(115200);//sets the baud rate
  pinMode(DOUTpin, INPUT);//sets the pin as an input to the arduino
  //pinMode(ledPin, OUTPUT);//sets the pin as an output of the arduino
}

void loop()
{
  value = analogRead(AOUTpin); //reads the analaog value from the hydrogen sensor's AOUT pin
  limit = digitalRead(DOUTpin); //reads the digital value from the hydrogen sensor's DOUT pin
  Serial.print("Hydrogen value: ");
  Serial.println(value);//prints the hydrogen value
  Serial.print("Limit: ");
  Serial.print(limit);//prints the limit reached as either LOW or HIGH (above or underneath)
  delay(100);
  if (limit == HIGH) {
    //digitalWrite(ledPin, HIGH);//if limit has been reached, LED turns on as status indicator
    Serial.println("Status : On"); 
  }
  else {
    //digitalWrite(ledPin, LOW);//if threshold not reached, LED remains off
    Serial.println("Status : Off"); 
  }
}
