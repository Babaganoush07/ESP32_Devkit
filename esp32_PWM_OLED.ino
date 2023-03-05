#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

// Wokwi Constructor
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 21, /* data=*/ 22);   // ESP32 Thing, HW I2C with pin remapping

// Arduino Constructors with Xiao
//U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Arduino ESP32 DEVKIT
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

const int channel = 0;
const int frequency = 1000;
const int resolution = 8;

int brightness = 0;
int fadeAmount = 5;
int wait = 1000;

void setup() {
  // PWM Setup
  ledcSetup(channel,frequency,resolution);
  ledcAttachPin(LED_BUILTIN,channel);

  //Screen Setup
  u8g2.begin();
  u8g2.setFontMode(1);  //activate transparent font mode
  u8g2.setDrawColor(2);
  u8g2.setFont(u8g2_font_7x13_t_cyrillic); // 9 Pixel Height

} // END setup()

void loop() {
  
  // PWM Stuff
  ledcWrite(channel, brightness);
  brightness = brightness + fadeAmount;
  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  } // END if
  
  int lineX = map(brightness, 0, 255, 1, 126);

  //Screen Loop
  u8g2.clearBuffer();
  u8g2.setCursor(0, 10);
  u8g2.print("LED PWM Brightness");

  u8g2.setCursor(10, 20);
  u8g2.print(brightness);

  u8g2.drawLine(1, 25, 126, 25); // Horizontal -
  u8g2.drawLine(0, 21, 0, 29); // Left  |
  u8g2.drawLine(127, 21, 127, 29); // Right |
  u8g2.drawLine(lineX, 21, lineX, 29); // Moving |
  
  u8g2.sendBuffer();
  delay(wait);
  
} // END loop()
