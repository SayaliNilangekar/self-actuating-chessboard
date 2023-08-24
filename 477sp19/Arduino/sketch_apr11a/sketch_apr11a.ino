#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80


void initWiFiConnection()
{

  int status = WL_IDLE_STATUS;
  // initialize ESP module
  WiFi.init(&amp;SoftSerial);

  delay(3000);



  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {



    WiFi.reset();

    // Connect to WPA/WPA2 network
    Serial.print(F("ssid="));
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);



    Serial.println(F("after WiFi.begin-----------------------&gt;"));
  }
}


and in setup()

 // Setup WiFI

  // initialize serial for ESP module
  SoftSerial.begin(115200);

  SoftSerial.println("AT+RST");
  Serial.println("AT+RST");
  char value;
  while (SoftSerial.available()) {
    value = SoftSerial.read();
    Serial.println(value);

  }

  SoftSerial.println(F("AT"));
  Serial.println(F("AT"));
  delay(1000);

  while (SoftSerial.available()) {
    value = SoftSerial.read();
    Serial.println(value);

  }

  // Baud rates above about 38,000 do not work reliably on the 328p (Pro Mini)

  Serial.println(F("AT+UART_DEF=19200,8,1,0,0"));
  SoftSerial.println(F("AT+UART_DEF=19200,8,1,0,0"));
  delay(1000);


  while (SoftSerial.available()) {
    value = SoftSerial.read();
    Serial.println(value);

  }

  // Restart SoftwareSerial for the slower baud rate for the WiFi

  SoftSerial.end();
  SoftSerial.begin(19200);



  initWiFiConnection();
