
//VARIABLES AND DEFINES HERE
#define WS2812_pin 8 
#define numberOfLEDs 256// total number of RGB LEDs
byte RGB[768];//take your number of LEDs and multiply by 3

#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin

int a;
int npc[10];
int c = 7;
int x;
int j;
int xValue = 0; // To store value of the X axis

// FUNCTIONS HERE
void RGB_update(int LED, byte RED, byte GREEN, byte BLUE);//function to drive LEDs

void mapLEDXY(int y, int x, byte RED, byte  GREEN, byte BLUE) {
  int RGBlocation = 0;

  if (y % 2 == 0) { //even column
    RGBlocation = x + y * 16;

  } else { //odd column
    RGBlocation = 15 - x + y * 16;
  }

  RGB[RGBlocation * 3] = BLUE;
  RGB[RGBlocation * 3 + 1] = RED;
  RGB[RGBlocation * 3 + 2] = GREEN;
}

void clearLEDs() {
  memset(RGB, 0, sizeof(RGB));
}

void setup() {
  Serial.begin(9600);
  pinMode(WS2812_pin, OUTPUT);

  clearLEDs();
  RGB_update(-1, 0, 0, 0);

  randomSeed(analogRead(0));
  
  border();
  mapLEDXY(c,0,20,0,0);mapLEDXY(c,1,20,0,0);

}//setup

void loop() {
  
  
  randomBlink();
  //losing();
  
}

void border(){
  int edgeL = 2;
  int edgeR = 12;

  for(int i =0;i<=15;i++){
    mapLEDXY(edgeL,i,0,0,20);
    mapLEDXY(edgeR,i,0,0,20);

  }}

void player(){
  xValue = analogRead(VRX_PIN);
  int delayTime = 150; // Time (in ms) between each step

  Serial.println("x = ");
  Serial.println(xValue);
  Serial.println(c);
 
  if (c >= 3 && c <= 10) {
    if(xValue <= 300){

      mapLEDXY(c-1,0,20,0,0);mapLEDXY(c-1,1,20,0,0);  
      mapLEDXY(c+1,0,0,0,0);mapLEDXY(c+1,1,0,0,0);
      c-=1;

    delay(delayTime);
    }

    if(xValue >= 900){

      mapLEDXY(c+1,0,20,0,0);mapLEDXY(c+1,1,20,0,0);
      mapLEDXY(c-1,0,0,0,0);mapLEDXY(c-1,1,0,0,0);
      c+=1;
      
      delay(delayTime);
    }
        
  }

}

void randomBlink() {
  int delayTime = 150; // Time (in ms) between each step

  for(int i=0;i<=9;i++){
    a = random(3, 12);
    npc[i]= a;
  } 

  for(int j=15;j>=0;j--){
    for (int i = 0; i < 10; i++) {
      x=npc[i];
      mapLEDXY(x, j, 20, 0, 0);
    }
   
    RGB_update(-1, 0, 0, 0);
    player();
    delay(delayTime);
    
    for (int i = 0; i < 10; i++) {
      x=npc[i];
      mapLEDXY(x, j, 0, 0, 0);
    }

    delay(delayTime);
  }
  
}

void losing(){

  if(x == c && j == 14){
    mapLEDXY(0,0,20,0,0);mapLEDXY(0,2,20,0,0);mapLEDXY(0,3,20,0,0);mapLEDXY(1,1,20,0,0);mapLEDXY(1,2,20,0,0);mapLEDXY(1,3,20,0,0);mapLEDXY(1,4,20,0,0);mapLEDXY(1,14,20,0,0);mapLEDXY(2,1,20,0,0);mapLEDXY(2,11,20,0,0);mapLEDXY(2,12,20,0,0);mapLEDXY(2,13,20,0,0);mapLEDXY(3,1,20,0,0);mapLEDXY(3,14,20,0,0);mapLEDXY(5,2,20,0,0);mapLEDXY(5,3,20,0,0);mapLEDXY(6,1,20,0,0);mapLEDXY(6,4,20,0,0);mapLEDXY(6,12,20,0,0);mapLEDXY(6,13,20,0,0);mapLEDXY(7,2,20,0,0);mapLEDXY(7,3,20,0,0);mapLEDXY(7,11,20,0,0);mapLEDXY(7,14,20,0,0);mapLEDXY(8,12,20,0,0);mapLEDXY(8,13,20,0,0);mapLEDXY(9,1,20,0,0);mapLEDXY(9,4,20,0,0);mapLEDXY(10,1,20,0,0);mapLEDXY(10,3,20,0,0);mapLEDXY(10,5,20,0,0);mapLEDXY(11,2,20,0,0);mapLEDXY(11,5,20,0,0);mapLEDXY(11,12,20,0,0);mapLEDXY(11,13,20,0,0);mapLEDXY(11,14,20,0,0);mapLEDXY(12,11,20,0,0);mapLEDXY(13,4,20,0,0);mapLEDXY(13,11,20,0,0);mapLEDXY(14,1,20,0,0);mapLEDXY(14,2,20,0,0);mapLEDXY(14,3,20,0,0);mapLEDXY(14,4,20,0,0);mapLEDXY(14,12,20,0,0);mapLEDXY(14,13,20,0,0);mapLEDXY(14,14,20,0,0);mapLEDXY(15,4,20,0,0);
    RGB_update(-1, 0, 0, 0);
}
}


