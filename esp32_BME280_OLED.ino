#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_BME280.h>

// Wokwi Constructor
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 21, /* data=*/ 22);   // ESP32 Thing, HW I2C with pin remapping

// Arduino Constructors with Xiao
//U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Arduino ESP32 DEVKIT
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

Adafruit_BME280 bme; // I2C

#define SEALEVELPRESSURE_HPA (1013.25)
unsigned long delayTime = 1000;

void setup() {
  Serial.begin(9600);

  // Start BME280
  if (! bme.begin(0x76, &Wire)) {
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
      while (1);
  }

  //Screen Setup
  u8g2.begin();
  u8g2.setFontMode(1);  //activate transparent font mode
  u8g2.setDrawColor(2);
  u8g2.setFont(u8g2_font_7x13_t_cyrillic); // 9 Pixel Height

}

void loop() {
  // Get the Data
  float temp = bme.readTemperature() * 9/5 + 32;
  float rh = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;
  float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA) * 3.281;

  //Screen Loop
  u8g2.clearBuffer();
  u8g2.setCursor(0, 10);
  u8g2.print("    BME280 Data");

  u8g2.setCursor(0, 22);
  u8g2.print("    Temp: ");
  u8g2.print(temp, 1);
  u8g2.print("f");

  u8g2.setCursor(0, 34);
  u8g2.print("      RH: ");
  u8g2.print(rh, 1);
  u8g2.print("%");

  u8g2.setCursor(0, 46);
  u8g2.print("Pressure: ");
  u8g2.print(pressure, 1);
  u8g2.print("hPa");

  u8g2.setCursor(0, 58);
  u8g2.print("Altitude: ");
  u8g2.print(altitude, 1);
  u8g2.print("'");
    
  u8g2.sendBuffer();
  delay(delayTime);

}
