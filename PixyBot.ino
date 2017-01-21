#include <SPI.h>  
#include <Pixy.h>

// This is the main Pixy object 
Pixy pixy;

void setup(){
  Serial.begin(9600);
  Serial.print("Starting...\n");

  pixy.init();
}

void loop() {
  static int i = 0;
  int j;
  uint16_t blocks;
  
  // grab blocks!
  blocks = pixy.getBlocks();
  
  // If there are detect blocks, print them!
  if (blocks){
    i++;
    
    // do this (print) every 50 frames because printing every
    // frame would bog down the Arduino
    if (i%50==0){
      Serial.println(blocks);
      if (blocks == 2){
        //Serial.println(pixy.blocks[0].x);
        //Serial.println(pixy.blocks[1].x);
        //Serial.println(averageX());
        //Serial.print(",");
        //Serial.println(averageY());
        //Serial.print(pixy.blocks[0].x+(pixy.blocks[0].width/2));
        //Serial.print(",");
        //Serial.println(pixy.blocks[1].x-(pixy.blocks[1].width/2));
        Serial.println(wholeWidth());
        Serial.print(distance());
        Serial.println(" ft");
      }
    }
  }  
}

int average(int a, int b){
  return (a+b)/2;
}
int averageX(){
  return 160-average(pixy.blocks[0].x, pixy.blocks[1].x);
}
int averageY(){
  return 100-average(pixy.blocks[0].y, pixy.blocks[1].y);
}
int wholeWidth(){
  if (pixy.blocks[0].x > pixy.blocks[1].x){
    return (pixy.blocks[0].x-(pixy.blocks[0].width/2))-(pixy.blocks[1].x+(pixy.blocks[1].width/2));
  } else {
    return (pixy.blocks[1].x-(pixy.blocks[1].width/2))-(pixy.blocks[0].x+(pixy.blocks[0].width/2));
  }
}
double distance(){
  return 1/(((8.006*pow(10,-3))*wholeWidth())+(8.664*pow(10,-4)));
}

