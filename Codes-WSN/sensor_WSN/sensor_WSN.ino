//Στα πλαίσια του demo αυτό το arduino δεν στέλνει δεδομένα κάπου. Σε πιθανή προέκταση που αναφέρετε στην αναφορά μπορεί να στέλνει δεδομένα στον receiver.  
/*#include <RF22.h>
#include <RF22Router.h>
#define MY_ADDRESS 14
#define DESTINATION_ADDRESS 5
RF22Router rf22(MY_ADDRESS); 
long randNumber;
boolean successful_packet = false;
int max_delay=3000;
int counter = 0;
int Data[6] = 0;
//int initial_time = 0;
//int final_time = 0;
//float throughput = 0;
//int flag_measurement = 0;
//int number_of_bytes = 0;
//////////////////////Επικοινωνία-Κεραία*/

#include <LedControl.h>
int DIN = 13;
int CS = 12;
int CLK = 11;

int echoPin1 = 10;
int trigPin1 = 9;
long duration1, distance1;

int echoPin2 = 8;
int trigPin2 = 7;
long duration2, distance2;

int echoPin3 = 6;
int trigPin3 = 5;
long duration3, distance3;


int pinLaser5 = 2; // output signal pin of laser module/laser pointer
const int pinReceiver5 = 2;
long distance5;


int pinLaser4 = 1; // output signal pin of laser module/laser pointer
const int pinReceiver4 = 1;
long distance4;


int echoPin6 = 4;
int trigPin6 = 3;
long duration6, distance6;

/*int echoPin5 = 2;
int trigPin5 = 1;
long duration5, distance5;*/



int Num[6];
int i;
//////////////////////////////






