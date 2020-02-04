// Copyright 2020 Azusa Pacific Univeristy

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "MtRbW-_U8kseq4O3oT_saH_PEJaXtYCh"; // put your auth token here

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "APU-MYDEVICES";
char pass[] = "";



// the number of the LED pin
const int ledPin = 25;

// setting PWM properties
const int freq = 5000;
const int resolution = 10;

// see https://github.com/blynkkk/blynk-library/blob/master/examples/GettingStarted/PushData/PushData.ino
BlynkTimer timer;

void myTimerEvent()
{
  int light = analogRead(10);
  Blynk.virtualWrite(V3, light);
  Serial.print("light value is ");
  Serial.println(light);
}


BLYNK_WRITE(V0)
{
  int pinData = param.asInt(); 
  pinData=map(pinData, 0, 1023, 1023, 0);
  ledcWrite(0, pinData);
  Serial.print("V0 Slider value is: ");
  Serial.println(pinData);
}

BLYNK_WRITE(V1)
{
  int pinData = param.asInt(); 
  pinData=map(pinData, 0, 1023, 1023, 0);
  ledcWrite(1, pinData);
  Serial.print("V1 Slider value is: ");
  Serial.println(pinData);
}


BLYNK_WRITE(V2)
{
  int pinData = param.asInt(); 
  pinData=map(pinData, 0, 1023, 1023, 0);
  ledcWrite(2, pinData);
  Serial.print("V2 Slider value is: ");
  Serial.println(pinData);
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  // https://randomnerdtutorials.com/esp32-pwm-arduino-ide/
  ledcSetup(0, freq, resolution);
  ledcSetup(1, freq, resolution);
  ledcSetup(2, freq, resolution);
  
  ledcAttachPin(25, 0);
  ledcAttachPin(26, 1);
  ledcAttachPin(27, 2);

  Blynk.begin(auth, ssid, pass);

  timer.setInterval(1 * 1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
  int light = analogRead(4);
  
}






// from Blynk Blink sketch:
/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  You’ll need:
   - Blynk App (download from AppStore or Google Play)
   - ESP32 board
   - Decide how to connect to Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  There is a bunch of great example sketches included to show you how to get
  started. Think of them as LEGO bricks  and combine them as you wish.
  For example, take the Ethernet Shield sketch and combine it with the
  Servo example, or choose a USB sketch and add a code from SendData
  example.
 *************************************************************/
