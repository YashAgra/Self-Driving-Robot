
#include <ESP8266WiFi.h>
int sum[3],avg[3],i=0;
const char* ssid_hm="Hotel Motherhood";
const char* pass_hm="9319898255";
const char* ssid_rj="Raj Jio";
const char* ssid_dl="D-Link";
const char* pass_rj="9634972600";
const char* pass_dl="9634972600";
IPAddress staticIP(192,168,0,110);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
//=======================================================================
//                     SETUP
//=======================================================================
void setup() {
  Serial.begin(115200);
  Serial.println(""); //Remove garbage
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid_hm,pass_hm);
  Serial.print("Connection Initiated");
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("WiFi Network Scan Started");
}

//=======================================================================
//                        LOOP
//=======================================================================
void getAverage() {
  for(int j=0;j<10;j++){
  int hm,rj,dl;
  int n = WiFi.scanNetworks();
  
  if (n == 0)
  Serial.println("No Networks Found");
  else{ 
    for (int i = 0; i < n; i++)
    {
      int rssi=WiFi.RSSI(i);
      String ssid=WiFi.SSID(i);
      float percent=100*(1-(-20-rssi)/(-20+80));
      if(ssid=="Hotel Motherhood")
        hm=rssi;
      if(ssid=="Raj Jio")
        rj=rssi;
      if(ssid=="D-Link")
        dl=rssi;
    }
   
  sum[0]=sum[0]+hm;
  sum[1]=sum[1]+rj;
  sum[2]=sum[2]+dl;
  }}
  
    for(int i=0;i<3;i++){
      avg[i]=sum[i]/10;
    }
    Serial.print(avg[0]);
    
    Serial.print("  ");
    Serial.print(avg[1]);
    
    Serial.print("  ");
    Serial.print(avg[2]);    
    for(int i=0;i<3;i++){
      sum[i]=0;
      avg[i]=0;
    }
}
void scanNetwork(){
    int hm,rj,dl;
  int n = WiFi.scanNetworks();
  if (n == 0)
  Serial.println("No Networks Found");
  else{ 
    for (int i = 0; i < n; ++i)
    {
      int rssi=WiFi.RSSI(i);
      String ssid=WiFi.SSID(i);
      float percent=100*(1-(-20-rssi)/(-20+80));
      if(ssid=="Hotel Motherhood")
      hm=rssi;
      if(ssid=="Raj Jio")
      rj=rssi;
      if(ssid=="D-Link")      
      dl=rssi;
  }
    Serial.print(hm);
    
    Serial.print("  ");
    Serial.print(rj);
    
    Serial.print("  ");
    Serial.println(dl); 
    
  }

}


void calibrate(){
   
}



void loop(){
  int command=7;
    if(Serial.available()){
      command=Serial.parseInt();
    }
   
if(command==1){
  scanNetwork();

}
if(command==2){
  getAverage();
}
}

  
