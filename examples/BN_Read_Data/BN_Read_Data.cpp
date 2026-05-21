#include <Arduino.h>
#include <BN_DHT11.h>

// Khởi tạo cảm biến BN_DHT11 kết nối với chân GPIO 4 của ESP32
BN_DHT11 myDht(4);

void setup()
{
    Serial.begin(115200);
    myDht.begin();
    Serial.println("BN_DHT11 Sensor Test Ready!");
}

void loop()
{
    // Đọc dữ liệu từ thư viện tự viết của bạn
    float temp = myDht.readTemperature();
    float hum = myDht.readHumidity();

    // Kiểm tra xem việc đọc dữ liệu có thành công hay không
    if (isnan(temp) || isnan(hum))
    {
        Serial.println("Loi: Khong doc duoc du lieu tu cam bien BN_DHT11!");
    }
    else
    {
        Serial.print("Nhiet do: ");
        Serial.print(temp);
        Serial.print(" *C | ");
        Serial.print("Do am: ");
        Serial.print(hum);
        Serial.println(" %");
    }

    delay(2000); // Đọc giãn cách 2 giây một lần
}