// Cổng gửi dữ liệu đến Ứng dụng ERa bằng cách sử dụng ERa.virtualWrite(vPin, value) và nhận dữ liệu từ Ứng dụng bằng cách sử dụng ERA_WRITE(vPIN).

ERA_WRITE(vPIN)
//ERA_WRITE là một chức năng được gọi mỗi khi có giá trị pin ảo từ Ứng dụng ERa:
// Để diễn giải dữ liệu đến dưới dạng Số nguyên, Số thực, Số đôi và Chuỗi, sử dụng:
param.getInt();
param.getFloat();
param.getDouble();
param.getString();   
ERA_WRITE(V0) {
    int value = param.getInt();    //value là giá trị được được từ Pin V0
 //   Serial.printf("Virtual pin %d get %d\r\n", pin, value);      // Thay vì in giá trị, có thể ứng dụng để bật tắt LED như sau:
    digitalWrite(pin, value ? HIGH : LOW);     //Check giá trị từ value và thay đổi mức logic từ "pin" bằng toán tử so sánh "?"    
    ERa.virtualWrite(V1, digitalRead(pin));    // Gửi lại giá trị để hiển thị trạng thái pin ảo
}
//--------------Lưu ý: Đối với các Ghim ảo có số &gt; 99, vui lòng sử dụng ERA_WRITE_DEFAULT() API---------------

//Để gửi dữ liệu đến ERA, hãy sử dụng:  
ERa.virtualWrite(vPin, giá trị)   
/* Send integer */
ERa.virtualWrite(pin, 123);

/* Send float, double */
ERa.virtualWrite(pin, 123.456);

/* Send string */
ERa.virtualWrite(pin, "Hello");

/* Send multiple pins */
ERa.virtualWrite(pin, 123, pin2, 12.34f);
//------------ Vui lòng KHÔNG đặt ERa.virtualWrite(vPin, value) trong void loop(), sử dụng nó trong hàm ERATimer (timerEvent()).-----------

//------------------ VÍ DỤ VỀ gửi dữ liệu đến ERA.------------------------  
void timerEvent() {   //CÓ Ở CODE MẪU
    ERA_LOG("Timer", "Uptime: %d", ERaMillis() / 1000L);
    ERa.virtualWrite(V0, digitalRead(pin));                              
}                          
