#define BLYNK_PRINT Serial

#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Auth Token in the Blynk App.
char auth[] = "1veMB14wEvIqJiMa2y_Z2_U2vOaWpJSD";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "vinay";
char pass[] = "vinay119";
//int rainsensor=D0;

int sense_Pin= 0; // Soil Sensor input at Analog PIN A0
int value= 0;

#define DHTPIN D4  
#define PUMPPIN D3 //pin where the dht11 is connected
 
DHT dht(DHTPIN, DHT11);


void setup()
{
  // Debug console
  //pinMode(rainsensor, INPUT);
  Serial.begin(115200);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
 // int rain = digitalRead(rainsensor);
  //Serial.println(rain);
  Blynk.run();
   float h = dht.readHumidity();
      float t = dht.readTemperature();
   Serial.print("MOISTURE LEVEL : ");
    value= analogRead(sense_Pin);
    value= value/10;
    Serial.println(value);
    Blynk.virtualWrite(V1,value);
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" degrees Celcius");
     Blynk.virtualWrite(V2,t);
     Serial.print("humidity:");
      Serial.println(h);
    
 
/*if(rain)
  {
    delay(1000);
    Serial.print("rain detected");
    Blynk.notify("rain detected");
  }
  else
  {
    
    Serial.print("rain not detected");
    delay(1000);
     }*/
   if(value>85)
  {
    delay(1000);
    Serial.println("low moisture");
    Blynk.notify("low moisture turn ON the pump");
  }
  else
  {
    
    Serial.print("good moisture level");
    delay(1000);
    
  }
}


