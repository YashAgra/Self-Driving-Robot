 #include <Motor_RS.h>
 #include <SoftwareSerial.h>
Motor_RS leftMotor(2,3);
Motor_RS rightMotor(4,5);
SoftwareSerial bluetooth(12,11);   //rx,tx
SoftwareSerial wifi(8,9);  //rx,tx

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
bluetooth.begin(9600);
wifi.begin(4800);
Serial.println("Code Started");

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
  wifi.println(command);
  wifi.listen();
  while(!wifi.available()){
  Serial.print(".");
  delay(500);
  }
  Serial.println(" ");
  String values=wifi.readString();
  Serial.print("Values: ");
  Serial.println(values);
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
  for(int k=0;k<3;k++){
    bluetooth.print(val[k]);
    bluetooth.print(" ");
  }
  Serial.println(" ");
  bluetooth.println(" ");
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
  Serial.println(" ");
}}


//...................Control Robot.................................................

bluetooth.listen();
if(bluetooth.available()){
  Serial.print("bluetooth Available ");
  int c =bluetooth.read();
  Serial.println(c);
  switch(c){
    case 8:
      moveForward();
      break;
    case 2:
    moveBack();
    break;
    case 4:
    moveLeft();
    break;
    case 6:
    moveRight();
    break;
    case 0:
    stopBot();
    break;
    case 5:
    getVal(val,1);
    break;
    case 53:
    getVal(val,1);
    break;
    case 1:
    getVal(val,2);
    break;
    case 49:
    getVal(val,2);
    break;
    case 3:
    getVal(val,3);
    break;
    case 51:
    getVal(val,3);
    break;
    default:
    stopBot();
  }
}


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
