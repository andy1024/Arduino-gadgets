#include <Arduino.h>

// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
// Adapter for round trinket by Andrzej Maslowski
// github.com/andy1024

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#include <Wire.h>
#include <RTClib.h>


// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            8

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      12

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
RTC_DS3231 clock;
DateTime dt;

int delayval = 500; // delay for half a second

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  clock.begin();
  pixels.begin(); // This initializes the NeoPixel library.
//  Serial.begin(9600);
//  Serial.println(F("Clock"));
}

void loop() {

  dt = clock.now();
//  Serial.print("Raw data: ");
//  Serial.print(dt.year);   Serial.print("-");
//  Serial.print(dt.month);  Serial.print("-");
//  Serial.print(dt.day);    Serial.print(" ");
//  Serial.print(dt.hour);   Serial.print(":");
//  Serial.print(dt.minute); Serial.print(":");
//  Serial.print(dt.second); Serial.println("");

  int hour12 = dt.hour() % 12;
  int minute12 = dt.minute() / 5;
  int second12 = dt.second() / 5;
  int secondRemainder = dt.second() % 5;
  int colors[12][3] = {0};
  colors[hour12][2]+=44;
  colors[minute12][0]+=30;
  colors[second12][1]+=20 + 8*secondRemainder;
  for(int i=0;i<12;++i){
    pixels.setPixelColor(i, colors[i][0], colors[i][1], colors[i][2]);
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(delayval); // Delay for a period of time (in milliseconds).
}
