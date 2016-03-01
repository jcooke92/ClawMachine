// Code by Jonathan Cooke.


// Before anything more is said, let's define some axes:

// (From the player's perpective)

// The X axis moves the claw assembly LEFT/RIGHT
// The Y axis moves the claw assembly FORWARD/BACKWARD
// The Z axis moves the claw assemble UP/DOWN

// I/O pins that the motors, relays, push buttons, etc are connected to

// X axis

const int lrmtr[] = {4,5};

// Y axis

const int fbmtr[] = {2,3};

// Z axis

const int udmtr[] = {6,7};

// Electromagnetic coil

const int coil[] = {8,9};

// Limit switches for X, Y and Z axes


const int lr = 31;
const int fb = 30;
const int ud = 32;

// Forward push button

const int forb = 33;

// Right push button

const int rightb = 34;

// Coin acceptor

const int coin = 35;

// Old cabinet light switch that now controls the difficulty
// If this switch's contacts are CLOSED then the claw will close with full power every time 

const int dif = 36;

// Pushbutton LEDs

const int forbLED = 12;
const int rightbLED = 13;


// Generate a random number 

const int n = random(0,4);
static int wonInRow = 0;


// NB: ALL NOTES DEFINED WITH STANDARD ENGLISH NAMES, EXCEPT FROM "A" 
//THAT IS CALLED WITH THE ITALIAN NAME "LA" BECAUSE A0,A1...ARE THE ANALOG PINS ON ARDUINO.
// (Ab IS CALLED Ab AND NOT LAb)
#define	C0      16.35
#define	Db0	17.32
#define	D0	18.35
#define	Eb0	19.45
#define	E0	20.60
#define	F0	21.83
#define	Gb0	23.12
#define	G0	24.50
#define	Ab0	25.96
#define	LA0	27.50
#define	Bb0	29.14
#define	B0	30.87
#define	C1	32.70
#define	Db1	34.65
#define	D1	36.71
#define	Eb1	38.89
#define	E1	41.20
#define	F1	43.65
#define	Gb1	46.25
#define	G1	49.00
#define	Ab1	51.91
#define	LA1	55.00
#define	Bb1	58.27
#define	B1	61.74
#define	C2	65.41
#define	Db2	69.30
#define	D2	73.42
#define	Eb2	77.78
#define	E2	82.41
#define	F2	87.31
#define	Gb2	92.50
#define	G2	98.00
#define	Ab2	103.83
#define	LA2	110.00
#define	Bb2	116.54
#define	B2	123.47
#define	C3	130.81
#define	Db3	138.59
#define	D3	146.83
#define	Eb3	155.56
#define	E3	164.81
#define	F3	174.61
#define	Gb3	185.00
#define	G3	196.00
#define	Ab3	207.65
#define	LA3	220.00
#define	Bb3	233.08
#define	B3	246.94
#define	C4	261.63
#define	Db4	277.18
#define	D4	293.66
#define	Eb4	311.13
#define	E4	329.63
#define	F4	349.23
#define	Gb4	369.99
#define	G4	392.00
#define	Ab4	415.30
#define	LA4	440.00
#define	Bb4	466.16
#define	B4	493.88
#define	C5	523.25
#define	Db5	554.37
#define	D5	587.33
#define	Eb5	622.25
#define	E5	659.26
#define	F5	698.46
#define	Gb5	739.99
#define	G5	783.99
#define	Ab5	830.61
#define	LA5	880.00
#define	Bb5	932.33
#define	B5	987.77
#define	C6	1046.50
#define	Db6	1108.73
#define	D6	1174.66
#define	Eb6	1244.51
#define	E6	1318.51
#define	F6	1396.91
#define	Gb6	1479.98
#define	G6	1567.98
#define	Ab6	1661.22
#define	LA6	1760.00
#define	Bb6	1864.66
#define	B6	1975.53
#define	C7	2093.00
#define	Db7	2217.46
#define	D7	2349.32
#define	Eb7	2489.02
#define	E7	2637.02
#define	F7	2793.83
#define	Gb7	2959.96
#define	G7	3135.96
#define	Ab7	3322.44
#define	LA7	3520.01
#define	Bb7	3729.31
#define	B7	3951.07
#define	C8	4186.01
#define	Db8	4434.92
#define	D8	4698.64
#define	Eb8	4978.03
// DURATION OF THE NOTES 
#define BPM 142      //you can change this value changing all the others
#define H 2*Q //half 2/4
#define Q 60000/BPM //quarter 1/4 
#define E Q/2   //eighth 1/8
#define S Q/4 // sixteenth 1/16
#define W 4*Q // whole 4/4

