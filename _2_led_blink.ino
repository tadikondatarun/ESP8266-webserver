#include <ESP8266WiFi.h>
 
const char* ssid = "connected";
const char* password = "anvesh1998";
 
int ledPin = 13; // GPIO13
int ledPin1=12; //gpio12
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin1,OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(ledPin1,LOW);
  
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led pin is now: ");
 
  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br>");  
  client.println("</html>");
    // Read the first line of the request
  String request1 = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the  second request 
 
  int value1 = LOW;
  if (request.indexOf("/LED1=ON") != -1)  {
    digitalWrite(ledPin1, HIGH);
    value1 = HIGH;
  }
  if (request.indexOf("/LED1=OFF") != -1)  {
    digitalWrite(ledPin1, LOW);
    value1 = LOW;
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  //client.println("HTTP/1.1 200 OK");
  //client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  //client.println("<br>");
 
  client.print("Led pin 1 is now: ");
 
  if(value1 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED1=ON\"\"><button>Turn On led 1 </button></a>");
  client.println("<a href=\"/LED1=OFF\"\"><button>Turn Off led 1</button></a>");  
  client.println("</html>");
 
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
