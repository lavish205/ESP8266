
#include <ESP8266WiFi.h>

const char* ssid = "belongbox";
const char* password = "largepanda221";

int warnPin = 15;
int okPin = 12;
//int buzzer = 14;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(warnPin, OUTPUT);
  pinMode(okPin, OUTPUT);

  //pinMode(buzzer, OUTPUT);
  digitalWrite(okPin, HIGH);
  digitalWrite(warnPin, LOW);

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
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request

  int value = LOW;
  if (request.indexOf("/buzzer") != -1)  {
    //digitalWrite(ledPin1, HIGH);
    //digitalWrite(ledPin2, HIGH);
    //digitalWrite(ledPin3, HIGH);
    blink(1);
    value = HIGH;
  }
  if (request.indexOf("/led") != -1)  {
    //digitalWrite(ledPin1, HIGH);
    //digitalWrite(ledPin2, HIGH);
    //digitalWrite(ledPin3, HIGH);
    blink(2);
    value = HIGH;
  }
  if (request.indexOf("/off") != -1)  {
    //digitalWrite(ledPin1, LOW);
    //digitalWrite(ledPin2, LOW);
    //digitalWrite(ledPin3, LOW);
    blink(0);
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

  if (value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/buzzer\"\"><button>Red LED With Buzzer</button></a>");
  client.println("<a href=\"/led\"\"><button>Blink Red LED</button></a>");
  client.println("<a href=\"/off\"\"><button>Go Green</button></a><br />");
  client.println("</html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}

void blink(int a) {
  Serial.println("In blinking function");
  Serial.println(a);
  if (a == 1) {
    for (int i = 0; i < 5; i++) {
      Serial.println("condition 1 true");
      digitalWrite(okPin, LOW);
      digitalWrite(warnPin, HIGH);
      Serial.println("Playing tone");
      tone(14, 800, 1000);

      delay(500);
      noTone(14);
      digitalWrite(warnPin, LOW);

      delay(500);
    }
    digitalWrite(warnPin, HIGH);
  }
  if (a == 2) {
    for (int i = 0; i < 5; i++) {
      digitalWrite(okPin, LOW);
      digitalWrite(warnPin, HIGH);
      delay(500);
      noTone(14);
      digitalWrite(warnPin, LOW);

      delay(500);
    }
    digitalWrite(warnPin, HIGH);
  }
  if  (a == 0) {
    Serial.println("Condition false");
    digitalWrite(okPin, HIGH);
    digitalWrite(warnPin, LOW);
  }
}

