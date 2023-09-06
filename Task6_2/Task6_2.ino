#define PIN_ENCODER_A 2
#define PIN_ENCODER_B 3

long long counter = 0;



void setup() 
{
  pinMode(PIN_ENCODER_A, INPUT_PULLUP);
  pinMode(PIN_ENCODER_B, INPUT_PULLUP);
  
  attachInterrupt(PIN_ENCODER_A, ISR_encoderPinA, CHANGE);
  attachInterrupt(PIN_ENCODER_B, ISR_encoderPinB, CHANGE);
}

float xn1 = 0;
float yn1 = 0;
int k = 0;

void loop() 
{
  // Test signal
  float t = micros()/1.0e6;
  float xn = sin(2*PI*2*t) + 0.2*sin(2*PI*50*t);

  // Compute the filtered signal
  float yn = 0.969*yn1 + 0.0155*xn + 0.0155*xn1;

  delay(1);
  xn1 = xn;
  yn1 = yn;

  if(k % 3 == 0)
  {
    Serial.print(2*xn);
    Serial.print(" ");
    Serial.println(2*yn);
  }
  k = k+1;
}

void ISR_encoderPinA()
{
  if(digitalRead(PIN_ENCODER_A) != digitalRead(PIN_ENCODER_B))  counter ++;
  else  counter --;
}

void ISR_encoderPinB()
{
  if(digitalRead(PIN_ENCODER_A) == digitalRead(PIN_ENCODER_B))  counter ++;
  else  counter --;
}