byte N1[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03};
byte N2[8] = {0x00,0x00,0x00,0x0f,0x0f,0x0c,0x0c,0x0c};
byte N3[8] = {0x0f,0x0f,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c};
byte N4[8] = {0xfc,0xfc,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c};
byte N5[8] = {0x3c,0x3c,0x2c,0xec,0xec,0x0c,0x0c,0x0c};
byte N6[8] = {0x3c,0x3c,0x2c,0x2c,0x2c,0x2c,0xec,0xec};
byte keno[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
LedControl lc = LedControl(DIN, CLK, CS, 0);

void printByte(byte character [])
{
    int i = 0;
    for(i=0;i<8;i++)
    {
       lc.setRow(0,i,character[i]);
    }
}

void setup() {
  // put your setup code here, to run once:
   pinMode(pinLaser4, OUTPUT); // set the laser pin to output mode
   pinMode(pinReceiver4, INPUT); // set the laser pin to output mode
   digitalWrite(pinLaser4, HIGH); // emit red laser

   pinMode(pinLaser5, OUTPUT); // set the laser pin to output mode
   pinMode(pinReceiver5, INPUT); // set the laser pin to output mode
   digitalWrite(pinLaser5, HIGH); // emit red laser

 
  pinMode(echoPin1, INPUT);
  pinMode(trigPin1, OUTPUT);

  pinMode(echoPin2, INPUT);
  pinMode(trigPin2, OUTPUT);

  pinMode(echoPin3, INPUT);
  pinMode(trigPin3, OUTPUT);

  /*pinMode(echoPin4, INPUT);
  pinMode(trigPin4, OUTPUT);*/

  pinMode(echoPin6, INPUT);
  pinMode(trigPin6, OUTPUT);
  
  lc.shutdown(0, false);
  lc.setIntensity(0, 15);
  lc.clearDisplay(0);

  for(i = 0; i < 6; i=i+1){
    Num[i] = 0;
    }

  Serial.begin(9600);
   //////////////////////////////////Επικοινωνία-Κεραία
  /*if (!rf22.init())
    Serial.println("RF22 init failed");
  // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36
  if (!rf22.setFrequency(431.0))
    Serial.println("setFrequency Fail");
  rf22.setTxPower(RF22_TXPOW_20DBM);
  //1,2,5,8,11,14,17,20 DBM
  //rf22.setModemConfig(RF22::OOK_Rb40Bw335  );
  rf22.setModemConfig(RF22::GFSK_Rb125Fd125);
  //modulation

  // Manually define the routes for this network
  rf22.addRouteTo(DESTINATION_ADDRESS, DESTINATION_ADDRESS);
  randomSeed(Num); //(μία μόνο φορά μέσα στην setup)
   //////////////////////////////////Επικοινωνία-Κεραία*/


}

void loop() {
  // put your main code here, to run repeatedly:
  
 

 
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 / 58.2;
  Serial.print("distance1 = ");
  Serial.print(distance1);
  Serial.println("CM");

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 / 58.2;
  Serial.print("distance2 = ");
  Serial.print(distance2);
  Serial.println("CM");

  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3 / 58.2;
  Serial.print("distance3 = ");
  Serial.print(distance3);
  Serial.println("CM");

  /*digitalWrite(trigPin4, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin4, LOW);
  duration4 = pulseIn(echoPin4, HIGH);
  distance4 = duration4 / 58.2;
  Serial.print("distance4 = ");
  Serial.print(distance4);
  Serial.println("CM");*/

  digitalWrite(trigPin6, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin6, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin6, LOW);
  duration6 = pulseIn(echoPin6, HIGH);
  distance6 = duration6 / 58.2;
  Serial.print("distance6 = ");
  Serial.print(distance6);
  Serial.println("CM");

   distance4 = digitalRead(pinReceiver4); 
   Serial.println(distance4); 

   distance5 = digitalRead(pinReceiver5); 
   Serial.println(distance5); 

  
  if(distance1 > 6){
    printByte(N1);
    Num[0] = 0;
    }
  else if(distance2 > 6){
    printByte(N2);
    Num[1] = 0;
    }
  else if(distance3 > 6){ 
    printByte(N3);
    Num[2] = 0;
    }
  else if(distance4 > 6){ 
    printByte(N4);
    Num[3] = 0;
    }
  else if(distance5 > 6){ 
    printByte(N5);
    Num[4] = 0;
    }
    else if(distance6 > 6){ 
    printByte(N6);
    Num[5] = 0;
    }
   else{
        printByte(keno);

    }

  if(distance1 < 6){
    Num[0] = 1;
    }
  if(distance2 < 6){
    Num[1] = 1;
    }
  if(distance3 < 6){ 
    Num[2] = 1;
    }
  if(distance4 < 6){ 
    Num[3] = 1;
    }
  if(distance5 < 6){ 
   Num[4] = 1;
    }
  if(distance6 < 6){ 
     Num[5] = 1;
    }

  Serial.print("Num1 = ");
  Serial.println(Num[0]);
  Serial.print("Num2 = ");
  Serial.println(Num[1]);
  Serial.print("Num3 = ");
  Serial.println(Num[2]);
  Serial.print("Num4 = ");
  Serial.println(Num[3]);
  Serial.print("Num5 = ");
  Serial.println(Num[4]);
  Serial.print("Num6 = ");
  Serial.println(Num[5]);


  
  /*counter = 0; //Επικοινωνία
  //initial_time = millis(); //Επικοινωνία
  char data_read[RF22_ROUTER_MAX_MESSAGE_LEN];  //Επικοινωνία
  uint8_t data_send[RF22_ROUTER_MAX_MESSAGE_LEN];  //Επικοινωνία
  /////////////////////////////////////////////Επικοινωνία-Κεραία
    
    
    
    memset(data_read, '\0', RF22_ROUTER_MAX_MESSAGE_LEN);
    memset(data_send, '\0', RF22_ROUTER_MAX_MESSAGE_LEN);
    sprintf(data_read, "%d", Data);
    data_read[RF22_ROUTER_MAX_MESSAGE_LEN - 1] = '\0';
    memcpy(data_send, data_read, RF22_ROUTER_MAX_MESSAGE_LEN);
   
  
    successful_packet = false;
    while (!successful_packet)
    {
  
      if (rf22.sendtoWait(data_send, sizeof(data_send), DESTINATION_ADDRESS) != RF22_ROUTER_ERROR_NONE)
      {
       // Serial.println("sendtoWait failed");
        randNumber=random(200,max_delay);
        //Serial.println(randNumber);
        delay(randNumber);
      }
      else
      {
        successful_packet = true;
        counter = counter + 1;  
        Serial.println("sendtoWait Succesful");
      } 
      Serial.println("Data = " + String(Data));
    }
    //final_time=millis();
    //throughput=(float)counter*number_of_bytes*1000.0/(final_time-initial_time); // *1000 is because time is measured in ms. This is not the communication throughput, but rather each measurement-circle throughput.
    //Serial.print("Throughput=");
    //Serial.print(throughput);
    //Serial.println("Bytes/s");
    //Serial.print("Initial time= ");  
    //Serial.print(initial_time);
    //Serial.print("     Final time= ");  
    //Serial.println(final_time);


  
  /////////////////////////////////////////////Επικοινωνία-Κεραία
  */

  delay(2000);


}
