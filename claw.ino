// Code by Jonathan Cooke.

const int fbmtr[] = {2,3};
const int lrmtr[] = {4,5};
const int udmtr[] = {6,7};
const int coil[] = {8,9};
const int fb = 30;
const int lr = 31;
const int ud = 32;
const int forb = 33;
const int rightb = 34;
const int coin = 35;
const int dif = 36;
const int n = random(0,4);
static int wonInRow = 0;
 
void setup() 
{ 
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
  
  
  /* 
  limit switches will read low
  when they are not in home position
  */
  
 
  // F/B limit switch
  pinMode(fb, INPUT);
  digitalWrite(fb,HIGH);
  
  // L/R limit switch
  pinMode(lr, INPUT);
  digitalWrite(lr,HIGH);
  
  // up limit switch
  pinMode(ud, INPUT);
  digitalWrite(ud,HIGH);
  
  /*
  buttons/acceptor will read low when
  they are pushed/activated
  */
  
  // forward button
  pinMode(forb, INPUT);
  digitalWrite(forb,HIGH);
  
  // right button
  pinMode(rightb, INPUT);
  digitalWrite(rightb,HIGH);
   
  // coin acceptor
  pinMode(coin, INPUT);
  digitalWrite(coin,HIGH);
  
  // difficulty switch 
  pinMode(dif, INPUT);
  digitalWrite(dif, HIGH);
  
  openClaw();
  gotoHome();
  delay(500);
}

void loop() 
{ 
 //waitForCoin(); 
 waitAndDoButtonInput();
 grabSequence();
}

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
  
  // l/r
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
  
  // f/b
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
}

void waitForCoin()
{
  // wait for coin to be inserted 
  while(digitalRead(coin) == HIGH)
  {
  }
}

void waitAndDoButtonInput()
{
  while(digitalRead(forb) == HIGH)
 {}
 moveBack(-1);
 delay(200);
 for(int i = 0; i < 2; ++i)
 {
   while(digitalRead(forb) == LOW)
   {}
 }
 stopFBMotor();
 while(digitalRead(rightb) == HIGH)
 {}
 moveRight(-1);
 delay(200);
 for(int i = 0; i < 2; ++i)
 {
   while(digitalRead(rightb) == LOW)
   {}
 }
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


