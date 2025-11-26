/*
 * ==============================================================
 * * * * CODE MASTER (NẠP VÀO ESP32) * * * *
 *
 * Nhiệm vụ: Chạy Web Server, xử lý mật khẩu, gửi lệnh đơn giản
 * (A, F, O) và chỉ gửi 3 SỐ GIÂY XANH.
 * ==============================================================
 */

#include <WiFi.h>
#include <WebServer.h>      // Dùng thư viện ổn định, có sẵn
#include <ArduinoJson.h> 

// --- 1. CẤU HÌNH MẠNG VÀ BẢO MẬT ---
// !!! SỬA 4 DÒNG NÀY THEO Ý BẠN !!!
char ssid[] = "Truong";
char pass[] = "88888888";
const char* www_username = "admin";
const char* www_password = "admin";

WebServer server(80);

// --- 2. BIẾN LOGIC (CHỈ CẦN GIÂY XANH) ---
// (Lấy giá trị mặc định từ code Arduino gốc của bạn)
unsigned long x1 = 30000;
unsigned long x2 = 30000;
unsigned long x3 = 30000;
// Đã xóa v1, v2, v3

int Mode = 0; // 0=Auto, 1=Off, 2=Flash
const int MODE_AUTO = 0;
const int MODE_OFF = 1;
const int MODE_FLASH = 2;

// --- 3. TRANG WEB HTML (Đã rút gọn) ---
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
    <head>
        <title>Điều khiển Đèn Giao Thông</title>
        <meta charset="UTF-8" />
        <meta name="viewport" content="width=device-width, initial-scale=1" />
        <style>
            body {
                font-family: Arial, sans-serif;
                background: #f4f4f4;
                padding: 20px;
            }
            h1 {
                text-align: center;
                color: #333;
            }
            .card {
                background: #fff;
                border-radius: 8px;
                box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
                margin-bottom: 20px;
                padding: 20px;
            }
            h2 {
                margin-top: 0;
                color: #555;
            }
            .mode-buttons {
                display: grid;
                grid-template-columns: 1fr 1fr 1fr;
                gap: 10px;
            }
            .btn {
                padding: 15px;
                font-size: 16px;
                border: none;
                border-radius: 5px;
                cursor: pointer;
            }
            .btn-auto {
                background: #2ecc71;
                color: white;
            }
            .btn-flash {
                background: #f1c40f;
                color: white;
            }
            .btn-off {
                background: #e74c3c;
                color: white;
            }
            .btn.active {
                box-shadow: 0 0 0 3px #3498db;
            }
            .config-form {
                display: grid;
                gap: 10px;
            }

            /* ĐÃ SỬA: Thêm 1 cột 'auto' cho chữ "giây" */
            .form-group {
                display: grid;
                grid-template-columns: 1fr 100px auto; /* label | input | unit */
                gap: 10px;
                align-items: center;
            }
            label {
                font-weight: bold;
            }
            input[type='number'] {
                padding: 8px;
                border: 1px solid #ddd;
                border-radius: 5px;
                text-align: right;
                font-size: 16px;
            }

            /* ĐÃ THÊM: CSS cho chữ "giây" */
            .unit {
                padding-left: 5px;
                color: #555;
                font-style: italic;
            }

            .btn-save {
                background: #3498db;
                color: white;
                padding: 12px;
                font-size: 16px;
                width: 100%;
            }
            #status {
                text-align: center;
                font-style: italic;
                color: #777;
                margin-top: 15px;
            }
        </style>
    </head>
    <body>
        <h1>ĐIỀU KHIỂN ĐÈN GIAO THÔNG</h1>
        <div class="card">
            <h2>Chế độ (Mode)</h2>
            <div class="mode-buttons">
                <button class="btn btn-auto" id="btnMode0" onclick="sendMode(0)">AUTO</button>
                <button class="btn btn-flash" id="btnMode2" onclick="sendMode(2)">FLASH</button>
                <button class="btn btn-off" id="btnMode1" onclick="sendMode(1)">OFF</button>
            </div>
        </div>
        <div class="card">
            <h2>Cấu hình thời gian XANH (giây)</h2>
            <div class="config-form">
                <div class="form-group">
                    <label>Hướng Lạch Tray rẽ trái:</label>
                    <input type="number" id="val-x1" />
                    <span class="unit">giây</span>
                </div>
                <div class="form-group">
                    <label>Hướng Lạch Tray đi thẳng:</label>
                    <input type="number" id="val-x2" />
                    <span class="unit">giây</span>
                </div>
                <div class="form-group">
                    <label>Hướng Nguyễn Văn Linh:</label>
                    <input type="number" id="val-x3" />
                    <span class="unit">giây</span>
                </div>

                <button class="btn btn-save" onclick="updateTimings()">Cập nhật</button>
            </div>
        </div>
        <p id="status">Đang tải trạng thái...</p>
        <script>
            window.onload = function () {
                getStatus()
            }
            function getStatus() {
                fetch('/getstatus')
                    .then((response) => {
                        if (!response.ok) {
                            throw new Error('Auth failed')
                        }
                        return response.json()
                    })
                    .then((data) => {
                        document.getElementById('status').innerText = 'Đã kết nối và đồng bộ.'

                        // ĐÃ SỬA: Chia 1000 để hiển thị giây
                        document.getElementById('val-x1').value = data.x1 / 1000
                        document.getElementById('val-x2').value = data.x2 / 1000
                        document.getElementById('val-x3').value = data.x3 / 1000

                        document
                            .querySelectorAll('.btn')
                            .forEach((btn) => btn.classList.remove('active'))
                        let activeBtn = document.getElementById('btnMode' + data.mode)
                        if (activeBtn) activeBtn.classList.add('active')
                    })
                    .catch((error) => {
                        document.getElementById('status').innerText =
                            'Lỗi kết nối/xác thực. Hãy tải lại.'
                    })
            }
            function sendMode(mode) {
                document.getElementById('status').innerText = 'Đang gửi lệnh...'
                fetch('/setmode?mode=' + mode).then((response) => getStatus())
            }
            function updateTimings() {
                document.getElementById('status').innerText = 'Đang cập nhật thời gian...'

                // ĐÃ SỬA: Nhân 1000 trước khi gửi
                let x1_ms = document.getElementById('val-x1').value * 1000
                let x2_ms = document.getElementById('val-x2').value * 1000
                let x3_ms = document.getElementById('val-x3').value * 1000

                let url = `/setconfig?x1=${x1_ms}&x2=${x2_ms}&x3=${x3_ms}`

                fetch(url).then((response) => getStatus())
            }
        </script>
    </body>
