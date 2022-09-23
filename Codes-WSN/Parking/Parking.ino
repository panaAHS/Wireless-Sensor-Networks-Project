#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h> 

/////////////////////// Επικοινωνία-Κεραία
#include <RF22.h>
#include <RF22Router.h>
#define MY_ADDRESS 12
#define DESTINATION_ADDRESS 5
RF22Router rf22(MY_ADDRESS);

long randNumber;
int successful_packet = 0;
int max_delay=3000;
int counter = 0;
int Data = 0;
//int initial_time = 0;
//int final_time = 0;
//float throughput = 0;
//int flag_measurement = 0;
//int number_of_bytes = 0;
//////////////////////Επικοινωνία-Κεραία

LiquidCrystal_I2C lcd(0x27, 16, 2);

int ServoPin = 3;
Servo s;
int ServoPin1 = 5;
Servo s1;

int Touchsensor = 4;
int button = A0;

int plirotita;
int max_plirotita = 6;
int old_plirotita;
int free_slots = 0;

int eisodos_led_red = 7;
int eisodos_led_green = 8;

int exit_led_red = 6;
int exit_led_green = 9;//1 sto p2 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

char Incoming_value = 0;

int BUZZER = 10;  

int input_sensor = A2; //
int exit_sensor = A1;


void setup() {
  // put your setup code here, to run once:
   pinMode(Touchsensor, INPUT);
   pinMode(button, INPUT);
   //pinMode(buzzer, OUTPUT);
   pinMode(eisodos_led_red, OUTPUT);
   pinMode(eisodos_led_green, OUTPUT);
   pinMode(exit_led_green, OUTPUT);
   pinMode(exit_led_red, OUTPUT);

   s.attach(ServoPin);
   s1.attach(ServoPin1);
   s1.write(0);
   s.write(0);
   Serial.begin(9600);


   lcd.begin();   // iInit the LCD for 16 chars 2 lines
   lcd.backlight();   // Turn on the backligt (try lcd.noBaklight() to turn it off)
   lcd.setCursor(3,0); //First line
   lcd.setCursor(1,0); //First line
   lcd.print("Parking slots" );

   plirotita = 0;
   free_slots = max_plirotita - plirotita;
   Serial.print("Parking slots: ");
   Serial.println("P1: " + String(free_slots));

   lcd.setCursor(1,1); //First line
   lcd.print("P1: " + String(free_slots));

   digitalWrite(eisodos_led_red, HIGH);
   digitalWrite(exit_led_red, HIGH);


    //////////////////////////////////Επικοινωνία-Κεραία
  if (!rf22.init())
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
  randomSeed(100); //(μία μόνο φορά μέσα στην setup)
   //////////////////////////////////Επικοινωνία-Κεραία


}

