#define BLYNK_TEMPLATE_ID "TMPL6KUwrQpvH"
#define BLYNK_TEMPLATE_NAME "LAB"
#define BLYNK_AUTH_TOKEN "xuvuy4gzYqQfBWky9brxiRtS1wKJ4s1n"

#include <WiFi.h>
#include <WiFiClient.h> // Sửa tên tệp từ 'WifiClient.h' thành 'WiFiClient.h'
#include <BlynkSimpleEsp32.h>
#include <string.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN 19
DHT dht(DHTPIN, DHTTYPE);

#define LED 5
WidgetLED LED_ON_APP(V2);
int button;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "tuyen";
char pass[] = "tuyen12t";

void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(115200); // Đảm bảo baud rate khớp với Serial Monitor
  dht.begin();

  Blynk.begin(auth, ssid, pass);

  // Thêm thông báo khởi động để kiểm tra Serial hoạt động
  Serial.println("System initialized...");
}

BLYNK_WRITE(V3) {
  button = param.asInt();
  if(button == 1) {
    digitalWrite(LED, HIGH);
    LED_ON_APP.on();
  } else {
    digitalWrite(LED, LOW);
    LED_ON_APP.off();
  }
}

void loop()
{
  Blynk.run();

  // Đọc nhiệt độ và độ ẩm
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(500);
    return;
  }

  // Gửi dữ liệu đến Blynk
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);

  // In dữ liệu ra Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("°C");

  delay(2000); // Đảm bảo không gửi dữ liệu quá nhanh
}
