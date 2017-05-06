#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "Auth token";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Wifi name";
char pass[] = "Wifi password";

#define DHTPIN 2         // What digital pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11     // DHT 11
#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  int d = digitalRead(15);
  Blynk.virtualWrite(V4,d);
  Serial.println(h);
  Serial.println(t);
  Serial.println(d);
  Serial.println("");
  if (d == 0){
    Blynk.notify("Door opened");
    Serial.println("Sent Notification");
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  Serial.println("Started serial");
  Blynk.begin(auth, ssid, pass);
  Serial.println("Started blynk");
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  dht.begin();
  Serial.println("Started dht");
  pinMode(15,INPUT);
  Serial.println("Set pin 15 to input");
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
  Serial.println("Started timer");
}

void loop()
{
  Blynk.run();
  timer.run();

}
