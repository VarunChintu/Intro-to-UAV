#include <Arduino.h>
#include <WiFi.h>

#include <esp32PWMUtilities.h>


// Replace with your network credentials
// const char* ssid = "POCO X3";
// const char* password = "iith.varun";

const char* ssid = "NeverGiveUP";
const char* password = "itslife2";

// Set web server port number to 80
WiFiServer server(80);

Motor Motor1;

Motor Motor2;

void webpage(WiFiClient client){

  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
  client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
  client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
  client.println(".button2 {background-color: #555555;}</style></head>");
  
  client.println("<body><h1>ESP32 Web Server</h1>");
  client.println("<p><a href=\"/forward\"><button class=\"button\">forward</button></a></p>");
  client.println("<p><a href=\"/right\"><button class=\"button\">right</button></a></p>");
  client.println("<p><a href=\"/left\"><button class=\"button\">left</button></a></p>");
  client.println("<p><a href=\"/reverse\"><button class=\"button\">reverse</button></a></p>");
  client.println("<p><a href=\"/stop\"><button class=\"button button2\">stop</button></a></p>");

  client.println("</body></html>");
  client.println();
}

void forward(){
  Motor1.moveMotor(2.55 * 100);
  Motor2.moveMotor(2.55 * 100);
}
void reverse(){
  Motor1.moveMotor(-2.55 * 100);
  Motor2.moveMotor(-2.55 * 100);
}
void right(){
  Motor1.moveMotor(2.55 * 100);
  Motor2.moveMotor(-2.55 * 100);
}
void left(){
  Motor1.moveMotor(-2.55 * 100);
  Motor2.moveMotor(2.55 * 100);
}
void stop(){
  Motor1.lockMotor();
  Motor2.lockMotor();
}

void handleRequest(String request){
  if (request.indexOf("/forward") > 0){
    forward();
    delay(500);
  }
  if (request.indexOf("/reverse") > 0){
    reverse();
    delay(500);
  }
  
  if (request.indexOf("/left") > 0){
    left();
    delay(500);
  }
  
  if (request.indexOf("/right") > 0){
    right();
    delay(500);
  }
  if (request.indexOf("/stop") > 0){
    stop();
    delay(500);
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Motor1.attach(14, 16, 17);

  Motor2.attach(15, 18, 19);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

}

void loop(){
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println(request);
        handleRequest(request);
      }
      webpage(client);
      break;
    }
  }
}