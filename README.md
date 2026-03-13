# ESP32-DHT22-HTTP-ThingSpeak
ESP32 IoT project sending temperature and humidity to ThingSpeak


Dự án IoT sử dụng ESP32 và cảm biến DHT22 để đo nhiệt độ và độ ẩm.
Dữ liệu được gửi lên nền tảng ThingSpeak để hiển thị trên dashboard web.

Chức năng:
- Đọc nhiệt độ và độ ẩm từ DHT22
- Kết nối WiFi
- Gửi dữ liệu lên ThingSpeak

## Phần cứng sử dụng
- ESP32 DevKit V1
- Cảm biến nhiệt độ và độ ẩm DHT22
- Breadboard
- Dây kết nối (jumper wires)

## Phần mềm sử dụng
- Arduino IDE
- Thư viện DHT sensor library
- Thư viện WiFi (ESP32)
- Nền tảng IoT ThingSpeak để hiển thị dữ liệu