</html>
)rawliteral";


// --- 4. HÀM GỬI LỆNH CHO ARDUINO (RÚT GỌN) ---
void sendCommandToArduino() {
  String command = "";
  if (Mode == MODE_AUTO) {
    // Gửi lệnh: "A,x1,x2,x3\n"
    command = "A," + String(x1) + "," + String(x2) + "," + String(x3);
  } else if (Mode == MODE_FLASH) {
    command = "F"; // Lệnh Flash
  } else if (Mode == MODE_OFF) {
    command = "O"; // Lệnh Off
  }
  
  Serial2.println(command); // Gửi qua TX2 (GPIO 17)
  Serial.println("Sent to Arduino: " + command); // In ra Serial Monitor để debug
}

// --- 5. CÁC HÀM XỬ LÝ WEB SERVER (RÚT GỌN) ---
void handleRoot() {
  if (!server.authenticate(www_username, www_password)) return server.requestAuthentication();
  server.send_P(200, "text/html", index_html);
}

void handleGetStatus() {
  if (!server.authenticate(www_username, www_password)) return server.requestAuthentication();
  StaticJsonDocument<256> status;
  status["mode"] = Mode;
  status["x1"] = x1;
  status["x2"] = x2;
  status["x3"] = x3;
  String jsonString;
  serializeJson(status, jsonString);
  server.send(200, "application/json", jsonString);
}

void handleSetMode() {
  if (!server.authenticate(www_username, www_password)) return server.requestAuthentication();
  if (server.hasArg("mode")) {
    int newMode = server.arg("mode").toInt();
    if (newMode >= 0 && newMode <= 2) {
      Mode = newMode;
      sendCommandToArduino(); // Gửi lệnh mới cho Arduino
      server.send(200, "text/plain", "OK");
    } else {
      server.send(400, "text/plain", "Invalid Mode");
    }
  } else {
    server.send(400, "text/plain", "Missing Mode");
  }
}

void handleSetConfig() {
  if (!server.authenticate(www_username, www_password)) return server.requestAuthentication();
  // Lấy 3 giá trị
  if (server.hasArg("x1")) x1 = atol(server.arg("x1").c_str());
  if (server.hasArg("x2")) x2 = atol(server.arg("x2").c_str());
  if (server.hasArg("x3")) x3 = atol(server.arg("x3").c_str());

  Mode = MODE_AUTO; // Tự động chuyển về AUTO
  sendCommandToArduino(); // Gửi cấu hình thời gian mới
  server.send(200, "text/plain", "OK");
}

void handleNotFound() {
  if (!server.authenticate(www_username, www_password)) return server.requestAuthentication();
  server.send(404, "text/plain", "Not found");
}

// --- 6. HÀM SETUP ---
void setup(){
  Serial.begin(115200); // Dùng để debug
  // Khởi động Serial2 (TX=17, RX=16) để nói chuyện với Arduino
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  // Kết nối Wi-Fi
  Serial.print("Connecting to "); Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println("\nWiFi connected!");
  Serial.print("IP address: "); Serial.println(WiFi.localIP());

  // Cài đặt Web Server
  server.on("/", HTTP_GET, handleRoot);
  server.on("/getstatus", HTTP_GET, handleGetStatus);
  server.on("/setmode", HTTP_GET, handleSetMode);
  server.on("/setconfig", HTTP_GET, handleSetConfig);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
  
  delay(1000); // Chờ Arduino sẵn sàng
  Mode = MODE_OFF; // Khởi động ở chế độ TẮT
  sendCommandToArduino(); // Gửi lệnh đầu tiên
}

// --- 7. HÀM LOOP ---
void loop() {
  server.handleClient(); // Chỉ làm đúng 1 việc: xử lý web
}