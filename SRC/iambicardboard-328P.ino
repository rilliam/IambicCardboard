#define DIT 3
#define DAH 6
#define LED 1
#define SPEAKER 2  
#define DITLEN A1
// THRESH is the count before the input pin goes high. I only needed 1.
#define THRESH 1
// #define note 75
#define TONE 2600

int note;

boolean readbutton(int button){
  volatile uint8_t* ddr;
  volatile uint8_t* port;
  volatile uint8_t* pin;
  byte bitmask;
  unsigned int count=0;
  port=portOutputRegister(digitalPinToPort(button));
  ddr=portModeRegister(digitalPinToPort(button));
  bitmask=digitalPinToBitMask(button);
  pin=portInputRegister(digitalPinToPort(button));
  *port &= ~(bitmask);
  *ddr |= bitmask;
  delay(1);
  *ddr &= ~(bitmask);
  *port |= bitmask;  // comment this out if you install 100k pullups
                     // on the inputs.

  while ( ! (*pin & bitmask)) {
    count++;
  }
  *port &= ~(bitmask);
  *ddr  |= bitmask;

  return(count>THRESH?1:0);
}

void setup (){
  pinMode(DIT, INPUT);
  pinMode(DAH, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(SPEAKER, OUTPUT);
}

void loop(){
//  bitWrite(PORTB, LED,HIGH);
//  delay(500);
  boolean dit,dah;

 // note=analogRead(A1);
 note=100;
  dit=readbutton(DIT);
  dah=readbutton(DAH);
  // dit and dah pressed together produce a dahdit
  if (dit && dah){
 
    digitalWrite(LED, HIGH);
    tone(SPEAKER,TONE, note*3);
    delay(note*3);
    digitalWrite(LED, LOW);
    delay(note);
    digitalWrite(LED, HIGH);
    tone(SPEAKER,TONE, note);
    delay(note);
    digitalWrite(LED, LOW);
    delay(note);

   } else if (dit) {
    digitalWrite(LED, HIGH);
    tone(SPEAKER,TONE,note);
    delay(note);
    digitalWrite(LED, LOW);
    delay(note);
  } else if (dah){
    digitalWrite(LED, HIGH);
    tone(SPEAKER,TONE, note*3);
    delay(note*3);
    digitalWrite(LED, LOW);
    delay(note);
  }
}
