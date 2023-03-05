#include <WiFi.h>
#include <DNSServer.h>

#include <Wire.h>
#include <Adafruit_BME280.h>

//network credentials
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

const byte DNS_PORT = 53;
IPAddress apIP(8,8,4,4); // The default android DNS
DNSServer dnsServer;
WiFiServer server(80);

// BME280 I2C
Adafruit_BME280 bme;
#define SEALEVELPRESSURE_HPA (1013.25)

/*
String responseHTML = ""
  "<!DOCTYPE html><html><head><title>CaptivePortal</title></head><body>"
  "<h1>Hello World!</h1><p>This is a captive portal example. All requests will "
  "be redirected here.</p></body></html>";
 */

void setup() { 
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  //WiFi.softAP("ESP32-DNSServer");
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  server.begin();

  // Start BME280
  if (! bme.begin(0x76, &Wire)) {
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
      while (1);
  }
}

void loop() {
  dnsServer.processNextRequest();
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            //client.print(responseHTML);
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the table 
            client.println("<style>body { text-align: center; font-family: Verdana;}");
            client.println("table { border-collapse: collapse; width:35%; margin-left:auto; margin-right:auto; }");
            client.println("th { padding: 12px; background-color: #0043af; color: white; }");
            client.println("tr { border: 1px solid #ddd; padding: 12px; }");
            //client.println("tr:hover { background-color: #bcbcbc; }");
            client.println("td { border: none; padding: 12px; }");
            client.println(".sensor { color:black; font-weight: bold; padding: 1px; }");
            
            // Web Page Heading
            client.println("</style></head><body><h1>Weather Data</h1>");
            client.println("<table><tr><th>MEASUREMENT</th><th>VALUE</th></tr>");
            
            //client.println("<tr><td>Temp. Celsius</td><td><span class=\"sensor\">");
            //client.println(bme.readTemperature(), 1);
            //client.println(" *C</span></td></tr>");  
            
            client.println("<tr><td>Temp.</td><td><span class=\"sensor\">");
            client.println(1.8 * bme.readTemperature() + 32, 1);
            client.println("&#8457;</span></td></tr>");

            client.println("<tr><td>Humidity</td><td><span class=\"sensor\">");
            client.println(bme.readHumidity(), 1);
            client.println(" %</span></td></tr>");
            
            client.println("<tr><td>Pressure</td><td><span class=\"sensor\">");
            client.println(bme.readPressure() / 100.0F, 1);
            client.println("hPa</span></td></tr>");
            
            client.println("<tr><td>Approx. Altitude</td><td><span class=\"sensor\">");
            client.println(bme.readAltitude(SEALEVELPRESSURE_HPA) * 3.281, 1);
            //client.println("'</span></td></tr>"); 
            
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
  }
}
