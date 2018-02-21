// demo: CAN-BUS Shield, send data
#include <mcp_can.h>
#include <SPI.h>



#define UP     A1
#define DOWN   A3
#define LEFT   A2
#define RIGHT  A5
#define CLICK  A4


void setup()
{
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  Serial.begin(115200);
  // init can bus, baudrate: 500k
  if(CAN.begin(CAN_500KBPS) ==CAN_OK) Serial.print("can init ok!!\r\n");
  else Serial.print("Can init fail!!\r\n");

   //Initialize analog pins as inputs
  pinMode(UP,INPUT);
  pinMode(DOWN,INPUT);
  pinMode(LEFT,INPUT);
  pinMode(RIGHT,INPUT);
  pinMode(CLICK,INPUT);
  
  //Pull analog pins high to enable reading of joystick movements
  digitalWrite(UP, HIGH);
  digitalWrite(DOWN, HIGH);
  digitalWrite(LEFT, HIGH);
  digitalWrite(RIGHT, HIGH);
  digitalWrite(CLICK, HIGH);
}

unsigned int stmp[8] = {0, 1, 2, 3, 4, 5, 6, 7};
int id = 0;
void loop()
{
//Joystick input to switch speed of CAN
  //
   if (digitalRead(LEFT) == 0) {
       
       if(CAN.begin(CAN_500KBPS) == CAN_OK)  //Initialise MCP2515 CAN controller at the specified speed
       {
          Serial.println("CAN Init at 500kBAUD ok");
          digitalWrite(8, HIGH);
          digitalWrite(7, LOW);
       }
        else
          Serial.println("Can't init CAN");
          
          delay(1000);

       }
   
   if (digitalRead(RIGHT) == 0) {
       if(CAN.begin(CAN_125KBPS) == CAN_OK)  //Initialise MCP2515 CAN controller at the specified speed
       {
        Serial.println("CAN Init at 125kBAUD ok");
        digitalWrite(8, LOW);
        digitalWrite(7, HIGH);
       }
      else
        Serial.println("Can't init CAN");
        
        delay(1000);

       }

   if (digitalRead(CLICK) == 0) {
       if(CAN.begin(CAN_5KBPS) == CAN_OK)  //Initialise MCP2515 CAN controller at the specified speed
       {
        Serial.println("CAN Init at 5kBAUD ok");
        digitalWrite(8, HIGH);
        digitalWrite(7, HIGH);
       }
      else
        Serial.println("Can't init CAN");
        
        delay(1000);

       }       
       delay(250);

  id = 0x00;
  // send data:  id = 0x00, standrad flame, data len = 8, stmp: data buf
  CAN.sendMsgBuf(id, 0, 8, stmp);  
  delay(100);
}

