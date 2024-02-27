#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#define RX_pin 44
#define TX_pin 43
#define GPS_baud 9600

SoftwareSerial gps_serial(RX_pin, TX_pin);

TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  gps_serial.begin(9600);
}

void loop() {
  while (gps_serial.available()) {
    String data = gps_serial.readStringUntil('\n'); // Read complete sentence

    // This line processes each character from the sentence
    for (int i = 0; i < data.length(); i++) {
      gps.encode(data.charAt(i));
      
    }

    // Check for valid location data after processing the entire sentence
    if (gps.location.isValid()) {
      double currentLatitude = gps.location.lat();
      double currentLongitude = gps.location.lng();
      Serial.print("Latitude: ");
      Serial.println(currentLatitude);
      Serial.print("Longitude: ");
      Serial.println(currentLongitude);
    }
    delay(1000);
  }

  delay(5000);
}
