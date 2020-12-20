// luuvachiase.net- ngoctuansqtt@gmail.com
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

//=========================NGƯỜI DÙNG TỰ ĐỊNH NGHĨA==========================//
const char* ssid     = "xxxx";  
const char* password =  "xxxxx";
const char* host     = "your_host"; //luuvachiase.000webhostapp.com
//=========================KHAI BÁO CÁC BIẾN TOÀN CỤC===========================//
  
String path          = "/test/tuan.json";  
String line;
const char* pwm;
char tes;
int count=0;
bool json_ok =0,en=0;
String tuan;
String section="message";

unsigned long number;
//====================================SETUP BAN ĐẦU, CHẠY 1 LẦN DUY NHẤT============//

void setup() {  
WiFi.softAPdisconnect (true); // Tắt chức năng quảng bá SSID của AP.

  pinMode(2, OUTPUT); // Led bao trang thai ket noi server ok
  pinMode(10, OUTPUT); // Led bao trang thai ket noi wifi ok
  pinMode(12, OUTPUT); // chan dieu khien relay
  
  digitalWrite(2, HIGH); // Mức logic 1 là tắt led, logic 0 là sáng led
  digitalWrite(12, HIGH);
  digitalWrite(10, HIGH);
     
  Serial.begin(9600);

  delay(10);
  Serial.print("Connecting to Wifi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(10, HIGH); 
    delay(500);
    Serial.print(".");
    digitalWrite(10, LOW); 
    delay(500);
  }
  Serial.println("Connected!");  

}
//====================================================================//
void loop() {  
  Serial.print("Connect to IoT-server");
  Serial.println(host);
  WiFiClient client;
  
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connect to server fail!");  
    if(WiFi.status() != WL_CONNECTED)
      {
        digitalWrite(10, HIGH); // Nếu mất kết nối với wifi thì Led 10 sẽ tắt
        delay(500);
        Serial.print(".");
        digitalWrite(10, LOW);
        delay(300);
      }
    return;
  }
  

digitalWrite(10, LOW); //ok Nếu kết nối với Server thành công LED 10 sẽ sáng
while(1)
{
  
        if(count==1)
          {            
            Serial.print("No response:");  
            digitalWrite(2, HIGH); 
            count=0;                 
            break;                 
          }
        
 // Nếu lần kết nối trước không thành công thì kết nối lại                           
      
  Serial.println("Send request");

                client.print(String("GET ") + path + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" + 
                "Connection: keep-alive\r\n\r\n");
               
               
  digitalWrite(2, HIGH);
  
  delay(1000); // wait for server to respond
  count=1; 
//============================================= read response=================================
    while(client.available()){
    count=2; 
     // Serial.println("Data available!"); // chi để kiểm tra có nhận dc data ko
      digitalWrite(2, LOW); //ok
    
 //=====================================   
    if(json_ok==false)
    {
      line = client.readStringUntil('\r');
     //Serial.println(line); 
      en=false;
    }
    else
    {  
      line = client.readStringUntil('}'); 
      int find_json = line.indexOf('{');
      
      if(find_json<0) Serial.println("NOT JSON==>SKIP DATA"); 
      else {tuan=line+"}"; en=true;Serial.println(tuan);}
      json_ok=false;  
    }
//=======================================    
        if (line=="\n") 
        { 
          section="json";
          json_ok=true;
        }
        else 
        {
          section="header";
        }

//=========================================        

      if(en==true) // Nếu response là json
      {     
         String result = tuan.substring(1);
         line="";
              
// ===============Parse JSON===============
      int size = result.length()+1;
      char json[size];
      result.toCharArray(json, size);
      DynamicJsonBuffer jsonBuffer(size);
      JsonObject& json_parsed = jsonBuffer.parseObject(json);
      if (!json_parsed.success())
      {
        Serial.println("parseObject() failed");
        break;
      }
      else   
//============can read value=============
      
         pwm=json_parsed["led1"];
         number = strtoul(pwm, NULL, 10);
         analogWrite(16,number);
         Serial.println(number);         
  //=============end value==================
                  
  }//end if(en==true)

} // end while client_available 
    

                          
}// while
}// loop
