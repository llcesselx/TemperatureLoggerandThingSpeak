#include <Ethernet.h>
#include "secrets.h"
#include "ThingSpeak.h"

#define W5100_CS 10
#define SDCARD_CS 4

int keyIndex = 0;

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

// IPAddress ip(Ethernet.localIP());
// IPAddress myDns(Ethernet.dnsServerIP());

// Works at home:
// IPAddress ip(192, 168, 0, 177);
// IPAddress myDns(192, 168, 0, 1);

EthernetClient client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

int tempPin = 0;
int btn = 8;
int num = 0;

void setup()
{
  Ethernet.init(10);
  Serial.begin(115200);

  pinMode(btn, INPUT);

  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH);
  Ethernet.init(W5100_CS);

  while (!Serial) {
    ;
  }
  Serial.println("Initialize Ethernet with DHCP...");

  int code = Ethernet.begin(mac);

  if (code == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found. Cannot run without hardware...");
      while (true) {
        delay(1);
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected...");
    }
  }
  else {
    Serial.print("DHCP assigned IP: ");
    Serial.println(Ethernet.localIP());
  }
  delay(1000);

  ThingSpeak.begin(client);
}

void loop()
{
  int tempReading = analogRead(tempPin);
  // This is OK
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  float tempC = tempK - 273.15;            // Convert Kelvin to Celcius
  float tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  /*  replaced
    float tempVolts = tempReading * 5.0 / 1024.0;
    float tempC = (tempVolts - 0.5) * 10.0;
    float tempF = tempC * 9.0 / 5.0 + 32.0;
  */

  Serial.print(tempC);
  Serial.println(" C");
  Serial.print(tempF);
  Serial.println(" F");

  int val = digitalRead(btn);

  if (val == 1){
    // String newTemp = tempF + 'F';
    ThingSpeak.setField(3, tempF);
  }
  if (val == 0){
    // String newTemp = tempC + 'C';
    ThingSpeak.setField(3, tempC);
  }

  ThingSpeak.setField(1, tempF);
  ThingSpeak.setField(2, tempC);

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200){
    Serial.println("Channel update successful.");
  }
  else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  Ethernet.maintain();
  delay(5000);
}