//WS2812 Driver Function
void RGB_update(int LED, byte RED, byte GREEN, byte BLUE) {
  // LED is the LED number starting with 0
  // RED, GREEN, BLUE is the brightness 0..255 setpoint for that LED
  byte ExistingPort, WS2812pinHIGH;//local variables here to speed up pinWrites

  if (LED >= 0) { //map the REG GREEN BLUE Values into the RGB[] array
    RGB[LED * 3] = GREEN;
    RGB[LED * 3 + 1] = RED;
    RGB[LED * 3 + 2] = BLUE;
  }

  noInterrupts();//kill the interrupts while we send the bit stream out...
  ExistingPort = PORTB; // save the status of the entire PORT B - let's us write to the entire port without messing up the other pins on that port
  WS2812pinHIGH = PORTB | 1; //this gives us a byte we can use to set the whole PORTB with the WS2812 pin HIGH
  int bitStream = numberOfLEDs * 3;//total bytes in the LED string

  //This for loop runs through all of the bits (8 at a time) to set the WS2812 pin ON/OFF times
  for (int i = bitStream - 1; i >= 0; i--) {

    PORTB = WS2812pinHIGH;//bit 7  first, set the pin HIGH - it always goes high regardless of a 0/1

    //here's the tricky part, check if the bit in the byte is high/low then right that status to the pin
    // (RGB[i] & B10000000) will strip away the other bits in RGB[i], so here we'll be left with B10000000 or B00000000
    // then it's easy to check if the bit is high or low by AND'ing that with the bit mask ""&& B10000000)"" this gives 1 or 0
    // if it's a 1, we'll OR that with the Existing port, thus keeping the pin HIGH, if 0 the pin is written LOW
    PORTB = ((RGB[i] & B10000000) && B10000000) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");//these are NOPS - these let us delay clock cycles for more precise timing
    PORTB = ExistingPort;//okay, here we know we have to be LOW regardless of the 0/1 bit state
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");//minimum LOW time for pin regardless of 0/1 bit state

    // then do it again for the next bit and so on

    PORTB = WS2812pinHIGH;//bit 6
    PORTB = ((RGB[i] & B01000000) && B01000000) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB = ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");

    PORTB = WS2812pinHIGH;//bit 5
    PORTB = ((RGB[i] & B00100000) && B00100000) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB = ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");

    PORTB = WS2812pinHIGH;//bit 4
    PORTB = ((RGB[i] & B00010000) && B00010000) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB = ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");

    PORTB = WS2812pinHIGH;//bit 3
    PORTB = ((RGB[i] & B00001000) && B00001000) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB = ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");

    PORTB = WS2812pinHIGH;//bit 2
    PORTB = ((RGB[i] & B00000100) && B00000100) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB = ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");

    PORTB = WS2812pinHIGH;//bit 1
    PORTB = ((RGB[i] & B00000010) && B00000010) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB = ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");

    PORTB = WS2812pinHIGH;//bit 0
    __asm__("nop\n\t");//on this last bit, the check is much faster, so had to add a NOP here
    PORTB = ((RGB[i] & B00000001) && B00000001) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB = ExistingPort;//note there are no NOPs after writing the pin LOW, this is because the FOR Loop uses clock cycles that we can use instead of the NOPS
  }

  interrupts();//enable the interrupts

}