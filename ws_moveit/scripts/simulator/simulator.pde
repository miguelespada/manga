import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress myRemoteLocation;

float value, angle;
int led;

import processing.serial.*;

Serial myPort;  


void setup() {
  size(400,400);
  frameRate(25);
  oscP5 = new OscP5(this,12000);
  myRemoteLocation = new NetAddress("127.0.0.1",12000);
 
 println(Serial.list());
  
  // Select correct arduino port
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 57600);
  delay(1000);
}

void draw() {
  background(255);
  
  stroke(0);
  fill(0);
  
  text(value, 20, 20);
  text(angle, 20, 40);
  text(led, 20, 60);
  
  translate(width/2, height/2);
  rotate(angle);
  line(-50, 0, 50, 0);
  ellipse(-50, 0, 5, 5);
  
}

void oscEvent(OscMessage theOscMessage) {
  
  if(theOscMessage.checkAddrPattern("/roll")==true) {
     value = theOscMessage.get(0).floatValue(); 
     if(value < 0) value = 360 + value;
     angle = radians(value) + PI/2;
     
    led = int(map(sin(angle), -1, 1, 0, 55));
    myPort.write(str(led) + "\n");
  } 
  println("### received an osc message. with address pattern "+theOscMessage.addrPattern());
}