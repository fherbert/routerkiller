#include <Arduino.h>
#include <WiFiManager.h>
#include <ESP8266WiFi.h>

// put function declarations here:
//int myFunction(int, int);
WiFiManager wifiManager;
WiFiClient client;
int pingfailcount = 0;
int reboottimout = 0;

void setup() {
  // put your setup code here, to run once:
 // int result = myFunction(2, 3);
 Serial.begin(9600);
 wifiManager.autoConnect("itronCAM-AP", "password");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (client.connect("www.google.co.nz", 80)) {   //check to see if the router can connect to Google
    pingfailcount = 0;
    Serial.println("Connection successful");
    delay(10000);
  } else {
    pingfailcount++;
    Serial.printf("Connection Unsuccessful, number of failures: %d\n", pingfailcount);
    delay(10000);
    if (pingfailcount > 10) {
      Serial.println("10 failures in a row, rebooting power");
      // turn off router power
      // restart esp
      if (reboottimout++ > 20) {
        ESP.reset();
      }
    }
  }
}

// put function definitions here:
//int myFunction(int x, int y) {
//  return x + y;
//}