const int buzzer = 10;

// Setup function that is called once when turning on the microcontroller
 
void setup() 
{ 
  
  // Define some I/O on the board
  
  // F/B motor relays
  pinMode(fbmtr[0], OUTPUT);
  pinMode(fbmtr[1], OUTPUT);
  
  // L/R motor relays
  pinMode(lrmtr[0], OUTPUT);
  pinMode(lrmtr[1], OUTPUT);
  
  // U/D motor relays
  pinMode(udmtr[0], OUTPUT);
  pinMode(udmtr[1], OUTPUT);
  
  // coil relays
  pinMode(coil[0], OUTPUT);
  pinMode(coil[1], OUTPUT);
  //pinMode(10, OUTPUT);
  
  
  // These limit switches will read LOW when an axis is not homed
  
 
  // F/B limit switch
  pinMode(fb, INPUT);
  digitalWrite(fb,HIGH);
  
  // L/R limit switch
  pinMode(lr, INPUT);
  digitalWrite(lr,HIGH);
  
  // up limit switch
  pinMode(ud, INPUT);
  digitalWrite(ud,HIGH);
  
  // Thsee buttons and switches will read LOW when they are pushed
  
  // forward button
  pinMode(forb, INPUT);
  digitalWrite(forb,HIGH);
  
  // right button
  pinMode(rightb, INPUT);
  digitalWrite(rightb,HIGH);
  
  // forward button LED
  
  pinMode(forbLED, OUTPUT);
  digitalWrite(forbLED, LOW);
  
  // right button LED
  
  pinMode(rightbLED, OUTPUT);
  digitalWrite(rightbLED, LOW);
   
  // coin acceptor
  pinMode(coin, INPUT);
  digitalWrite(coin,HIGH);
  
  // difficulty switch 
  pinMode(dif, INPUT);
  digitalWrite(dif, HIGH);
  
  pinMode(buzzer, OUTPUT);
  
  // Cut power to the coil
  
  openClaw();
  
  // Home the claw
  
  gotoHome();
  
  // Propagation delay
  
  delay(500);
}

void loop() 
{ 
  // Wait until a coin is inserted (electricity isn't free)
  
  // This is commented out for now because the coin acceptor is not connected
  
 //waitForCoin(); 
 
 // Wait for the user to push the buttons and move the claw
 
 waitAndDoButtonInput();
 
 // Lower the claw, put power to the coil and start moving to the prize drop
 
 grabSequence();
}


// This function cuts power from the electromagnetic coil on the claw 

void openClaw()
{
  if(digitalRead(coil[1]) != HIGH)
  {
    digitalWrite(coil[1],HIGH);
  }
  if(digitalRead(coil[0]) != LOW)
  {
    digitalWrite(coil[0], LOW);
  }
}


// This function applies power to the claw coil and how much power to supply
// Currently there are 2 power settings: one is through a physically adjustable potentiometer and the other is full power
// This function generates a random number to decide if full power should be supplied or not and makes sure full power is never supplied more than 2 times in a row
// There is also a boolean value that the function takes; if this boolean value is true, the coil will be supplied with full power no matter what
// If the boolean is false, it lets the random number generator decide

void closeClaw(bool win)
{
  if(!win && wonInRow < 2)
  {
    int i = random(0,4);
    if(i == n)
    {
      if(digitalRead(coil[1]) != LOW)
      {
        digitalWrite(coil[1], LOW);
      }
      ++wonInRow;
    }
    else
    {
      if(digitalRead(coil[1]) != HIGH)
      {
        digitalWrite(coil[1], HIGH);
      }
      wonInRow = 0;
    }
  }
  else if(wonInRow >= 2)
  {
    if(digitalRead(coil[1]) != HIGH)
      {
        digitalWrite(coil[1], HIGH);
      }
      wonInRow = 0;
  }
  else
  {
    if(digitalRead(coil[1]) != LOW)
      {
        digitalWrite(coil[1], LOW);
      }
  }
  if(digitalRead(coil[0]) != HIGH)
  {
    digitalWrite(coil[0], HIGH);
  }
}

