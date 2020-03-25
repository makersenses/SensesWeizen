//Credit: https://microcontrollerslab.com/esp32-web-server-arduino-led/

#include <WiFi.h>
const char* WIFI_NAME = "BOOM_WiFi";
const char* WIFI_PASSWORD = "076434654";
WiFiServer server(80); 

String header;
String Relay1_State = "off";
String Relay2_State = "off";
String Relay3_State = "off";

const int Relay1_PIN = 32;
const int Relay2_PIN = 26;
const int Relay3_PIN = 13;

void setup() {
  Serial.begin(115200);
  pinMode(Relay1_PIN, OUTPUT);
  pinMode(Relay2_PIN, OUTPUT);
  pinMode(Relay3_PIN, OUTPUT);

  digitalWrite(Relay1_PIN, LOW);
  digitalWrite(Relay2_PIN, LOW);
  digitalWrite(Relay3_PIN, LOW);

  Serial.print("Connecting to ");
  Serial.println(WIFI_NAME);
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Trying to connect to Wifi Network");
  }
  Serial.println("");
  Serial.println("Successfully connected to WiFi network");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client is requesting web page");
    String current_data_line = "";
    while (client.connected()) {
      if (client.available()) {
        char new_byte = client.read();
        Serial.write(new_byte);
        header += new_byte;
        if (new_byte == '\n') {

          if (current_data_line.length() == 0)
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("Relay1=ON") != -1)
            {
              Serial.println("GPIO21 Relay is ON");
              Relay1_State = "on";
              digitalWrite(Relay1_PIN, HIGH);
            }
            if (header.indexOf("Relay1=OFF") != -1)
            {
              Serial.println("GPIO21 Relay is OFF");
              Relay1_State = "off";
              digitalWrite(Relay1_PIN, LOW);
            }
 
            if (header.indexOf("Relay2=ON") != -1)
            {
              Serial.println("GPIO22 Relay is ON");
              Relay2_State = "on";
              digitalWrite(Relay2_PIN, HIGH);
            }
            if (header.indexOf("Relay2=OFF") != -1)
            {
              Serial.println("GPIO22 Relay is OFF");
              Relay2_State = "off";
              digitalWrite(Relay2_PIN, LOW);
            }
            
            if (header.indexOf("Relay3=ON") != -1)
            {
              Serial.println("GPIO33 Relay is ON");
              Relay3_State = "on";
              digitalWrite(Relay3_PIN, HIGH);
            }
            if (header.indexOf("Relay3=OFF") != -1) {
              Serial.println("GPIO33 Relay is OFF");
              Relay3_State = "off";
              digitalWrite(Relay3_PIN, LOW);
            }

            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #338DFF; border: 2px solid #338DFF;; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; }");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            // Web Page Heading
            client.println("</style></head>");
            client.println("<body><center><h1>ESP32 Web server Relay control</h1></center><br>");
            client.println("<form><center>");
            
            client.println("<p> Relay1 : " + Relay1_State + "</p>"); 
            client.println("<center> <button class=\"button\" name=\"Relay1\" value=\"ON\" type=\"submit\">Relay1 ON</button>") ;
            client.println("<button class=\"button\" name=\"Relay1\" value=\"OFF\" type=\"submit\">Relay1 OFF</button><br><br>");
            
            client.println("<p> Relay2 : " + Relay2_State + "</p>");
            client.println("<button class=\"button\" name=\"Relay2\" value=\"ON\" type=\"submit\">Relay2 ON</button>");
            client.println("<button class=\"button\" name=\"Relay2\" value=\"OFF\" type=\"submit\">Relay2 OFF</button> <br><br>");
            
            client.println("<p> Relay3 : " + Relay3_State + "</p>");
            client.println ("<button class=\"button\" name=\"Relay3\" value=\"ON\" type=\"submit\">Relay3 ON</button>");
            client.println ("<button class=\"button\" name=\"Relay3\" value=\"OFF\" type=\"submit\">Relay3 OFF</button></center>");
            client.println("</center></form></body></html>");
            client.println();
            break;
          }
          else
          {
            current_data_line = "";
          }
        }
        else if (new_byte != '\r')
        {
          current_data_line += new_byte;
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
