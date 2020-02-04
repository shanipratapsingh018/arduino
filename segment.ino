

 
#include < ESP8266WiFi.h>
 
const char* ssid = "Your SSID";
const char* password = "Your Wifi Password";

//Seven segment pins attachecd with nodemcu pins  
int a = 0;  //Gpio-0 with a of 7 segment display   
int b = 1;  //Gpio-1 with b of 7 segment display    
int c = 2;  //Gpio-2 with c of 7 segment display  
int d = 3;  //Gpio-3 with d of 7 segment display  
int e = 4;  //Gpio-4 with e of 7 segment display   
int f = 5;  //Gpio-5 with f of 7 segment display  
int g = 16; //Gpio-16 with g of 7 segment display

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
//Declaring Seven segment pins as Output
pinMode(a, OUTPUT);      pinMode(b, OUTPUT);     pinMode(c, OUTPUT);
pinMode(d, OUTPUT);      pinMode(e, OUTPUT);     pinMode(f, OUTPUT);
pinMode(g, OUTPUT);  
 
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
 
  // Print the IP address on serial monitor
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");    //URL IP to be typed in mobile/desktop browser
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

 int value = 0;
 // Match the request

if (request.indexOf("/Req=1") != -1)  {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);       //Displaying 1
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
  value=1;
}
if (request.indexOf("/Req=2") != -1)  {  
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);      //Displaying 2
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
  value=2;
}
if (request.indexOf("/Req=3") != -1)  { 
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);      //Displaying 3
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
  value=3;
}
if (request.indexOf("/Req=4") != -1)  {  
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);     //Displaying 4
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  value=4;
}
if (request.indexOf("/Req=5") != -1)  { 
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);     //Displaying 5
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  value=5;
}
if (request.indexOf("/Req=6") != -1)  {  
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);    //Displaying 6
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  value=6;
}
if (request.indexOf("/Req=7") != -1)  {  
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);   //Displaying 7
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  value=7;
}
if (request.indexOf("/Req=8") != -1)  { 
  digitalWrite(a, LOW );
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);     //Displaying 8
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  value=8;
}
if (request.indexOf("/Req=9") != -1)  {  
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);    //Displaying 9
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  value=9;
}  

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<h1 align=center>7 segment display over WiFi</h1><br><br>");
  client.print("Currently Displaying = ");
  client.print(value); 
  client.println("<br><br>");
  client.println("<a href=\"/Req=1\"\"><button>Display-1 </button></a><br/>");
  client.println("<a href=\"/Req=2\"\"><button>Display-2 </button></a><br/>");
  client.println("<a href=\"/Req=3\"\"><button>Display-3 </button></a><br/>");
  client.println("<a href=\"/Req=4\"\"><button>Display-4 </button></a><br/>");
  client.println("<a href=\"/Req=5\"\"><button>Display-5 </button></a><br/>");
  client.println("<a href=\"/Req=6\"\"><button>Display-6 </button></a><br/>");
  client.println("<a href=\"/Req=7\"\"><button>Display-7 </button></a><br/>");
  client.println("<a href=\"/Req=8\"\"><button>Display-8 </button></a><br/>");
  client.println("<a href=\"/Req=9\"\"><button>Display-9 </button></a><br/>"); 
  client.println("</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}