void moveForward(int ms)
{
  if(digitalRead(fbmtr[0]) != HIGH)
  { digitalWrite(fbmtr[0], HIGH); }
  
  if(digitalRead(fbmtr[1]) != LOW)
  { digitalWrite(fbmtr[1], LOW); }
  
  if(ms > 0)
  {
    delay(ms);
    stopMotors();
  }
}

void moveBack(int ms)
{
  if(digitalRead(fbmtr[0]) != LOW)
  { digitalWrite(fbmtr[0], LOW); }
  
  if(digitalRead(fbmtr[1]) != HIGH)
  { digitalWrite(fbmtr[1], HIGH); }
  
   if(ms > 0)
  {
    delay(ms);
    stopMotors();
  }
}

void moveRight(int ms)
{
  if(digitalRead(lrmtr[0]) != HIGH)
  { digitalWrite(lrmtr[0], HIGH); }
  
  if(digitalRead(lrmtr[1]) != LOW)
  { digitalWrite(lrmtr[1], LOW); }
  
  if(ms > 0)
  {
    delay(ms);
    stopMotors();
  }
}

void moveLeft(int ms)
{
  if(digitalRead(lrmtr[0]) != LOW)
  { digitalWrite(lrmtr[0], LOW); }
  
  if(digitalRead(lrmtr[1]) != HIGH)
  { digitalWrite(lrmtr[1], HIGH); }
  
   if(ms > 0)
  {
    delay(ms);
    stopMotors();
  }
}

void moveUp(int ms)
{
  if(digitalRead(udmtr[0]) != HIGH)
  { digitalWrite(udmtr[0], HIGH); }
  
  if(digitalRead(udmtr[1]) != LOW)
  { digitalWrite(udmtr[1], LOW); }
  
  if(ms > 0)
  {
    delay(ms);
    stopMotors();
  }
}

void moveDown(int ms)
{
  if(digitalRead(udmtr[0]) != LOW)
  { digitalWrite(udmtr[0], LOW); }
  
  if(digitalRead(udmtr[1]) != HIGH)
  { digitalWrite(udmtr[1], HIGH); }
  
   if(ms > 0)
  {
    delay(ms);
    stopMotors();
  }
}


void stopFBMotor()
{
  if(digitalRead(fbmtr[0]) != LOW)
  { digitalWrite(fbmtr[0],LOW); }
  if(digitalRead(fbmtr[1]) != LOW)
  { digitalWrite(fbmtr[1],LOW); }
  
  delay(10);
}

void stopLRMotor()
{
  if(digitalRead(lrmtr[0]) != LOW)
  { digitalWrite(lrmtr[0],LOW); }
  if(digitalRead(lrmtr[1]) != LOW)
  { digitalWrite(lrmtr[1],LOW); }
  
  delay(10);
}

void stopUDMotor()
{
  if(digitalRead(udmtr[0]) != LOW)
  { digitalWrite(udmtr[0],LOW); }
  if(digitalRead(udmtr[1]) != LOW)
  { digitalWrite(udmtr[1],LOW); }
  
  delay(10);
}

void stopMotors()
{
  if(digitalRead(fbmtr[0]) != LOW)
  { digitalWrite(fbmtr[0],LOW); }
  if(digitalRead(fbmtr[1]) != LOW)
  { digitalWrite(fbmtr[1],LOW); }
  
  delay(100);
  
  if(digitalRead(lrmtr[0]) != LOW)
  { digitalWrite(lrmtr[0],LOW); }
  if(digitalRead(lrmtr[1]) != LOW)
  { digitalWrite(lrmtr[1],LOW); }
  
  delay(100);
  
  if(digitalRead(udmtr[0]) != LOW)
  { digitalWrite(udmtr[0],LOW); }
  if(digitalRead(udmtr[1]) != LOW)
  { digitalWrite(udmtr[1],LOW); }
  
  delay(100);
}

