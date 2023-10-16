#include <BluetoothSerial.h>


BluetoothSerial SerialBT;
byte BTData;
/* Check if Bluetooth configurations are enabled in the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


const int trigPin = 32;
const int echoPin = 33;
const int buzzer = 25;
const int ldrPin = 34;
const int LED = 26;

long duration;
int distance;
int ldrValue = 0;

unsigned long last_time = 0;
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 400;           // interval at which to blink (milliseconds)
int ledState = LOW;             // ledState used to set the LED
int buzzerState = LOW;             // buzzerState used to set the buzzer


void setup() {
//Determining the state of the pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(LED, OUTPUT);

//At first, the buzzer turns on and off only twice

  digitalWrite(buzzer,HIGH);
  delay(300);
  digitalWrite(buzzer,LOW);
  delay(300);
  digitalWrite(buzzer,HIGH);
  delay(300);
  digitalWrite(buzzer,LOW);

 // Starts the serial communication
  Serial.begin(115200);
  SerialBT.begin();
}
void loop() {
  if(SerialBT.available())
    {
      BTData = SerialBT.read();
        if(BTData == '1')
          {
             digitalWrite(buzzer,HIGH);
              delay(150);
              digitalWrite(buzzer,LOW);
              delay(150);
              digitalWrite(buzzer,HIGH);
              delay(150);
              digitalWrite(buzzer,LOW);
              delay(150);
              digitalWrite(buzzer,HIGH);
              delay(150);
              digitalWrite(buzzer,LOW);
              delay(150);
              digitalWrite(buzzer,HIGH);
              delay(150);
              digitalWrite(buzzer,LOW);
            BTData = 0;
          }
    }
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.03432 / 2;
  //If the distance is between 90 and 61
  if(distance<=90 && distance>=61)
    {
      //The buzzer turns off and on every 200 ms
      if(millis()-last_time>=200)
        {
          last_time=millis();
          if (buzzerState == LOW) {
              buzzerState = HIGH;
            } 
            else {
              buzzerState = LOW;

            }

            digitalWrite(buzzer, buzzerState);
        }
    }

    //If the distance is between 60 and 31
    else if(distance<=60 && distance>=31)
    {
      //The buzzer turns off and on every 80 ms
      if(millis()-last_time>=80)
        {
          last_time=millis();
          if (buzzerState == LOW) {
              buzzerState = HIGH;
            } 
            else {
              buzzerState = LOW;

            }

            digitalWrite(buzzer, buzzerState);
        }
    }

    //If the distance is less than 30
    else if(distance<=30)
      {
        //The buzzer is turned on and the message is sent to the phone
        digitalWrite(buzzer,HIGH);
        if(millis()-last_time>=500)
          {
             last_time=millis();
             SerialBT.print("0");
          }
      }

  //And if there are none, the buzzer is off
  else
    {
      digitalWrite(buzzer,LOW);
    }


  //The value of the LDR is read every 400 ms
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time the ADC
    previousMillis = currentMillis;
    ldrValue = analogRead(ldrPin);
    if(ldrValue>=3800)
      {
            if (ledState == LOW) {
              ledState = HIGH;
            } 
            else {
              ledState = LOW;
            }

            // set the LED with the ledState of the variable:
            digitalWrite(LED, ledState);
      }
    else
      digitalWrite(LED, LOW);

   //Prints distance & LDR on the Serial Monitor     
    Serial.print(ldrValue);
    Serial.print("         Distance: ");
    Serial.println(distance);
  }


}
