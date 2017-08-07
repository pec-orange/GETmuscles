#include <Wire.h>
#include <Servo.h>

#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>

#define  LED_PIN       13

AndroidAccessory acc("Shen dev. std.",
         "GETplatform",
         "DemoKit Arduino Board",
         "1.0",
         "http://www.android.com",
         "0000000012345678");
bool connected = false;
void setup();
void loop();


//void init_leds()
//{
//	digitalWrite(LED_RED, 1);
//	pinMode(LED_RED, OUTPUT);
//}

void setup()
{
	Serial.begin(115200);
	Serial.println("Start");
	//init_leds();
  pinMode(LED_PIN, OUTPUT);
	acc.powerOn();
 
  connected = acc.isConnected();
}

void loop()
{
	byte msg[4];
  //Serial.println(connected);
	if (acc.isConnected()) {
		int len = acc.read(msg, sizeof(msg), 1);
    
		if (len > 0) {
			// assumes only one command per packet
      Serial.print("Received packet: ");
      Serial.print(msg[0]); 
      Serial.print(" "); 
      Serial.print(msg[1]); 
      Serial.print(" "); 
      Serial.print(msg[2]); 
      Serial.print(" "); 
      Serial.println(msg[3]); 
			if (msg[0] == 0x18) {
        if (msg[3] == 0) {
          digitalWrite(LED_PIN, LOW);
          Serial.println("LED OFF");
        }
        else {
          digitalWrite(LED_PIN, HIGH);
          Serial.println("LED ON"); 
        }
			} 
		}
	} 

  if (Serial.available() > 0) {
    byte buff[1];
    buff[0] = Serial.read();
    if (acc.isConnected()) {
      acc.write(buff, 1);
    }
  
  }
	delay(100);
}