void gotoHome()
{
   // check positioning; home if necessary
   
   // u/d
   
  if(digitalRead(ud) == LOW)
  {
     moveUp(-1);
     for(int i = 0; i < 4; ++i)
     {
       while(digitalRead(ud) == LOW)
       {}
       delay(5);
     }
     stopUDMotor();
  }
  
  delay(100);
  
  bool xHomed = true;
  bool yHomed = true;
  
  for(int i = 0; i < 2; ++i)
  {
    if(digitalRead(lr) != LOW)
    {
      xHomed = false;
    }
  }
  for(int i = 0; i < 2; ++i)
  {
    if(digitalRead(fb) != LOW)
    {
      yHomed = false;
    }
  }
  
  homeXY(xHomed, yHomed);
}

void waitForCoin()
{
  // wait for coin to be inserted 
  while(digitalRead(coin) == HIGH)
  {
  }
}

boolean cycleCheck(unsigned long *lastMillis, unsigned int cycle) 
{
 unsigned long currentMillis = millis();
 if(currentMillis - *lastMillis >= cycle)
 {
   *lastMillis = currentMillis;
   return true;
 }
 else
   return false;
}

void waitAndDoButtonInput()
{
  unsigned long lastMillis = millis();
  unsigned long* lm = &lastMillis;
  unsigned int cycle = 750;
  digitalWrite(forbLED, HIGH);
  while(digitalRead(forb) == HIGH)
 { 
    if(cycleCheck(lm, cycle))
    { digitalWrite(forbLED, !digitalRead(forbLED)); }
 }
 digitalWrite(forbLED, HIGH);
 moveBack(-1);
 delay(200);
 for(int i = 0; i < 2; ++i)
 {
   while(digitalRead(forb) == LOW)
   {}
 }
 digitalWrite(forbLED, LOW);
 stopFBMotor();
 digitalWrite(rightbLED, HIGH);
 while(digitalRead(rightb) == HIGH)
 {
   if(cycleCheck(lm, cycle))
   { digitalWrite(rightbLED, !digitalRead(rightbLED)); }
 }
 digitalWrite(rightbLED, HIGH);
 moveRight(-1);
 delay(200);
 for(int i = 0; i < 2; ++i)
 {
   while(digitalRead(rightb) == LOW)
   {}
 }
 digitalWrite(rightbLED, LOW);
 stopLRMotor();
 delay(50);
 moveDown(1700);
 delay(200); 
}

void grabSequence()
{
 if(digitalRead(dif) == LOW)
 { 
   closeClaw(true);
 }
 else
 {
   closeClaw(false);
 }
 delay(300);
 gotoHome();
 openClaw();
 delay(500);
}

void playSong(int p)
{
  note(p, D6, E);
  note(p, E6, E);
  note(p, F6, E);
  note(p, B6, E);
  note(p, D6, E);
  note(p, E6, E);
  note(p, F6, E);
  note(p, LA6, E);
  note(p, B6, E);
  note(p, C7, E);
  note(p, D7, E);
  note(p, C7, Q);
}

void note(int p, float n, float l)
{
  tone(p, n, l);
  delay(1+l);
}

void homeXY(bool x, bool y)
{
  if(x && y)
  {
    moveLeft(-1);
    moveForward(-1);
    for(int i = 0; i < 2; ++i)
    {
       while(digitalRead(lr) == LOW && digitalRead(fb) == LOW)
       {}
       delay(50);
    }
    if(digitalRead(lr) != LOW && digitalRead(fb) != LOW)
    {
      stopLRMotor();
      stopFBMotor();
      return;
    }
    if(digitalRead(lr) != LOW)
    {
      stopLRMotor();
      homeXY(false, true);
      return;
    }
    if(digitalRead(fb) != LOW)
    {
      stopFBMotor();
      homeXY(true, false);
      return;
    }
  }
  else if(x)
  {
    if(digitalRead(lr) == LOW)
    {
       moveLeft(-1);
       for(int i = 0; i < 2; ++i)
       {
         while(digitalRead(lr) == LOW)
         {}
         delay(50);
       }
       stopLRMotor();
    }
    delay(100);
    return;
  }
  else if(y)
  {
    if(digitalRead(fb) == LOW)
    {
       moveForward(-1);
       for(int i = 0; i < 2; ++i)
       {
         while(digitalRead(fb) == LOW)
         {}
         delay(50);
       }
       stopFBMotor();
       }
       delay(100);
       return;
    }
}


