
#define NUM_NOTES 8
int sensorPin = 0;    // The potentiometer is connected to analog pin 0
int sensorValue = 0;
int buttonValue = 0;
int ledPin = 10;      // The LED is connected to digital pin 10
int count = 1;

int piezoPin = 9;  //pin number for the buzzer

int inPin = 7; // pin for the button
int val = 0;
// notes are C, D, E, F, G, A, B 
int notes[NUM_NOTES] = {2093, 2394, 2637, 2793, 3136, 3520, 3951, 4186};
void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)     // the sound producing function
{   
    int x;   
    long delayAmount = (long)(1000000/frequencyInHertz);
    long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
    for (x=0;x<loopTime;x++)   
    {   
        digitalWrite(speakerPin,HIGH);
        
        delayMicroseconds(delayAmount);
        digitalWrite(speakerPin,LOW);
        delayMicroseconds(delayAmount);
    }   
}

void scale(int intr, int ctr)
{   
  for (int i = 0; i < NUM_NOTES; i++) {
    // Play each note for 1000/ctr milliseconds to make a scale
    beep(piezoPin, notes[i]/intr, 1000/ctr);
    //tone(piezoPin, sensorValue, 1000); 
  }
}
void setup() 
{
  pinMode(piezoPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(inPin, INPUT);
  Serial.begin(9600);
 
}


void loop() 
{
  
  sensorValue = analogRead(sensorPin);
  buttonValue = digitalRead(inPin);
  if(buttonValue == HIGH)
  {
    count = count+1;
  }
  int outputValue = map(sensorValue, 0, 1023, 0, 136);
  analogWrite(ledPin, outputValue); //sensorValue*5/1023);
  int interval = (int) (sensorValue*NUM_NOTES/1024.0);
 Serial.print("\n count:");
  Serial.print(count);
  Serial.print("\n OV:");
  Serial.print(outputValue);
  //beep(piezoPin, notes[interval], 50);
  scale(interval,count);
  //delay(1000);
}

