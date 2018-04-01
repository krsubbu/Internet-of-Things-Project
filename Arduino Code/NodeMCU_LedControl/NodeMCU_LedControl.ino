#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

const char* ssid     = "subham"; //Your ssid for wifi connected to nodemcu
const char* password = "123456789"; // Your wifi password

const char* host     = "coolshubhmdelhi10.000webhostapp.com"; // Your domain
String path          = "/light.json"; //json file name
const int pin        = 2; //led pin on nodemcu

void setup() {
  //Setting pin 2 as output for led
  pinMode(pin, OUTPUT);
  //Initializing led to ON Status
  pinMode(pin, HIGH);

  Serial.begin(115200);
  delay(10);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP());
}

void loop() {
  Serial.print("Connecting to :");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 80;

  //Checking if client is connected to host and httpPort
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  //After client connected to server It sends request to server to get the json file
  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: keep-alive\r\n\r\n");

  // wait for server to respond
  delay(500);

  // Read Response from server which was send to the client about the response
  String section = "header";

  //Checking continuously until a client is connected to the server
  while (client.available()) {

    //Read String from the request until \r
    String line = client.readStringUntil('\r');

    //We will check for \n to appear in request responce after which json text will appear.
    if (section == "header") {
      Serial.print(".");
      if (line == "\n") {
        section = "json";
      }
    }
    else if (section == "json") {
      section = "ignore";

      //Removing the \n charachter from line and storing it to result string.
      String result = line.substring(1);

      // Parse/Decoding JSON using the ArduinoJson library function
      int size = result.length() + 1;

      //creating json charachter array
      char json[size];

      //converting the result to json charachter array
      result.toCharArray(json, size);

      //Creating the buffer 200 to store the json file
      StaticJsonBuffer<200> jsonBuffer;

      //function parse the json object stored in json charachter array and store it in json_parsed
      JsonObject& json_parsed = jsonBuffer.parseObject(json);

      //Checking for json parsed is success or not
      if (!json_parsed.success())
      {
        Serial.println("parseObject() failed");
        return;
      }

      // Make the decision to turn off or on the LED
      if (strcmp(json_parsed["light"], "on") == 0) {
        digitalWrite(pin, LOW);
        Serial.println("LED ON");
      }
      else {
        digitalWrite(pin, HIGH);
        Serial.println("LED OFF");
      }
    }
  }
  Serial.println("closing connection. ");
}
