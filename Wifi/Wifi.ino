#include<SoftwareSerial.h>
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
SoftwareSerial arduino(D6,D5);
//=======================================================================
//                     SETUP
//=======================================================================
void setup() {
  Serial.begin(9600);
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
  arduino.begin(4800);
  arduino.print("");
}

//=======================================================================
//                        LOOP
//=======================================================================
void scanNetwork(int arr[3],bool printv){
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
    
    if(hm<0 && hm>-100)
    arr[0]=hm;
    
    if(rj<0 && rj>-100)
    arr[1]=rj;
    
    
    if(dl<0 && dl>-100)
    arr[2]=dl;
    if(printv){
    Serial.print("Printing from scan networks: ");  
    Serial.print(hm);
    Serial.print("  ");
    Serial.print(rj);
    Serial.print("  ");
    Serial.println(dl);
    arduino.print(hm);
    arduino.print("  ");
    arduino.print(rj);
    arduino.print("  ");
    arduino.print(dl);
    }
    }
}




void getAverage() {
  for(int j=0;j<10;j++){
  int val[3];
  scanNetwork(val,false);
  Serial.println("Scan Netwrks Finished---get average");
  for(int i=0;i<3;i++){
  sum[i]=sum[i]+val[i];
  }}
  
    for(int i=0;i<3;i++){
      avg[i]=sum[i]/10;
    }
  
    Serial.print(avg[0]);
    Serial.print("  ");
    Serial.print(avg[1]);
    Serial.print("  ");
    Serial.println(avg[2]);
    arduino.print(avg[0]);
    arduino.print("  ");
    arduino.print(avg[1]);
    arduino.print("  ");
    arduino.print(avg[2]);
    for(int i=0;i<3;i++){
      sum[i]=0;
      avg[i]=0;
    }
}



void getAverage1(){
  Serial.println("GetAverage1 initiated");
  float kg[3],ee[3][2],est[3][2],em=5;
  for(int i=0;i<3;i++){
  ee[i][0]=2;
  est[i][0]=0.00;
  }
  int rssi[3];
  for(int i=0;i<=15;i++){
    
    scanNetwork(rssi,false);
    
    for(int j=0;j<3;j++){
      if(est[j][0]==0.00)
      est[j][0]=rssi[j];
      Serial.print(rssi[j]);
      Serial.print(" ");
      kg[j]=ee[j][0]/(ee[j][0]+em);  //eqn 1
      est[j][1]=est[j][0]+kg[j]*(rssi[j]-est[j][0]);  //eqn2
      ee[j][1]=(1-kg[j])*ee[j][0];   //eqn3
      ee[j][0]=ee[j][1];
      est[j][0]=est[j][1];
  }
  Serial.println(" ");
  }
  Serial.println("");
  for(int i=0;i<3;i++){
  Serial.print(est[i][1]);
  Serial.print(" ");
  est[i][1]=est[i][1]+0.5;    //conversion of float to int 
  int x=est[i][1];
  arduino.print(x);
  arduino.print("  ");
  }
  delay(2000);
  Serial.println("");
}



void loop(){
  int command=7;
    if(Serial.available()){
      command=Serial.parseInt();
    }
    if(arduino.available()){
      command=arduino.parseInt();
    }
   
if(command==1){
  int arr[3];
  scanNetwork(arr,true);

}
if(command==2){
  getAverage();
}
if(command==3)
getAverage1();
}

  
