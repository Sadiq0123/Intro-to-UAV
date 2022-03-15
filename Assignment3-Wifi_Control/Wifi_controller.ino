#include <WiFi.h>
//Constants
#define LED 2
#define L_in1 16
#define L_in2 17
#define R_in1 18
#define R_in2 19
#define R_enable HIGH
#define L_enable HIGH

//Parameters
String request ;
char* ssid  = "Mi Redmi 7";
char* password  = "sadiq1234";
String nom  = "ESP32";


void webpage(WiFiClient client) { /* function webpage */
  ////Send webpage to client
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<title> UGV_Wifi_Navigation </title>");
  client.println("<meta http-equiv='content-type' content='text/html; charset=UTF-8'>");
  client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
  client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
  client.println("<meta http-equiv='refresh' content='5'>");
  client.println("</head>");
  client.println("<body bgcolor = '#FFE5B4'> ");
  client.println("<hr/><hr>");
  client.println("<h1 style='color : #194D33;'><center> SCV UGV - Web Controller </center></h1>");
  client.println("<hr/><hr>");
  client.println("<h2 style='color : #194D33;'> Navigation </h2>");
  client.println("<table>");
  client.println("<tr>");
  client.println("<td></td>");
  client.println("<td><a href='/forward'><button style=\"height:200px;width:200px\"><img src=\"https://cdn.pixabay.com/photo/2013/07/12/13/43/arrow-147174__480.png\" height=\"50%\" width=\"50%\"/></button></a></td>");
  client.println("<td></td>");
  client.println("</tr>");
  client.println("<tr>");
  client.println("<td><a href='/left'><button style=\"height:200px;width:200px\"><img src=\"https://cdn.pixabay.com/photo/2013/07/12/13/43/arrow-147173_960_720.png\" height=\"50%\" width=\"50%\"/></button></a></td>");
  client.println("<td><a href='/stop'><button style=\"height:200px;width:200px\"><img src=\"https://www.pelennapatchworks.co.uk/user/products/large/paper%20squares.jpg\" height=\"50%\" width=\"50%\"/></button></a></td>");
  client.println("<td><a href='/right'><button style=\"height:200px;width:200px\"><img src=\"https://cdn.pixabay.com/photo/2013/07/12/13/43/arrow-147175_960_720.png\" height=\"50%\" width=\"50%\"/></button></a></td>"); 
  client.println("</tr>");
  client.println("<tr>");
  client.println("<td></td>");
  client.println("<td><a href='/back'><button style=\"height:200px;width:200px\"><img src=\"https://cdn.pixabay.com/photo/2013/07/12/13/43/arrow-147172_960_720.png\" height=\"50%\" width=\"50%\"/></button></a></td>");
  client.println("<td></td>");
  client.println("</tr>");
  client.println("</table>");
  delay(1);
}


void forward(){
  digitalWrite(L_in1, HIGH);
  digitalWrite(L_in2, LOW);
  digitalWrite(R_in1, HIGH);
  digitalWrite(R_in2, LOW);
}
void back(){
  digitalWrite(L_in1, LOW);
  digitalWrite(L_in2, HIGH);
  digitalWrite(R_in1, LOW);
  digitalWrite(R_in2, HIGH);
}
void left(){
  digitalWrite(L_in1, LOW);
  digitalWrite(L_in2, HIGH);
  digitalWrite(R_in1, HIGH);
  digitalWrite(R_in2, LOW);
}

void right(){
  digitalWrite(L_in1, HIGH);
  digitalWrite(L_in2, LOW);
  digitalWrite(R_in1, LOW);
  digitalWrite(R_in2, HIGH);  
}

void stop(){
  digitalWrite(L_in1, LOW);
  digitalWrite(L_in2, LOW);
  digitalWrite(R_in1, LOW);
  digitalWrite(R_in2, LOW);
}


// Wifi server on esp setup
WiFiServer server(80);
WiFiClient client;

void setup() {
  // Motor controls
  pinMode(L_in1, OUTPUT);
  pinMode(L_in2, OUTPUT);
  pinMode(R_in1, OUTPUT);
  pinMode(R_in2, OUTPUT);
  
  // Serial USB
  delay(5000);
  Serial.begin(115200);
  Serial.println(F("Initialize System"));
  //Init ESP32Wifi
  Serial.print("Connecting to network: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  // Wifi
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(F("."));
  }
  server.begin();
  Serial.println();
  Serial.println(F("ESP32Wifi initialized"));
  Serial.print(F("IP Address: "));
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println(request);
        handleRequest(request);
      }
      webpage(client);//Return webpage
      break;
    }
  }
}


void handleRequest(String request) { /* function handleRequest */
  ////Handle web client request
  String pwmCmd;
  //Digital Ouputs
  if (request.indexOf("/forward") > 0){
    forward();
    delay(500);
  }
  else if (request.indexOf("/back") > 0){
    back();
    delay(500);
  }
  
  else if (request.indexOf("/left") > 0){
    left();
    delay(500);
  }
  
  else if (request.indexOf("/right") > 0){
    right();
    delay(500);
  }
  else{
    stop();
    delay(500);
  }
  
}
