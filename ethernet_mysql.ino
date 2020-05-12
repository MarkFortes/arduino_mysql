#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ipServer(192,168,1,146);
IPAddress ipClient(192,168,1,150);

EthernetClient client;

int t = 20;
int h = 25;

void setup(){
  Serial.begin(9600);
  while(!Serial){
      
  }

  if(Ethernet.begin(mac) == 0){
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac,ipClient);
  }

  delay(1000);
  Serial.println("connecting...");

  if(client.connect(ipServer, 80)){
    Serial.println("connected");
    /*client.print("GET /arduino_mysql/mysql.php?temperature=61&humidity=94");*/
    client.print("GET /arduino_mysql/mysql.php?temperature=");  
    client.print(t);
    client.print("&humidity=");
    client.print(h);  
    client.println(" HTTP/1.0");
    client.println("Connection: close");
    client.println();

    client.println();
  }else{
    Serial.println("connection failed");
  }
}

void loop(){
  if(client.available()){
    char c = client.read();
    Serial.print(c);
  }

  if(!client.connected()){
    Serial.println();
    Serial.println("disconnecting");
    client.stop();

    while(true);
  }
}
