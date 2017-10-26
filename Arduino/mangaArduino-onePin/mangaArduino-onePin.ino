#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PINPIXEL            2
#define NUMPIXELS      48

int c = 0; 
int prevC = -1;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PINPIXEL, NEO_GRB + NEO_KHZ800);


int pin;
bool values[16];
int C;
int STATE;

bool DEBUG = true;

int myDelay = 100;

void setup(){
  
    Serial.begin(9600);
    
    for (int i = 2 ; i < 13 ; i++)
          pinMode(i , OUTPUT);

    pinMode(7, INPUT);
    
    if(DEBUG) myDelay = 500;
    
   
    pixels.begin(); // This initializes the NeoPixel library.
    pixels.setBrightness(100);
    
}

void loop(){   
  
  // Habilita multiplexores

  
  if(DEBUG){
    Serial.println("----------------");
    delay(myDelay);
  }
 
 
 
  while (Serial.available()){
     c = Serial.read();    
  }
  
  if(c != prevC){
    

    for(int i=0;i<c;i++) {
      pixels.setPixelColor(i, pixels.Color(0,0,255)); // Moderately bright green color.
    }
    
    for(int i=c;i<NUMPIXELS;i++) {
      pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
    }
    pixels.show(); // This sends the updated pixel color to the hardware. 
    prevC = c;
  }
 
 
    printMux(0);

}


void printMux(unsigned char mux){
    readMux(mux);
    
    if(DEBUG){
      int nPins = 12;
      
      if(mux == 4 || mux == 1)
        nPins = 14;
      
      Serial.print(mux);
      Serial.print("->");
      for(pin=0;pin < nPins;pin++)
        Serial.print(values[pin]);
      Serial.println();
    }
    else{
      Serial.write(-1);
      Serial.write(mux);
      Serial.write(lsb(values));
      Serial.write(hsb(values));
    }
      
      
}

void readPins(int mux){

  
  for(pin=0;pin<16;pin++){ 
    
       values[pin] = 0;
       unsigned S0,S1,S2,S3;

       int pinToRead = 0;
       S0 = pinToRead & B00000001; 
       S1 = pinToRead & B00000010;
       S2 = pinToRead & B00000100; 
       S3 = pinToRead & B00001000; 
    
       digitalWrite (8, S0); 
       digitalWrite ( 9, S1) ;
       digitalWrite (10, S2) ;
       digitalWrite (11 ,S3) ;
       
       STATE = digitalRead(7);
       
       values[pin] = STATE;
       
       if(mux == 5){
         if(pin == 12) values[3] = STATE;
         if(pin == 13) values[1] = STATE;
       }
       
       if(mux == 4){
         if(pin == 14) values[1] = STATE;
       }
       if(mux == 3){
         if(pin == 12) values[7] = STATE;
         if(pin == 13) values[8] = STATE;
       }
       
       
    }  
}


void readMux(int C){ 
    int channel = C;
   
    if(C == 2) channel = 7;
    if(C == 1) channel = 2;
    unsigned int SC0, SC1, SC2;
    SC0 = channel & B00000001;  
    digitalWrite (3 , SC0);
    SC1 = channel & B00000010 ; 
    digitalWrite (4 , SC1);
    SC2 = channel & B00000100;
    digitalWrite (5 , SC2) ;
    digitalWrite (6 , 0) ;

    readPins(C);
}



int lsb(bool v[]){
  unsigned char  b = 0; 
  for(int i = 7; i >= 0; i --){
    b = (b << 1);
    if(values[i]) 
      b = b + 1;
  }
  return b;
}

int hsb(bool v[]){
  unsigned char  b = 0; 
  for(int i = 15; i >= 8; i --){
    b = (b << 1);
    if(values[i]) 
      b = b + 1;
  }
  return b;
}

