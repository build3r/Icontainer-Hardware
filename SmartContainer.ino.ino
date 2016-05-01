
#include <math.h>
#include <SPI.h>
#include <WiFi.h>

String yourdata = "Shabaz Ahmed";
char ssid[] = "Agent47"; //  your network SSID (name) 
char pass[] = "12345678";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)
int i = -1;
int status = WL_IDLE_STATUS;
WiFiClient client;
char buff[400] = "0";

char data='0';
String postJson = "{\"deviceId\":\"5723ec3f529247160ad517a0\",\"data\":{\"containerId\" : 1,\"weight\":";
//5723ec3f529247160ad517a0
#define CONTAINER_ID 1
int incomingByte = 0;   // for incoming serial data
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
    if(status == WL_CONNECTED)
      Serial.println("Connected to wifi");
     else
     Serial.println("Connection Failed");
  //printWifiStatus();
}
int res = 0;
int prevRes=0;
String weight = "0.0";
// the loop function runs over and over again forever
void loop() {
  
 /*Serial.print(digitalRead(2));
 Serial.print(digitalRead(3)); 
 Serial.print(digitalRead(4));
 Serial.print(digitalRead(5));  
 
 Serial.print(digitalRead(6));
 Serial.print(digitalRead(7)); 
 
 Serial.print(digitalRead(8));  
  Serial.print(digitalRead(9)); 
 Serial.println("");*/
  res = 0;
  for(int i=0;i<8;i++)
  {
    Serial.print(digitalRead(9-i));
    Serial.print(" ");
    Serial.println(((int)pow(2,i)));
    res += (int)digitalRead(9-i)*((int)pow(2,i));
    
 //Serial.println(res);
   }
   if(res!=prevRes)
 {  
   if(res == 73 || res == 89)
   {
    weight = "0.0";
    Serial.println("Empty");
   }
   else if(res >73 && res <93) 
   {
    weight = "1.0";
     Serial.println("1 KG");
   }
   else if(res>106 && res <115)
   {
    weight = "2.0";
    Serial.println("2 KG");
   }
    else if(res>93 && res <106)
   {
    weight = "2.5";
    Serial.println("2.5 KG");
   }
    else if(res<93 && res >40)
   {
    weight = "1.5";
    Serial.println("1.5 KG");
   }
   else if(res <26)
   {
    weight = "0.5";
    Serial.println("0.5 KG");
   }
   post(weight);
}
 /* */
   prevRes = res;
  delay(1000);
}

void pl(String s)
{
  Serial.println(s);
 }
void post(String weight){
  String data = String(postJson+weight+"}}");
  pl(data);
IPAddress server1(192,168,1,87);
if (client.connected() || client.connect(server1, 3000)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("POST /api/dump HTTP/1.1");
    client.println("Host: {192,168,0,100}");
    client.println("User-Agent: Arduino/1.0");
    client.println("Content-Type: application/JSON; charset=UTF-8");
    client.println("Connection: Keep-Alive");
    client.print("Content-Length: ");
    client.println(data.length());


    client.println();
    
    
    client.println(data);
    Serial.print("sent data");
    
  pl(postJson);
}
else
{
  Serial.print("Could not connect to ");
 Serial.println(server1);
 //client.disconnect();
}
//delay (2000);
  //Serial.println("****************");
  while (client.available()) {
   char c = client.read();
    Serial.write(c);
  }

  //Serial.println(buff);

}
