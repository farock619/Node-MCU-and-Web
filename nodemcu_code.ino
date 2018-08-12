
#include <ESP8266WiFi.h>


IPAddress ip(192,168,1,100);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);


 
const char* ssid = "Jazz-LTE-F2F2";
const char* password = "63003384";
 
int ledPin1 = D0;
int ledPin2 = D1;
int ledPin3 = D7;
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, LOW);

   pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, LOW);

   pinMode(ledPin3, OUTPUT);
  digitalWrite(ledPin3, LOW);
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

 WiFi.config(ip, gateway, subnet);
 
  WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected :)");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 

  Serial.println("waiting for URL ");
  while(!client.available()){
    delay(1);
  }
 

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

 
  int value1 = LOW;
  if (request.indexOf("/LOCK1=Locked") != -1)  {
    digitalWrite(ledPin1, HIGH);
    value1 = HIGH;
  }
  if (request.indexOf("/LOCK1=Unlocked") != -1)  {
    digitalWrite(ledPin1, LOW);
    value1 = LOW;
  }
    int value2 = LOW;
  if (request.indexOf("/LOCK2=Locked") != -1)  {
    digitalWrite(ledPin2, HIGH);
    value2 = HIGH;
  }
  if (request.indexOf("/LOCK2=Unlocked") != -1)  {
    digitalWrite(ledPin2, LOW);
    value2 = LOW;
  }
    int value3 = LOW;
  if (request.indexOf("/LOCK3=Locked") != -1)  {
    digitalWrite(ledPin3, HIGH);
    value3 = HIGH;
  }
  if (request.indexOf("/LOCK3=Unlocked") != -1)  {
    digitalWrite(ledPin3, LOW);
    value3 = LOW;
  }
 
  
  client.println("<!DOCTYPE HTML>");

 client.println("<body style=background-color:#6A576C>");
client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
client.println("<link rel=\"icon\" href=\"data:,\">");
client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
client.println(".button { background-color: #C9FBFA; border: none; color: black; padding: 16px 40px;");
client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
client.println(".button2 {background-color: #C9FBFA;}</style></head>");

 
  if(value1 == HIGH) {
    client.print("Locked");
  } else {
    client.print("Unlocked");
  }
  client.println("<br><br>");
  client.println("<p><a href=\"/LOCK1=Locked\"><button class=\"button\">ON</button></a></p>");
  client.println("<p><a href=\"/LOCK1=Unlocked\"><button class=\"button button2\">OFF</button></a></p>");
  client.println("<br><br>");

  
  client.print("Door 2 is now: ");
  if(value2 == HIGH) {
    client.print("Locked");
  } else {
    client.print("Unlocked");
  }
  client.println("<br><br>");
 client.println("<p><a href=\"/LOCK2=Locked\"><button class=\"button\">ON</button></a></p>");
  client.println("<p><a href=\"/LOCK2=Unlocked\"><button class=\"button button2\">OFF</button></a></p>");
  client.println("<br><br>");

  
  client.print("Door 3 is now: ");
   if(value3 == HIGH) {
    client.print("Locked");
  } else {
    client.print("Unlocked");
  }
  client.println("<br><br>");
  client.println("<p><a href=\"/LOCK3=Locked\"><button class=\"button\">ON</button></a></p>");
  client.println("<p><a href=\"/LOCK3=Unlocked\"><button class=\"button button2\">OFF</button></a></p>");

  client.println("</body></html>");
 
  delay(1);
  Serial.println("WIFI disonnected");
  Serial.println("");
}

