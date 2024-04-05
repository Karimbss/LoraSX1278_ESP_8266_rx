#include <SPI.h>
#include <LoRa.h>
#define led 14
const int csPin = 15;         // LoRa chip select   GPIO15(D8)->SS or chip select
const int resetPin = 2;       // LoRa reset         GPIO2(D4)->RESET OF Lora module
const int DIO0Pin = 0;         // LoRa IRQ (Callback)      GPIO0 (D3) -> IRQ or "Callback"
volatile bool doRead = false; // Flag set by callback to perform read process hand interrupt main loop

void setup() 
{
  SPI.begin();
  LoRa.setPins(csPin, resetPin, DIO0Pin); // set CS, reset, IRQ pin. Override the default CS, reset, and IRQ pins (optional)
  Serial.begin(9600);
  delay(1000);
  while (!Serial);
  Serial.println("LoRa Receiver IRQ");
  Serial.flush();
  while (!LoRa.begin(433E6)) {
    Serial.print(".");
    delay(500);
  }

  // LoRa.setSyncWord(0xF3); // syncword default or private: 0x12; LoRaWAN/TTN: 0x34
  // LoRa.setTxPower(20);

  Serial.println("LoRa Initializing OK!");
  // trigger interrupt on pin 2 (INT0) (Arduino) or GPIO0 (D3) on ESP8266 (NodeMCU) from DIO0
  // register the receive callback
  //LoRa.onReceive(onReceive);
  // put the radio into receive mode
 // LoRa.receive();
}

void loop() 
{ 
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet: '");

    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
  

}

