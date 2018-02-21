// demo: CAN-BUS Shield, receive data
#include "mcp_can.h"
#include <SPI.h>
#include <stdio.h>
#define INT8U unsigned char



/* Define Joystick connection pins */
#define UP     A1
#define DOWN   A3
#define LEFT   A2
#define RIGHT  A5
#define CLICK  A4

INT8U Flag_Recv = 0;
INT8U len = 0;
INT8U buf[8];
INT32U ID = 0;
char str[20];
void setup()
{
  //LEDs
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
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
  
  CAN.begin(CAN_500KBPS);                   // init can bus : baudrate = 500k
  attachInterrupt(0, MCP2515_ISR, FALLING); // start interrupt
  Serial.begin(115200);
  Serial.println("CAN Init OK");
  Serial.println("Joystick Init ok");
}

void MCP2515_ISR()
{
     Flag_Recv = 1;
}

void loop()
{
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
       if(Canbus.init(CAN_125KBPS) == CAN_OK)  //Initialise MCP2515 CAN controller at the specified speed
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
       if(Canbus.init(CAN_5KBPS) == CAN_OK)  //Initialise MCP2515 CAN controller at the specified speed
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
       
    if(Flag_Recv)                   // check if get data
    {
      Flag_Recv = 0;                // clear flag
      CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf
      ID = CAN.getCanId(); //INT32U??
      
      Serial.println("CAN BUS RX:"); 
      Serial.print("Message ID: "); 
      Serial.println(ID);
      Serial.print("data len = ");Serial.println(len);
      for(int i = 0; i<len; i++)    // print the data
      {
        Serial.print(buf[i], HEX);Serial.print("\t");
      }
      Serial.println();
    }
}
