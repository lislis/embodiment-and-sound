#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

char ssid[] = "hardware-network";          // your network SSID (name)
char pass[] = "alotofraspberrytarts";      // your network password

WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP

// CHANGE IP AND PORT
const IPAddress outIp(192,168,8,184);        // remote IP of your computer
const unsigned int outPort = 3334;          // remote port to receive OSC


const unsigned int localPort = 3333;
// CHANGE SENSOR ID HERE
char * oscAddress = "/breath/1";

int analogPin = 32;
int reading = 0;
int Vin = 3.3;
float Vout = 0;
float R1 = 100;
float R2 = 0;
float buffer = 0;


void setup() {
    Serial.begin(115200);

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Starting UDP");
    Udp.begin(localPort);
    Serial.print("Local port: ");
#ifdef ESP32
    Serial.println(localPort);
#else
    Serial.println(Udp.localPort());
#endif
}

void loop(){
  reading = analogRead(analogPin);
  Serial.println(reading);

  buffer = reading * Vin;
  Vout = (buffer)/4095.0;
  buffer = (Vin/Vout) - 1;
  R2= R1 * buffer;
  Serial.print("R2: ");
  Serial.println(R2);

  OSCMessage msg(oscAddress);

  // normalize
  // CHANGE HERE
  msg.add(normalize(R2, 28.0, 48.0));
  msg.add(R2);
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
  delay(100); 
}

float normalize(float val, float min, float max) {
  return (val - min) / (max - min); 
}