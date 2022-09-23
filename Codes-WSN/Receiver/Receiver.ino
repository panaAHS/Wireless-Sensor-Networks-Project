#include <LiquidCrystal.h>
#include <RF22.h>
#include <RF22Router.h>
#define MY_ADDRESS 5
#define NODE_ADDRESS_1 12
#define NODE_ADDRESS_2 13
RF22Router rf22(MY_ADDRESS);
//#define NODE_ADDRESS_3 14


LiquidCrystal lcd(7, 6, 5, 4, 3, 8);
String free_slots_p1 = "6";
String free_slots_p2 = "6";
int received_value = 0; 

void setup() {
  Serial.begin(9600);
  if (!rf22.init())
    Serial.println("RF22 init failed");
  // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36
  if (!rf22.setFrequency(431.0))
    Serial.println("setFrequency Fail");
  rf22.setTxPower(RF22_TXPOW_20DBM);
  //1,2,5,8,11,14,17,20 DBM
  rf22.setModemConfig(RF22::GFSK_Rb125Fd125);
  //modulation

  // Manually define the routes for this network
  rf22.addRouteTo(NODE_ADDRESS_1, NODE_ADDRESS_1);
  rf22.addRouteTo(NODE_ADDRESS_2, NODE_ADDRESS_2);
  //rf22.addRouteTo(NODE_ADDRESS_3, NODE_ADDRESS_3);
  
  lcd.begin(16, 2);   // Init the LCD for 16 chars 2 lines
  lcd.setCursor(0,0); //First line of lcd
  lcd.print("Parking slots" );
  lcd.setCursor(0,1); //Second line of lcd
  lcd.print("P1: " + String(free_slots_p1) + "  " + "P2: " + String(free_slots_p2));


}

void loop() {
  uint8_t buf[RF22_ROUTER_MAX_MESSAGE_LEN];
  char incoming[RF22_ROUTER_MAX_MESSAGE_LEN];
  memset(buf, '\0', RF22_ROUTER_MAX_MESSAGE_LEN);
  memset(incoming, '\0', RF22_ROUTER_MAX_MESSAGE_LEN);
  uint8_t len = sizeof(buf);
  uint8_t from;
  
  if (rf22.recvfromAck(buf, &len, &from))
  {
    buf[RF22_ROUTER_MAX_MESSAGE_LEN - 1] = '\0';
    memcpy(incoming, buf, RF22_ROUTER_MAX_MESSAGE_LEN);
    Serial.print("got request from : ");
    Serial.println(from, DEC);
    received_value = atoi((char*)incoming);
    Serial.println(received_value);
 //   delay(1000);
  }
  
    if(from == 12){
    free_slots_p1 = (received_value);
    if(received_value == 1999){
      free_slots_p1 = "0";
      Serial.println("Call 199");
      Serial.println("Call 199");
      Serial.println("Call 199");
      }
    else{
      Serial.print("P1: ");
      Serial.println(free_slots_p1);
      }
    
    }
  else if(from == NODE_ADDRESS_2){
    free_slots_p2 = (received_value);
    
    if(received_value == 1999){
      free_slots_p2 = "0";
      Serial.println("Call 199");
      Serial.println("Call 199");
      Serial.println("Call 199");
      }
     else{
      Serial.print("P2: ");
      Serial.println(free_slots_p2);
      }
    }

  lcd.setCursor(0,1); //First line
  lcd.print("P1: " + (free_slots_p1) + "  " + "P2: " + (free_slots_p2));
  

  
}
