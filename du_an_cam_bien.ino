#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"


#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// tên wifi
const char* ssid = "---------";        
// mật khẩu wifi
const char* password = "-----------";

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  dht.begin();
  Serial.println("connecting to WiFi ");
  // kết nối lại wifi
  while(WiFi.status() != WL_CONNECTED)
  {
    WiFi.begin(ssid, password);
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
  // nếu cảm biến hoạt động sai hoặc không hoạt động sẽ chạy lại
  if(isnan(temperature) || isnan(humidity))
  {
    Serial.println("error sensor");
    return;
  }
  // kết nối lại wifi khi bị ngắt kết nối
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
  // gửi giá trị của cảm biến về thingspeak
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
