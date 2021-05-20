 #include <Motor_RS.h>
 #include <SoftwareSerial.h>
Motor_RS leftMotor(2,3);
Motor_RS rightMotor(4,5);
SoftwareSerial comms(12,11);

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
comms.begin(115200);
Serial.print("Code Started");
comms.println("Comms Started");

}

void moveForward(){
  leftMotor.forward();
  rightMotor.forward();
}
void moveLeft(){
  leftMotor.back();
  rightMotor.forward();
}
void moveRight(){
  leftMotor.forward();
  rightMotor.back();
}
void moveBack(){
  leftMotor.back();
  rightMotor.back();
}
void stopBot(){
  leftMotor.stop(); 
  rightMotor.stop();
}

void getVal(int val[3],int command){
  comms.println(command);
  while(!comms.available()){
  Serial.print(".");
  delay(500);
  }
  Serial.println(" ");
  String values=comms.readString();
  //return command;
    int ind[4],z=0;
//  String values=getAverage();
  for(int i=0;i<values.length();i++){
    if(isWhitespace(values[i])){
      ind[z]=i;
      z++;
      }}
  val[0]=values.substring(0,ind[0]).toInt();
  val[1]=values.substring(ind[1]+1,ind[2]).toInt();
  val[2]=values.substring(ind[2]+1,values.length()).toInt();
  Serial.print("AVERAGE VALUES FROM ARDUINO: ");
  for(int i=0;i<3;i++){
    Serial.print(val[i]);
    Serial.print(" ");
  }
  Serial.println(" ");
}


void calibrate(int cal[3]){
  
}


void loop() {
  int val[3];
  if(Serial.available()){
    int command=Serial.parseInt();
    if(command!=0){
    Serial.println(command);
  getVal(val,command);
  Serial.println("");
  for(int i=0;i<3;i++){
    Serial.print(val[i]);
    Serial.print(" ");
  }
}}

delay(2000);

}





















  
//  int val[3],ind[4],z=0;
//  String values=getAverage();
//  for(int i=0;i<values.length();i++){
//    if(isWhitespace(values[i])){
//      ind[z]=i;
//      z++;
//      }}
//  val[0]=values.substring(0,ind[0]).toInt();
//  val[1]=values.substring(ind[1]+1,ind[2]).toInt();
//  val[2]=values.substring(ind[2]+1,values.length()).toInt();
//  Serial.print("AVERAGE VALUES FROM ARDUINO: ");
//  for(int i=0;i<3;i++){
//    Serial.print(val[i]);
//    Serial.print(" ");
//  }
//  Serial.println(" ");
