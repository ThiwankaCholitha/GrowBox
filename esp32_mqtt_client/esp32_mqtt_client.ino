#include <WiFi.h>
#include <PubSubClient.h>

//DHT Configurations
#include "DHT.h"
#define DHTPIN 13
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);


// Replace the next variables with your SSID/Password combination
//const char* ssid = "Lucky3241";
//const char* password =  "pushpa6633";

const char* ssid = "Dialog 4G";
const char* password =  "NRHAQL1RNJ6";




// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "192.168.8.13";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;


float temperature = 0;
float humidity = 0;

// LED Pin
const int ledPin = 4;



//Relays---------------------------------->
const int light1 = 18; //D23//23
const int light2 = 5; //D22//22
const int light3 = 15; //D21//22
const int fan1 = 19; //D19
const int fan2 = 4; //D18//18
const int fan3 =  21; //D5
const int motors = 23; //D4 //4
const int growLight = 22;//D2//15
//---------------------------------------->






void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  //Set the pin modes
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(light3, OUTPUT);
  pinMode(fan1, OUTPUT);
  pinMode(fan2, OUTPUT);
  pinMode(fan3, OUTPUT);
  pinMode(motors, OUTPUT);
  pinMode(growLight, OUTPUT);
  //Trigger 
  digitalWrite(light1, HIGH);
  digitalWrite(light2, HIGH);
  digitalWrite(light3, HIGH);
  digitalWrite(fan1, HIGH);
  digitalWrite(fan2, HIGH);
  digitalWrite(fan3, HIGH);
  digitalWrite(motors, HIGH);
  digitalWrite(growLight, HIGH);

  dht.begin();

  
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {


  digitalWrite(LED_BUILTIN,HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN,LOW);
  delay(50);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN,LOW);
  delay(50);
  
  
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Changes the output state according to the message
  //Light 1 controlls
  if (String(topic) == "GrowBox/Lights/Light01") {
    Serial.print("Changing output to ");
    if (messageTemp == "on") {
      Serial.println("on");
      digitalWrite(light1, LOW);
      delay(10);
    }
    else if (messageTemp == "off") {
      Serial.println("off");
      //      digitalWrite(ledPin, LOW);
      digitalWrite(light1, HIGH);
      delay(10);
    }
  }
  //Light 2 control
  if (String(topic) == "GrowBox/Lights/Light02") {
    Serial.print("Changing output to ");
    if (messageTemp == "on") {
      Serial.println("on");
      digitalWrite(light2, LOW);
      delay(10);
    }
    else if (messageTemp == "off") {
      Serial.println("off");
      //      digitalWrite(ledPin, LOW);
      digitalWrite(light2, HIGH);
      delay(10);
    }
  }

    //Light 3 control
  if (String(topic) == "GrowBox/Lights/Light03") {
    Serial.print("Changing output to ");
    if (messageTemp == "on") {
      Serial.println("on");
      digitalWrite(light3, LOW);
      delay(10);
    }
    else if (messageTemp == "off") {
      Serial.println("off");
      //      digitalWrite(ledPin, LOW);
      digitalWrite(light3, HIGH);
      delay(10);
    }
  }

    if (String(topic) == "GrowBox/Fans/Fan01") {
    Serial.print("Changing output to ");
    if (messageTemp == "on") {
      Serial.println("on");
      digitalWrite(fan1, LOW);
      delay(10);
    }
    else if (messageTemp == "off") {
      Serial.println("off");
      //      digitalWrite(ledPin, LOW);
      digitalWrite(fan1, HIGH);
      delay(10);
    }
  }
  if (String(topic) == "GrowBox/Fans/Fan02") {
    Serial.print("Changing output to ");
    if (messageTemp == "on") {
      Serial.println("on");
      digitalWrite(fan2, LOW);
      delay(10);
    }
    else if (messageTemp == "off") {
      Serial.println("off");
      //      digitalWrite(ledPin, LOW);
      digitalWrite(fan2, HIGH);
      delay(10);
    }
  }
  if (String(topic) == "GrowBox/Fans/Fan03") {
    Serial.print("Changing output to ");
    if (messageTemp == "on") {
      Serial.println("on");
      digitalWrite(fan3, LOW);
      delay(10);
    }
    else if (messageTemp == "off") {
      Serial.println("off");
      //      digitalWrite(ledPin, LOW);
      digitalWrite(fan3, HIGH);
      delay(10);
    }
  }
    if (String(topic) == "GrowBox/Motors") {
    Serial.print("Changing output to ");
    if (messageTemp == "on") {
      Serial.println("on");
      digitalWrite(motors, LOW);
      delay(10);
    }
    else if (messageTemp == "off") {
      Serial.println("off");
      //      digitalWrite(ledPin, LOW);
      digitalWrite(motors, HIGH);
      delay(10);
    }
  }

      if (String(topic) == "GrowBox/GrowLight") {
    Serial.print("Changing output to ");
    if (messageTemp == "on") {
      Serial.println("on");
//      digitalWrite(growLight, LOW);
      digitalWrite(growLight, LOW);
      delay(10);
    }
    else if (messageTemp == "off") {
      Serial.println("off");
      //      digitalWrite(ledPin, LOW);
      digitalWrite(growLight, HIGH);
      delay(10);
    }
  }

        if (String(topic) == "GrowBox/AllLights") {
    Serial.print("Changing output to ");
    if (messageTemp == "on") {
      Serial.println("on");
      digitalWrite(light1, LOW);
      digitalWrite(light2, LOW);
      digitalWrite(light3, LOW);
      delay(10);
    }
    else if (messageTemp == "off") {
      Serial.println("off");
      //      digitalWrite(ledPin, LOW);
      digitalWrite(light1, HIGH);
      digitalWrite(light2, HIGH);
      digitalWrite(light3, HIGH);
      delay(10);
    }
  }

  if (String(topic) == "GrowBox/AllFans") {
    Serial.print("Changing output to ");
    if (messageTemp == "on") {
      Serial.println("on");
      digitalWrite(fan1, LOW);
      digitalWrite(fan2, LOW);
      digitalWrite(fan3, LOW);
      delay(10);
    }
    else if (messageTemp == "off") {
      Serial.println("off");
      //      digitalWrite(ledPin, LOW);
      digitalWrite(fan1, HIGH);
      digitalWrite(fan2, HIGH);
      digitalWrite(fan3, HIGH);
      delay(10);
    }
  }
          if (String(topic) == "GrowBox/AllControls") {
    Serial.print("Changing output to ");
    if (messageTemp == "on") {
      Serial.println("on");
      digitalWrite(light1, LOW);
      digitalWrite(light2, LOW);
      digitalWrite(light3, LOW);
      digitalWrite(fan1, LOW);
      digitalWrite(fan2, LOW);
      digitalWrite(fan3, LOW);
      digitalWrite(growLight, LOW);
      digitalWrite(motors, LOW);
      delay(10);
    }
    else if (messageTemp == "off") {
      Serial.println("off");
      //      digitalWrite(ledPin, LOW);
      digitalWrite(light1, HIGH);
      digitalWrite(light2, HIGH);
      digitalWrite(light3, HIGH);
      digitalWrite(fan1, HIGH);
      digitalWrite(fan2, HIGH);
      digitalWrite(fan3, HIGH);
      digitalWrite(growLight, HIGH);
      digitalWrite(motors, HIGH);
      delay(10);
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
       digitalWrite(LED_BUILTIN,HIGH);
        delay(50);
        digitalWrite(LED_BUILTIN,LOW);
        delay(50);
        digitalWrite(LED_BUILTIN,HIGH);
        delay(50);
        digitalWrite(LED_BUILTIN,LOW);
        delay(50);
         digitalWrite(LED_BUILTIN,HIGH);
        delay(50);
        digitalWrite(LED_BUILTIN,LOW);
        delay(50);
      // Subscribe
      //      client.subscribe("GrowBox");
      client.subscribe("GrowBox/Lights/Light01");
      client.subscribe("GrowBox/Lights/Light02");
      client.subscribe("GrowBox/Lights/Light03");
      client.subscribe("GrowBox/Fans/Fan01");
      client.subscribe("GrowBox/Fans/Fan02");
      client.subscribe("GrowBox/Fans/Fan03");  
      client.subscribe("GrowBox/Motors");
      client.subscribe("GrowBox/GrowLight");
      client.subscribe("GrowBox/AllLights");
      client.subscribe("GrowBox/AllFans");
      client.subscribe("GrowBox/AllControls");
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
    long now = millis();
    if (now - lastMsg > 5000) {
      
      lastMsg = now;

    //Humidity
    double h = dht.readHumidity();
    double t = dht.readTemperature();
    double hic = dht.computeHeatIndex(t, h, false);


    char tempString[8];
    char humString[8];
    char heatString[8];


     dtostrf(t, 1, 2, tempString);     
     dtostrf(h, 1, 2, humString);
     dtostrf(hic, 1, 2, heatString);

     Serial.println(tempString);
     Serial.println(humString);
     Serial.println(heatString);
     delay(100);


     //Publish for the topics
     client.publish("GrowBox/Temperature", tempString);
     client.publish("GrowBox/Humidity", humString);
     client.publish("GrowBox/HeatIndex", heatString);
     

    }
}
