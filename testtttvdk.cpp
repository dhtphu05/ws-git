#include "DHT.h" // Gọi thư viện DHT.h

const int DHT_PIN = 4;      // Đọc dữ liệu từ DHT11 ở chân 4 trên mạch Arduino
const int DHT_TYPE = DHT11; // Khai báo loại cảm biến, có 2 loại là DHT11 và DHT22

DHT dht(DHT_PIN, DHT_TYPE); // Tạo đối tượng dht, sử dụng chân 4 và loại cảm biến DHT11 để giao tiếp

void setup() {
  Serial.begin(9600); // Thiết lập tốc độ giao tiếp giữa Arduino và máy tính là 9600 bps.
  Serial.println("DHT TEST PROGRAM");
  dht.begin(); // Khởi tạo cảm biến DHT11
  Serial.println("Type\tHumidity (%)\tTemperature (C)");
}

void loop() {
  float h = dht.readHumidity();    // Đọc độ ẩm
  float t = dht.readTemperature(); // Đọc nhiệt độ (mặc định trả về Celsius)

  if (isnan(h) || isnan(t)) { // Kiểm tra xem các giá trị h (độ ẩm) và t (nhiệt độ) có hợp lệ hay không
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("DHT11\t");
    Serial.print(h);
    Serial.print("%\t\t");
    Serial.print(t);
    Serial.println("C");
  }

  delay(2000); // Đợi 2 giây
}
