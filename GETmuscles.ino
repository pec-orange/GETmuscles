#include <Wire.h>
#include <Servo.h>
#include <Multiservo.h>

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

Multiservo servoArray[18];
int servoAngle[18];


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

  for (int i = 0; i < 18; i++) {
    servoArray[i].attach(i);
    servoAngle[i] = 0;
  }
}

void loop()
{

  for (int i = 0; i < 18; i++)
  {
//    if (servoAngle[i] != 0)
//      servoArray[i].write(servoAngle[i]);
  }
  
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
        if (msg[1] == 0x24) {
            servoAngle[msg[2]] = msg[3];
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
	//delay(100);
}
