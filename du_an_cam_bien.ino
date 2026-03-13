#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"


#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Ong Thuong";
const char* password = "123456789@";

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  dht.begin();
  Serial.println("connecting to WiFi ");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if(isnan(temperature) || isnan(humidity))
  {
    Serial.println("error sensor");
    return;
  }
  
  if(WiFi.status() != WL_CONNECTED)
  {
    WiFi.begin(ssid, password);
    Serial.println("Reconnecting to Wi-Fi ");
    while(WiFi.status() != WL_CONNECTED)
    {
      Serial.print(".");
      delay(1000);
    }
    Serial.println();
    Serial.println("Reconnection successful");
  }

  if(WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    String url ="http://api.thingspeak.com/update?api_key=-----------------";
    url += "&field1=" + String(temperature);
    url += "&field2=" + String(humidity);

    http.begin(url);

    int httpResponseCode = http.GET();
    if(httpResponseCode > 0)
    {
      Serial.print("Response: ");
      Serial.println(httpResponseCode);
    }
    else
    {
      Serial.print("error");
      Serial.println(httpResponseCode);
    }
    http.end();
  }


  Serial.print("temperature: ");
  Serial.print(temperature);
  Serial.println("°c");

  Serial.print("humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  Serial.println("---------------");

  delay(15000);

}