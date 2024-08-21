#define ERA_DEBUG
// ERA AUTOKEN
#define DEFAULT_MQTT_HOST "mqtt1.eoh.io"
#define ERA_AUTH_TOKEN "ERA123"  //THAY THẾ AUTH_TOKEN

// ADD LIBRARY
#include <WiFi.h>
#include <Arduino.h>
#include <ERa.hpp>
#include <ERa/ERaTimer.hpp>

int LED1= 2;
char ssid[] = "";
char password[] = "";

ERaTimer timer;
void TaskEra(void * pvParameters);

// ĐỌC GIÁ TRỊ TỪ ERA
ERA_WRITE(V0) {
    uint8_t value = param.getInt();
    digitalWrite(LED1, value ? HIGH : LOW);
    ERa.virtualWrite(V0, digitalRead(LED1));
}

//GỬI GIÁ TRỊ LÊN ERA - ỨNG DỤNG ĐỂ ĐỒNG BỘ CÔNG TẮC,....
// Ở VÍ DỤ NÀY KHÔNG CẦN HÀM NÀY VÌ TRONG HÀM "ERA_WRITE(0)" đã có sẵn để thay đổi giá trị pin ảo
void timerEvent() {
    ERA_LOG("Timer", "Uptime: %d", ERaMillis() / 1000L);    
    ERa.virtualWrite(V0, digitalRead(LED1));                //ĐẶT TRONG HÀM timerEvent()                      
}


void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to wifi");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  ERa.begin(ssid, password);
  xTaskCreatePinnedToCore (TaskEra, "Task Era NTP", 10000, NULL, 1, NULL, 0); // TẠO TASK ERA CHẠY TRÊN CORE 0
}

//------------------------------------------------------------------ TASK ERA CHẠY CORE 0--------------------------------------------------------------
void TaskEra(void * pvParameters) {
   (void) pvParameters;
    timer.setInterval(1000L, timerEvent);
    for(;;) {
        ERa.run();
        timer.run();
        vTaskDelay(10);      // NÊN CÓ LỆNH "vTaskDelay(time)" ĐỂ TRÁNH TÌNH TRẠNG WATCHDOG TIME
    }
}

//------------------------------------------------------------------ HÀM LOOP CHẠY CORE 1--------------------------------------------------------------
void loop() {
 // TẠI ĐÂY CÓ THỂ SỬ DỤNG CÁC HÀM NHƯ: GIAO TIẾP MODULE LORA, MÀN HÌNH HMI, RELAY,....           
 vTaskDelay(10);
}