void loop() {
  // put your main code here, to run repeatedly:
  //fire_alarm analogRead(A3);
  old_plirotita = plirotita;
  counter = 0; //Επικοινωνία
    //initial_time = millis(); //Επικοινωνία
    char data_read[RF22_ROUTER_MAX_MESSAGE_LEN];  //Επικοινωνία
    uint8_t data_send[RF22_ROUTER_MAX_MESSAGE_LEN];  //Επικοινωνία
  if(Serial.available() > 0)  
  {
    Incoming_value = Serial.read();      
    Serial.print(Incoming_value);        
    Serial.print("\n");

    while(Incoming_value == '9'){
 
      Serial.println("Contol Mode");
      delay(4000);
      Incoming_value = Serial.read();
      if(Incoming_value == '0'){
        Serial.println("max_plirotita = ???");
        max_plirotita = int(Serial.read()) - 48;
        Serial.println(String(max_plirotita));
        }
      else if(Incoming_value == '1'){
        plirotita += 1;
        Serial.println("Parking P1: " + String(free_slots));
        lcd.clear();
        lcd.setCursor(1,0); 
        lcd.print("Parking slots" );
        free_slots = max_plirotita - plirotita;
        Data = free_slots;
        Serial.print("Parking slots: ");
        Serial.println("P1: " + String(free_slots));
        lcd.setCursor(1,1); //First line
        lcd.print("P1: " + String(free_slots));
        }
      else if(Incoming_value == '2'){
        lcd.clear();
        lcd.setCursor(1,0); //First line
        lcd.print("Parking slots" );
        plirotita -= 1;
        free_slots = max_plirotita - plirotita;
        Data = free_slots;
        Serial.print("Parking slots: ");
        Serial.println("P1: " + String(free_slots));
        lcd.setCursor(1,1); //First line
        lcd.print("P1: " + String(free_slots));
        }
      else if(Incoming_value == '3'){
        plirotita = 0;
        lcd.clear();
        lcd.setCursor(1,0); 
        lcd.print("Parking slots" );
        free_slots = max_plirotita - plirotita;
        Data = free_slots;
        Serial.print("Parking slots: ");
        Serial.println("P1: " + String(free_slots));
        lcd.setCursor(1,1); //First line
        lcd.print("P1: " + String(free_slots));
        
        }
      else if(Incoming_value == '4'){
        plirotita = max_plirotita;
        lcd.clear();
        lcd.setCursor(1,0); 
        lcd.print("Parking slots" );
        free_slots = max_plirotita - plirotita;
        Data = free_slots;
        Serial.print("Parking slots: ");
        Serial.println("P1: " + String(free_slots));
        
        lcd.setCursor(0,1); 
        lcd.print("Sorry, no spots");
        }
      else if(Incoming_value == '5'){
         s.write(90);
         s1.write(90);
        }
      else if(Incoming_value == '6'){
         s.write(0);
         s1.write(0);
         digitalWrite(exit_led_red, HIGH);
         digitalWrite(exit_led_green, LOW);
        }
    } 
  }
   

    if( analogRead(A3) < 500){
        lcd.clear();
        lcd.setCursor(5,0); 
        lcd.print("Warning");
        lcd.setCursor(0,1);
        lcd.print("Fire Fire Fire!");
        digitalWrite(eisodos_led_red, HIGH);
        digitalWrite(exit_led_green, HIGH);
        digitalWrite(exit_led_red, LOW);
        s1.write(90);
        s.write(90);

        for(int j = 300; j<700; j++)
            {
                tone(BUZZER, j);
                delay(10);
             }
        for(int j = 700; j>300; j--){
          tone(BUZZER, j);
          delay(10);
          }

         
          noTone(BUZZER);
          Serial.println("Stop");
          Serial.println("Detected Fire!");
          lcd.clear();
          lcd.setCursor(1,0); 
          lcd.print("Warining! FIRE!");
          lcd.setCursor(1,1); 
          lcd.print("P1: " + String(free_slots));
          Data = 1999;
         }
    
    if(digitalRead(Touchsensor)){
      plirotita += 1;
      if(plirotita > max_plirotita){
          plirotita = max_plirotita;
          free_slots = 0;
          
          
          lcd.clear();
          lcd.setCursor(4,0); 
          lcd.print("Parking" );
          Data = free_slots;
          Serial.print("Parking slots: ");
          Serial.println("P1: " + String(free_slots));
          
          lcd.setCursor(0,1); 
          lcd.print("Sorry, no spots");
  
          digitalWrite(eisodos_led_red, HIGH);
          digitalWrite(eisodos_led_green, LOW);
      }
      else{
  
          
          digitalWrite(eisodos_led_red, LOW);
          digitalWrite(eisodos_led_green, HIGH);
          
          s.write(90);
          delay(3000);
          
          lcd.clear();
          lcd.setCursor(1,0); 
          lcd.print("Parking slots" );
          free_slots = max_plirotita - plirotita;
          Data = free_slots;
          Serial.print("Parking slots: ");
          Serial.println("P1: " + String(free_slots));
          
          lcd.setCursor(0,1); 
          lcd.print("P1: " + String(free_slots));
            delay(3000);
         while(analogRead(input_sensor) > 200){
              delay(1);
            }
          if(analogRead(input_sensor) < 200){
              s.write(0);
          
      
              digitalWrite(eisodos_led_red, HIGH);
              digitalWrite(eisodos_led_green, LOW);
          
          }
          
  
    
          
          if(plirotita == max_plirotita){
            delay(1000);
            lcd.clear();
            lcd.setCursor(4,0); 
            lcd.print("Parking" );
            free_slots = 0;
            Data = free_slots;
            Serial.print("Parking slots: ");
            Serial.println("P1: " + String(free_slots));
            
            lcd.setCursor(0,1); 
            lcd.print("Sorry, no spots");
          }
      }
          
      
    }
    else if(analogRead(button) < 100 && (plirotita > 0)){
      delay(1000);
      plirotita -= 1;
      //if(/*digitalRead(Touchsensor) == 1 &&*/ (plirotita > 0))
      {
          digitalWrite(exit_led_red, LOW);
          digitalWrite(exit_led_green, HIGH);
  
          s1.write(90);
          delay(3000);
          
         lcd.clear();
         lcd.setCursor(1,0); 
         lcd.print("Parking slots" );
         free_slots = max_plirotita - plirotita;
         Data = free_slots;
         Serial.print("Parking slots: ");
         Serial.println("P1: " + String(free_slots));
        
         lcd.setCursor(0,1); 
         lcd.print("P1: " + String(free_slots));
          delay(3000);
          while(analogRead(exit_sensor) < 800){
              delay(1);
            }
          if(analogRead(exit_sensor) > 800){
              s1.write(0);
              digitalWrite(exit_led_red, HIGH);
              digitalWrite(exit_led_green, LOW);
          
          }
          
      }

 
      }
   if(plirotita != old_plirotita /*|| free_slots == max_plirotita*/ || Data == 1999){
     if(free_slots == max_plirotita){
        Data = free_slots;
      }
    
     Serial.println("Epikoinonia");
     Serial.println("Data = " + String(Data));
     //counter = 0; //Επικοινωνία
    //char data_read[RF22_ROUTER_MAX_MESSAGE_LEN];  //Επικοινωνία
    //uint8_t data_send[RF22_ROUTER_MAX_MESSAGE_LEN];  //Επικοινωνία
    /////////////////////////////////////////////Επικοινωνία-Κεραία
      
    
    
    memset(data_read, '\0', RF22_ROUTER_MAX_MESSAGE_LEN);
    memset(data_send, '\0', RF22_ROUTER_MAX_MESSAGE_LEN);
    sprintf(data_read, "%d", Data);
    data_read[RF22_ROUTER_MAX_MESSAGE_LEN - 1] = '\0';
    memcpy(data_send, data_read, RF22_ROUTER_MAX_MESSAGE_LEN);
    successful_packet = 0;

    while (!successful_packet)
    {
  
      if (rf22.sendtoWait(data_send, sizeof(data_send), DESTINATION_ADDRESS) != RF22_ROUTER_ERROR_NONE)
      {
        Serial.println("sendtoWait failed");
        randNumber=random(200,max_delay);
        Serial.println(randNumber);
        delay(randNumber);
      }
      else
      {
        successful_packet = 1;
        counter = counter + 1;  
        Serial.println("sendtoWait Succesful");
      } 
      Serial.println("Data = " + String(Data));
    }
   
  }
    
   
  

  
  

}
